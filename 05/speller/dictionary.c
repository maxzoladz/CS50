// Implements a dictionary's functionality
#include <stdlib.h>
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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

int wordCount = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hashValue = hash(word);
    node *wordPointer = table[hashValue];

    while (wordPointer != NULL) {
        if(strcasecmp(word, wordPointer -> word) == 0) return true;

        wordPointer  = wordPointer -> next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hashValue = 0;
    int wordLength = strlen(word);
    
    for (int wordIndex = 0; wordIndex < wordLength; wordIndex++) {
        hashValue = hashValue + toupper(word[wordIndex]);
    }
    
    return hashValue + wordLength;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");

    if (dictionary == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];

    while(fscanf(source, "%s", word) == 1) {

        node *tableNode = malloc(sizeof(node));

        if (tableNode == NULL) return 1;

        strcpy(tableNode -> word, word);
        wordCount++;

        int hashValue = hash(word);

        tableNode -> next = table[hashValue];

        table[hashValue] = tableNode;
    }

    fclose(source);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int tableIndex = 0; tableIndex < N; tableIndex++) {

        node *current = table[tableIndex];

        while (current != NULL) {
            node *temp = current;
            current = current -> next;
            free(temp);
        }

        if (current == NULL && tableIndex == N - 1) return true;
    }

    return false;
}
