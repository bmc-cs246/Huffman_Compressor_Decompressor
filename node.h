/*
  Prototypes of functions for working with huffman tree nodes.
*/

#ifndef _NODE_
#define _NODE_

typedef struct Node
{
    int ch; 
    int freq; 
    struct Node* left; 
    struct Node* right;
}Node;

//make a new node (malloc)
Node* new_node(int ch, int freq);

//return true if node is leaf 
int isLeaf(Node* root);

//free all nodes in a binary tree
void free_node (Node* root);

//return the number of nodes in the tree
int size(Node* root);

#endif