/*
  Prototypes of functions for working with huffman tree nodes.
*/

#ifndef HUFF_TREE_NODE_
#define HUFF_TREE_NODE_

typedef struct huff_tree_node
{
    int ch; 
    int freq; 
    struct huff_tree_node* left; 
    struct huff_tree_node* right;
}huff_tree_node;

//make a new node (malloc)
huff_tree_node* new_node(int ch, int freq);

//return true if node is leaf 
int isLeaf(huff_tree_node* root);

//free all nodes in a binary tree
void free_node (huff_tree_node* root);

//return the number of nodes in the tree
int size(huff_tree_node* root);

// //insert a new node to huff tree
// void insert_node(huff_tree* tree, huff_tree_node* node);

#endif