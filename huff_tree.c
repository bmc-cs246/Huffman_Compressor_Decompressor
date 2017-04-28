#include <stdio.h>
#include <stdlib.h>
#include "huff_tree.h"


void printFrequencies(int frequencies[256]) {
  printf("Frequencies:\n");
  for (int i = 0; i < 256; i++) {
    if (frequencies[i] != 0) {
      printf("%c (%d): %d\n", i, i, frequencies[i]);
    }
  }
  printf("\n");
}

huff_tree huff_tree_new() {
  huff_tree ht = calloc(1, sizeof(huff_tree_record));
  return ht;
}

void add_node(huff_tree ht, int ch, int freq) {
  huff_tree_node* node = calloc(1, sizeof(huff_tree_node));
  node->ch = ch;
  node->freq = freq;
  ht->nodes[ht->num_nodes++] = node;

}

void print_nodes(huff_tree ht) {
  printf("Huffman Tree Nodes:\n");
  for (int i = 0; i < ht->num_nodes; i++) {
    huff_tree_node* node = ht->nodes[i];
    printf("%c (%d): %d / %02x00\n", node->ch, node->ch, node->freq, node->freq);
  }
}

huff_tree_node* remove_min_node(huff_tree ht) {
  if (ht->num_nodes == 0) {
    return NULL;
  }
  huff_tree_node* min_node = ht->nodes[0];
  int min_node_index = 0;
  for (int i = 1; i < ht->num_nodes; i++) {
    huff_tree_node* cur_node = ht->nodes[i];
    if (cur_node->freq < min_node->freq) {
      min_node = cur_node;
      min_node_index = i;
    }
  }
  huff_tree_node* last_node = ht->nodes[ht->num_nodes - 1];
  ht->nodes[ht->num_nodes - 1] = NULL;
  ht->nodes[min_node_index] = last_node;
  ht->num_nodes--;
  return min_node;
}

huff_tree_node* combine_nodes(huff_tree_node* x, huff_tree_node* y) {
  static int parent_ch = -1;
  huff_tree_node* parent = malloc(sizeof(huff_tree_node));
  parent->ch = parent_ch--;
  parent->freq = x->freq + y->freq;
  parent->left = x;
  parent->right = y;
  return parent;
}

void construct_tree(huff_tree ht) {
  while (ht->num_nodes > 1) {
    huff_tree_node* x = remove_min_node(ht);
    huff_tree_node* y = remove_min_node(ht);
    ht->nodes[ht->num_nodes++] = combine_nodes(x, y);
  }
  ht->cur_node = ht->root = ht->nodes[0];
}

void gen_encodings(encoding_record encodings[256], huff_tree_node* node, encoding_record cur_encoding) {
  if (node->left == NULL && node->right == NULL) {
    encodings[node->ch] = cur_encoding;
  }
  else {
    if (node->left != NULL) {
      encoding_record next_encoding;
      next_encoding.length = cur_encoding.length + 1;
      next_encoding.code = (cur_encoding.code << 1) | 0;
      gen_encodings(encodings, node->left, next_encoding);
    }
    if (node->right != NULL) {
      encoding_record next_encoding;
      next_encoding.length = cur_encoding.length + 1;
      next_encoding.code = (cur_encoding.code << 1) | 1;
      gen_encodings(encodings, node->right, next_encoding);
    }
  }
}

void build_huffman_table(huff_tree ht, encoding_record encodings[256]) {
  encoding_record start_encoding;
  start_encoding.length = 0;
  start_encoding.code = 0;
  gen_encodings(encodings, ht->root, start_encoding);
}

void printBits(int bits, void const * const ptr) {
    size_t size = bits / 8 + ((bits % 8 == 0) ? 0 : 1);
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    int i, j;

    for (i=size-1;i>=0;i--)
    {
        for (j = (i == 0) ? ((bits % 8) - 1) : 7; j>=0; j--)
        {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}


void print_encodings(encoding_record encodings[256]) {
  printf("Huffman Encodings:\n");
  for (int i = 0; i < 256; i++) {
    encoding_record cur = encodings[i];
    if (cur.length != 0) {
      printf("%c (%d): length=%d, code=%04x / ", i, i, cur.length, cur.code);
      printBits(cur.length, &cur.code);
    }
  }
}

void huff_tree_free(huff_tree ht) {

}

int traverse(huff_tree ht, int bit) {
  if (bit) {
    ht->cur_node = ht->cur_node->right;
  }
  else {
    ht->cur_node = ht->cur_node->left;
  }
  if (ht->cur_node->left == NULL && ht->cur_node->right == NULL) {
    int ret = ht->cur_node->ch;
    ht->cur_node = ht->root;
    return ret;
  }
  return -1;
}