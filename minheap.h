#ifndef _MINHEAP_
#define _MINHEAP_

#include "node.h"

typedef struct MinHeap
{
    int size; 
    int capacity; 
    Node** forest; 
}MinHeap;

// A utility function to create a min heap of given capacity
MinHeap* createMinHeap(int capacity);
//minheapify the heap 
void heapify(MinHeap* heap, int index);
//insert a node into minheap
void insert(MinHeap* heap, Node* node);
//build a minheap
void buildMinHeap(MinHeap* heap);
// Creates a minheap of capacity equal to size and inserts all ch[] 
MinHeap* createAndBuildMinHeap(int* ch, int* freq, int size);
//find the minimum node in the heap and return it
Node* findMin(MinHeap* heap);

#endif