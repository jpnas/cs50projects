// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Creating a global variable for counting the number of words
int count = 0;

// Number of buckets in hash table
const unsigned int N = 100000;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int index = hash(word);
    if (table[index] != NULL)
    {
        for (node *cursor = table[index]; cursor != NULL; cursor = cursor->next)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
        }
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
   int hashnum = 0;
   char hash_word[strlen(word)];
   strcpy(hash_word, word);
   for (int i = 0; hash_word[i] != '\0'; i++)
   {
       hash_word[i] = tolower(hash_word[i]);
   }
   for (int i = 0; i < strlen(hash_word); i++)
   {
       hashnum = hashnum + hash_word[i] * (10*i + 10); 
   }
   hashnum = (hashnum << 3) % N;
   return hashnum;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        return false;
    }
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    char word[LENGTH + 1];
    while (fscanf(f, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word);
        int index = hash(word);
        if (table[index] == NULL)
        {
            n->next = NULL;
            table[index] = n;
        }
        else
        {
        n->next = table[index];
        table[index] = n;
        }
        count++;
    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
       node *cursor = table[i];
       while (cursor != NULL)
       {
       node *tmp = cursor;
       cursor = cursor->next;
       free(tmp);
       }
    }
    return true;
}
