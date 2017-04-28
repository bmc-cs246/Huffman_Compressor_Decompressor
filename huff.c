#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_tree.h"
#include "bit.h"

#define MAX_LINE_SIZE 5000

int main(int argc, char ** argv) {
  if (argc != 3) {
    printf("Terminating. You must pass exactly 2 arguments.\n");
    return 0;
  }
  char * infile = argv[1];
  char * outfile = argv[2];
  
  // printf("infile: %s, outfile: %s\n", infile, outfile);

  FILE * fp = fopen(infile, "r");
  if (fp == NULL) {
    printf("Terminating. Failed to open %s.\n", infile);
    return 0;
  }

  // 1. Calculate the frequencies of all the characters in the input file.
  // For example, if the file contains abracadabra, you will calculate that
  // there are 5 as, 2 bs, 1 c, 1 d, and 2 rs.
  int frequencies[256] = { 0 };
  int c;
  while ((c = fgetc(fp)) != EOF) {
    frequencies[c]++;
  }
  #ifdef DEBUG
  printFrequencies(frequencies);
  #endif

  // 2. For each character with a non-zero frequency, create a leaf
  // huff_tree_node containing the character (in the ch field) and the
  // frequency (in the freq field). These trees (each initially containing
  // one node) are collectively known as the forest.
  huff_tree ht = huff_tree_new();
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] != 0) {
      add_node(ht, i, frequencies[i]);
    }
  }
  #ifdef DEBUG
  print_nodes(ht);
  #endif



  // 3. Let x be the minimum tree in the forest and y be the next-minimum tree
  // in the forest. (Comparing trees is done by the freq stored in the root,
  // using ch to break ties.) Remove x and y from the forest. Create a new
  // huff_tree_node (call it n), whose left child is x and whose right child is
  // y. Choose a fresh negative number—that is, a negative number that hasn’t
  // been used yet. A convenient way to do this is to count down from -1. Let
  // n’s ch field be this negative number, and let n’s freq field be the sum
  // of x’s freq and y’s freq. Put n into the forest.
  // 4. If the forest has more than one element, repeat step 3. Otherwise,
  // we have arrived at the final Huffman tree.
  construct_tree(ht);

  // 5. The Huffman tree tells you how to encode every character. To encode
  // a character (all of which are stored in leaves of the tree), consider the
  // path from the root to the leaf containing that character. For every left
  // child traversed, add a 0 to the encoding. For every right child, add a 1.
  // So, if the path from the root to the leaf containing r requires going left,
  // then left, then right, the encoding for r is 001. Using this notion of
  // encoding, build a Huffman table that allows you to look up a character and
  // find its encoding.
  encoding_record encodings[256] = {{0, 0}};
  build_huffman_table(ht, encodings);
  #ifdef DEBUG
  print_encodings(encodings);
  #endif


  // 6. There are 256 possible characters. Write 256 ints to the output file;
  // the nth int is the frequency for the nth character. In the case of
  // abracadabra, int number 97 will have the value 5, whereas all ints
  // before that will be 0.
  FILE* fout = fopen(outfile, "wb");
  fwrite(frequencies, sizeof(int), 256, fout);

  // 7. For each character in the input file, write its encoding in the output
  // file as a sequence of bits. With r’s encoding above, this would mean
  // writing three bits to the file. Do not use three bytes.
  fseek(fp, 0, SEEK_SET);
  int buf = 0;
  int buf_length = 0;
  int buf_bit = 0;
  int byte_to_write;
  while ((c = fgetc(fp)) != EOF) {
    feed_buf(encodings[c]);
    while ((byte_to_write = get_buf_byte()) != -1) {
      fputc(byte_to_write, fout);
    }
  }
  if ((byte_to_write = buf_flush()) != -1) {
    fputc(byte_to_write, fout);
  }


  // 8. We’re done. Close the files and free your memory.

  fclose(fp);
  fclose(fout);
  return 0;
}