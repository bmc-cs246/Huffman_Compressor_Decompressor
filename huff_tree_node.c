#include <stdio.h>
#include <stdlib.h>

#include "huff_tree_node.h"

huff_tree_node* new_node(int ch, int freq)
{
    huff_tree_node* new = (huff_new_node*) malloc(sizeof(huff_tree_node));
    new->ch = ch; 
    new->freq = freq; 
    new->left = NULL;
    new->right = NULL:
    return new;
}

int isLeaf(huff_tree_node* root)
{
    return(root->left == NULL && root->right == NULL);
}

void free_node(huff_tree_node* root)
{
    if(root)
    {
        free(root->left);
        free(root->right);
        free(root);
    }
}

int size(huff_tree_node* root)
{
    if(root)
    {
        return 1 + size(root->left)+size(root->right);
    }
    else
    {
        return 0;
    }
}

// void insert_node(huff_tree* tree, huff_tree_node* node)
// {
//     tree->size++;
//     int i = tree->size - 1;
//     while(i && node->freq < tree->array[(i - 1)/2]->freq)
//     {
//         tree->array[i] = tree->array[(i -1)/2];
//         i = (i -1)/2;
//     }
//     tree->array[i] = node;
// }