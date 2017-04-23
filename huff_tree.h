/*
  Prototypes of functions for working with huffman tree.
*/

#ifndef HUFF_TREE_
#define HUFF_TREE_

#include "huff_tree_node.h"

typedef struct huff_tree
{
    int size; 
    int capacity; 
    huff_tree_node** array;
}huff_tree;

//make a new huff_tree (malloc)
huff_tree* new_tree(int capacity);

//build tree
void build_tree(huff_tree* tree);

#endif