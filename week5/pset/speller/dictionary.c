// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int sizeofHashTable = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashCode = hash(word);
    node *n = table[hashCode];
    if(n == NULL){
        return false;
    }
    // FIXME: consider resetting pointer back to head for subsequent calls to check()!
    // As it stands, table[hashCode] has n == NULL so subsequent calls to the same
    // bucket or hashcode will ALWAYS result to false since pointer is at the terminal tail and not the head! 

    // On second thought, given that we're not setting table[hashcode] = n
    // n pointer is just a local variable within a stackframe that gets freed upon function return
    while(n != NULL){
        if(strcasecmp(n->word, word) == 0){
            return true;
        }
        n = n->next;
    }
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
    char buffer[LENGTH + 1];
    // Synonymous but saving on heap: char *buffer = malloc(sizeof(LENGTH + 1));
    FILE *file = fopen(dictionary, "r");
    if (file == NULL){
        printf("Cannot open file: %s", dictionary);
        return false;
    }

    // QUESTION: so fscanf() can take either a pointer or value at that address to store strings??
    // Seeing discrepancies in examples: https://www.ibm.com/docs/en/i/7.1?topic=functions-fscanf-read-formatted-data
    // https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
    while(fscanf(file, "%s", buffer) != EOF){
        int hashCode = hash(buffer);
        node *n = malloc(sizeof(node));
        if(n == NULL){
            printf("Not enough memory on heap to create new node");
            unload();
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
            // get reference to first element in link list @ index hashCode
            node *head = table[hashCode];
            // declaring new node n to be the first link
            n->next = head;
            // setting new node as the head of the list
            // so that when next node, N1 comes in, we have N0 -> OLD_HEAD linkage setup such that N1 -> N0-> OLD_HEAD
            table[hashCode] = n;
        }
        sizeofHashTable++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return sizeofHashTable;
}

void free_list(node *n){
    if(n->next != NULL){
        free_list(n->next);
    }
    //printf("freeing %p...\n", n);
    free(n);
    //printf("freed %p...\n", n);
    //printf("value at %p: %s\n", n, n->word);
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for(int i = 0; i < N; i++){
        if(table[i] != NULL){
            free_list(table[i]);
        }
    }
    return true;
}
