/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"


// global variable representing the dictionary
dictionary dict;

// indicator of loading success
bool is_loaded = false;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    int n = strlen(word);    
    
    node* ptr = dict.trie;
    
    for(int i = 0; i < n ; i++)
    {
        char c = tolower(word[i]);
        
        int id = (c == '\'') ? (ALPHABET_SIZE - 1) : (c - 'a');
        
        if(ptr->children[id] == NULL)
        {
            return false;
        }
        else 
        {
            ptr = ptr->children[id];
        }        
    }
    
    if(ptr->is_word)
    {
        return true;
    }
    
    return false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // initialize the dictionary
    dict.size = 0;
    dict.trie = new_node();
    if(dict.trie == NULL)
    {
        return false;
    }
    
    FILE* in = fopen(dictionary, "r");
    
    if(in == NULL)
    {
        return false;
    }
    
    char word[LENGTH + 1];
    
    while(fscanf(in, "%s", word) == 1)
    {
        if(!insert(word))
        {
            return false;
        }
    }
    
    is_loaded = true;
    
    fclose(in);
    
    return true;
}

bool insert(const char* word)
{
    int n = strlen(word);    
    
    node* ptr = dict.trie;
    
    for(int i = 0; i < n ; i++)
    {
        int id = (word[i] == '\'') ? (ALPHABET_SIZE - 1) : (word[i] - 'a');
        
        if(ptr->children[id] == NULL)
        {
            ptr->children[id] = new_node();
            if(ptr->children[id] == NULL)
            {
                return false;
            }
        }
        ptr = ptr->children[id];        
    }
    
    if(!ptr->is_word)
    {
        ptr->is_word = true;
        dict.size++;
    }
    
    return true;
}

// node constructor
node* new_node(void)
{
    node* new_node = malloc(sizeof(node));
    if(new_node == NULL)
    {
        return NULL;
    }
    new_node->is_word = false;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        new_node->children[i] = NULL;
    } 
    return new_node;
}


/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return is_loaded ? dict.size : 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{   
    free_trie(dict.trie);
    return true;   
}

// frees trie
void free_trie(node* trie)
{
    if(trie == NULL)
    {
        return;
    }
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        free_trie(trie->children[i]);
    }
    free(trie);
}
