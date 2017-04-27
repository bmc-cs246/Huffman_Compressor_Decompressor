#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "node.h"
#include "minheap.h"

#define INPUT_SIZE 100   
#define STR_SIZE 500
#define FREQ_SIZE 256

//make the huffman tree
Node* buildHuffmanTree(int* ch, int* freq, int size);

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Usage: %s \n", argv[0]);
        return 1;
    }
    char* input_filename = argv[1];
    char* output_filename = argv[2];
    
    FILE* file = fopen(input_filename, "r");
    if(!file)
    {
        printf("Cannot open file.");
    }
    char str[STR_SIZE];
    int freq[FREQ_SIZE] = { 0 };
    //count the frequecy of each char
    while(fgets(str, STR_SIZE, file) != NULL)
    {
        int length = strlen(str);
        for (int i = 0; i < length; i ++) 
        {
            char ch = str[i];
            freq[ch]++;
        }
    }
    int j = 0;
    int chars[FREQ_SIZE];
    int frequency[FREQ_SIZE];
    for(int i = 0; i < FREQ_SIZE; i++)
    {
        if(freq[i]!=0)
        {
            chars[j] = i; 
            frequency[j] = freq[i];
            j++;
        }
    }
    int size = j;
    Node* root = buildHuffmanTree(chars, frequency, size);
    
    fclose(file);
    return 0;
}

Node* buildHuffmanTree(int* ch, int* freq, int size)
{
    Node *left, *right, *root;
 
    // Step 1: Create a min heap of capacity equal to size.  Initially, there are
    // modes equal to size.
    MinHeap* minHeap = createAndBuildMinHeap(ch, freq, size);
    int n = -1; 
    // Iterate while size of heap doesn't become 1
    while (!(minHeap->size == 1))
    {
        // Step 2: Extract the two minimum freq items from min heap
        left = findMin(minHeap);
        right = findMin(minHeap);
 
        // Step 3:  Create a new internal node with frequency equal to the
        // sum of the two nodes frequencies. Make the two extracted node as
        // left and right children of this new node. Add this node to the min heap
        // '$' is a special value for internal nodes, not used
        root = new_node(n, left->freq + right->freq);
        n--;
        root->left = left;
        root->right = right;
        insert(minHeap, root);
        
    }
 
    // Step 4: The remaining node is the root node and the tree is complete.
    return findMin(minHeap);
}
