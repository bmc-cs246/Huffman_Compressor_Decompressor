#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "huff_tree_node.h"
#include "huff_tree.h"

#define INPUT_SIZE 100   
#define STR_SIZE 500
#define FREQ_SIZE 256
int main()
{
    char buf[INPUT_SIZE];
    fgets(buf, INPUT_SIZE, stdin);
    if(buf[strlen(buf) - 1] == '\n')
    {
        buf[strlen(buf) - 1] = '\0';
    }
    int i = 0;
    char* p = strtok(buf, " ");
    char* array[3];
    while(p != NULL)
    {
        array[i++] = p;
        p = strtok(NULL, " ");
    } 
    char* exe = array[0];
    char* input_filename = array[1];
    char* output_filename = array[2];
    
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
    for (int ch = 0; ch < FREQ_SIZE; ch++)
    {
        if(freq[ch] > 0)
        {
            huff_tree_node* node = new_node(ch, freq[ch]);
        }
    }
    fclose(file);
    return 0;
}