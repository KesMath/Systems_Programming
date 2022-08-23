// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // one optimization route is to create buckets for all permutations of 26^(first n characters) - (set of first n characters from all 100k dictionary items)
    // essentially doing a set subtraction problem in order to get the benefit of shortened chains (for search performance) without the wasted space having unnecessary buckets
    // then we can do (int)(word[0] + word[1] + word[2] + ... word[n]) as our improved hash function!
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    char *buffer[LENGTH + 1];
    //TODO: try with char *buffer = malloc(sizeof(LENGTH + 1));
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        printf("Cannot open file: %s", dictionary);
        return false;
    }

    // QUESTION: so fscanf() can take either a pointer or value at that address to store strings??
    // Seeing discrepancies in examples: https://www.ibm.com/docs/en/i/7.1?topic=functions-fscanf-read-formatted-data
    // https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
    while(fscanf(file, "%s", buffer) != EOF){
        printf("Buffer address: %p", &buffer);
        int hashCode = hash(buffer);
        node *n = malloc(sizeof(node));
        if(n == NULL){
            printf("Not enough memory on heap to create new node");
            // call upload() here to free up already created nodes
            fclose(file);
            return false;
        }
        strcpy(n->word, buffer);

        // insertion of first node in bucket or index
        if(table[hashCode] == NULL){
            table[hashCode] = n;
        }
        // chaining nodes within a given bucket or index
        else{
            node *head = table[hashCode];
            n->next = head;
            table[hashCode] = n;
        }
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
