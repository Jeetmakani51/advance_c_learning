#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "entry.h"

typedef struct Container{
    int size;
    Entry **slots; //slots points to start of an array, each element in the array is itself a pointer(Entry *) to the head of linked list chain
}HashTable;

void insert(HashTable *ht, char *key, char *value);
char *get(HashTable *ht, char *key);
void cleanup(HashTable *ht);
void print_all(HashTable *ht);
HashTable create_table(int size);
int hash(char *key, int size);

#endif