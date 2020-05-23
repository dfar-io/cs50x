// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Prototypes
static int hashTableIndex(char c);

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open the file
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Error when opening dictionary '%s'\n", dictionary);
        return false;
    }

    // Read line by line and insert into linked list
    char line[LENGTH + 1];
    while (fgets (line, sizeof line, fp) != NULL)
    {
        int index = hashTableIndex(line[0]);
        if (index == -1)
        {
            continue;
        }
        node *tmp = table[index];

        // Traverse to end of linked list
        while (tmp != NULL && tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        // Create a new node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            printf("Error when allocating memory for dictionary '%s'\n", dictionary);
            return false;
        }

        strcpy(newNode->word, line);
        newNode->next = NULL;

        // Initialize for first item in linked list
        if (tmp == NULL)
        {
            table[index] = newNode;
        }
        // Have previous node point to new node
        else
        {
            tmp->next = newNode;
        }
    }

    fclose(fp);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Go through each key in hashtable
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }

    return true;
}


// #################
// Private functions
// #################

// Provides the index of hash table based on first two characters
static int hashTableIndex(char c)
{
    // No character provided, give negative value to indicate failure
    if (!isalpha(c))
    {
        return -1;
    }

    const int offset = 97;
    return tolower(c) - offset;
}