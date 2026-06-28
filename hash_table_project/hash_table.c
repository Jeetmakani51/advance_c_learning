#include "hash_table.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int hash(char *key, int size){
    unsigned int total = 0;
    for(int i = 0; i < strlen(key); i++){
        total = total * 31 + key[i];
    }
    return total % size;
}

HashTable create_table(int size){
    HashTable ht;
    ht.size = size;
    Entry **slots = malloc(size * sizeof(Entry *));
    ht.slots = slots;
    for(int i = 0; i < size; i++){
        slots[i] = NULL;
    }
    return ht;
}

void insert(HashTable *ht, char *key, char *value){
    int index = hash(key, ht -> size);
    Entry *node = malloc(sizeof(Entry)); // size for the key string
    char *key_string = malloc(strlen(key) + 1);
    node -> key = key_string;
    strcpy(node -> key, key);
    char *value_string = malloc(strlen(value) + 1); // size for value string
    node -> value = value_string;
    strcpy(node -> value, value);

    node -> next = ht -> slots[index];
    ht -> slots[index] = node;
}

char *get(HashTable *ht, char *key){
    int index = hash(key, ht -> size);
    Entry *current = ht -> slots[index];
    while(current != NULL){
        if(strcmp(current -> key, key) == 0){
            return current -> value;
        }
        current = current -> next;
    }
    return NULL;
}

void cleanup(HashTable *ht){
    for(int i = 0; i < ht -> size; i++){
        Entry *current = ht -> slots[i];
        while(current != NULL){
            Entry *temp = current -> next;
            free(current -> key);
            free(current -> value);
            free(current);
            current = temp;
        }
    }
    free(ht -> slots);
}

void print_all(HashTable *ht){
    for(int i = 0; i < ht -> size; i++){
        Entry *current = ht -> slots[i];
        while(current != NULL){
            printf("%s\n", current -> key);
            printf("%s\n", current -> value);
            current = current -> next;
        }
    }
}
