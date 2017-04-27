#include <stdio.h>
#include <stdlib.h>

#include "node.h"

Node* new_node(int ch, int freq)
{
    Node* new = malloc(sizeof(Node));
    new->ch = ch; 
    new->freq = freq; 
    new->left = NULL;
    new->right = NULL;
    return new;
}

void free_node(Node* root)
{
    if(root)
    {
        free(root->left);
        free(root->right);
        free(root);
    }
}

int size(Node* root)
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

