#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huff_tree.h"

int main(int argc, char ** argv) {

  if (argc != 3) {
    printf("Terminating. You must pass exactly 2 arguments.\n");
    return 0;
  }
  char * infile = argv[1];
  char * outfile = argv[2];
  
  // printf("infile: %s, outfile: %s\n", infile, outfile);

  FILE * fin = fopen(infile, "r");
  if (fin == NULL) {
    printf("Terminating. Failed to open %s.\n", infile);
    return 0;
  }

  // 1. Read in the table of character frequencies in the first 256 ints
  // in the input file.
  int frequencies[256] = { 0 };
  fread(frequencies, sizeof(int), 256, fin);
  printFrequencies(frequencies);

  // 2. Build the Huffman tree (as in steps 2-4 above).
  huff_tree ht = huff_tree_new();
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] != 0) {
      add_node(ht, i, frequencies[i]);
    }
  }
  #ifdef DEBUG
  print_nodes(ht);
  #endif
  construct_tree(ht);

  // 3. For every bit read in from the input file, traverse down the
  // Huffman tree (going left for 0 bits and right for 1 bits).
  // When you reach a leaf, there will be a character stored in the
  // leaf node. Write this character to the output file.

  // 4. Repeat step 3 for every character in the input file (as determined
  // by looking at the frequency of the root of the Huffman tree, which
  // is necessarily the total number of characters in the input).
  
  // printf("\n\n\n");
  FILE* fout = fopen(outfile, "w");
  int c;
  while ((c = fgetc(fin)) != EOF) {
    // printf("read %x \n", c); fflush(stdout);
    for (int i = 7; i >= 0; i--) {
      int bit = !!(c & (1 << i));
      // printf("processing bit %d \n", bit); fflush(stdout);
      int res = traverse(ht, bit);
      if (res != -1) {
        fputc(res, fout);
      }
    }
  }


  // 5. We’re done. Close the files and free your memory.
  fclose(fin);
  fclose(fout);

  return 0;
}