#ifndef HUFF_TREE
#define HUFF_TREE

typedef struct huff_tree_node {
  int ch;
  int freq;
  struct huff_tree_node* left;
  struct huff_tree_node* right;
} huff_tree_node;

typedef struct huff_tree_record {
  huff_tree_node* nodes[256];
  int num_nodes;
  huff_tree_node* root;
  huff_tree_node* cur_node;
} huff_tree_record;

typedef struct huff_tree_record* huff_tree;

typedef struct encoding_record {
  int length;
  unsigned int code;
} encoding_record;

void printFrequencies(int frequencies[256]);

huff_tree huff_tree_new();

void add_node(huff_tree ht, int ch, int freq);

void print_nodes(huff_tree ht);

void construct_tree(huff_tree ht);

void build_huffman_table(huff_tree ht, encoding_record encodings[256]);

void print_encodings(encoding_record encodings[256]);

void huff_tree_free(huff_tree ht);

int traverse(huff_tree ht, int bit);

#endif  
