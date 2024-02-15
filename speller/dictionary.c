// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

//counter variable to keep track size of dictionary
unsigned int counter = 0;

//variable for hash value
unsigned int hash_value;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    hash_value = hash(word);
    node *cursor = table[hash_value];

    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    unsigned long total = 0;

    for(int i = 0; i < strlen(word); i++)
    {
        total += total + tolower(word[i]);
    }

    return total % N;


}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //open the dictionary file
    FILE *file = fopen(dictionary, "r");

    //check file exists
    if(file == NULL)
    {
        printf("no such file exists");
        fclose(file);
        return false;
    }

    //read each word in the file
    char word[LENGTH + 1];
    while(fscanf(file, "%s", word) != EOF)
    {
        node *new = malloc(sizeof(node));

        if(new == NULL)
        {
            printf("not enough memory to create new node");
            fclose(file);
            return false;
        }

    // add each word to the hash table
    strcpy(new->word, word);
    hash_value = hash(word);
    new->next = table[hash_value];
    table[hash_value] = new;
    counter++;

    }


    //close the dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for(int i = 0; i < N; i++)
    {
        //set cursor to start of linked list
        node *cursor = table[i];

        //if cursor is not null, free memory wiith help of second pointer
        while(cursor != NULL)
        {
            node *tmp = cursor;
            //move cursor to next node
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
