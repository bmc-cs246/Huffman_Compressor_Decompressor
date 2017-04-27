#include <stdio.h>
#include <stdlib.h>

#include "minheap.h"

MinHeap* createMinHeap(int capacity)
{
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->size = 0;  // current size is 0
    heap->capacity = capacity;
    heap->forest = (Node**)malloc(heap->capacity * sizeof(Node*));
    return heap;
}

// Creates a minheap of capacity equal to size and inserts all ch[] 
MinHeap* createAndBuildMinHeap(int ch[], int freq[], int size)
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->forest[i] = new_node(ch[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// A standard funvtion to build min heap
void buildMinHeap(MinHeap* heap)
{
    int n = heap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; i--)
    {
        heapify(heap, i);
    }  
}
//standard minheapify 
void heapify(MinHeap* heap, int index)
{
    int min= index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
 
    if (left < heap->size && heap->forest[left]->freq < heap->forest[min]->freq)
    {
        min = left;
    }
    else if(left < heap->size && heap->forest[left]->freq == heap->forest[min]->freq)
    {
        if(heap->forest[left]->ch < heap->forest[min]->ch)
        {
            min = left;
        }
    }
 
    if (right < heap->size && heap->forest[right]->freq < heap->forest[min]->freq)
    {
        min = right;
    }
    else if (right < heap->size && heap->forest[right]->freq == heap->forest[min]->freq)
    {
        if(heap->forest[right]->ch < heap->forest[min]->ch)
        {
            min = right;
        }
    }
 
    if (min != index)
    {
        Node* tmp = heap->forest[min]; 
        heap->forest[min] = heap->forest[index];
        heap->forest[index] = tmp;
        heapify(heap, min);
    }
}

// A utility function to insert a new node to Min Heap
void insert(MinHeap* heap, Node* node)
{
    heap->size++;
    int i = heap->size - 1;
    while (i && node->freq < heap->forest[(i - 1)/2]->freq)
    {
        heap->forest[i] = heap->forest[(i - 1)/2];
        i = (i - 1)/2;
    }
    heap->forest[i] = node;
}

// A standard function to extract minimum value node from heap
Node* findMin(MinHeap* heap)
{
    Node* tmp = heap->forest[0];
    heap->forest[0] = heap->forest[heap->size - 1];
    heap->size--;
    heapify(heap, 0);
    return tmp;
}
