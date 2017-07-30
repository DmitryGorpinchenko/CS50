/****************************************************************************
 * dictionary.h
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Declares a dictionary's functionality.
 ***************************************************************************/

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

#define ALPHABET_SIZE 27

typedef struct node
{
    bool is_word;
    struct node* children[ALPHABET_SIZE];
}
node;

typedef struct dictionary
{
    int size;
    node* trie;
}
dictionary;

// returns pointer to new node
node* new_node(void);

/**
 * insert word into the trie
 */
bool insert(const char* word);

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word);

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary);

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void);

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void);

// frees trie data structure
void free_trie(node* trie);

#endif // DICTIONARY_H
