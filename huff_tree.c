#include "huff_tree.h"

huff_tree* new_tree(int capacity)
{
    huff_tree* new = (huff_tree*) malloc(sizeof(huff_tree));
    new->size = 0; 
    new->capacity = capacity; 
    new->array = (huff_tree_node**) malloc(sizeof(huff_tree_node*));
}

// void build_tree(huff_tree* tree)
// {

// }