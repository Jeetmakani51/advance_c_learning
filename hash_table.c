#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Entry{
    char *key;
    char *value;
    struct Entry *next;
}Entry;

typedef struct Container{
    int size;
    Entry **slots; //slots points to start of an array, each element in the array is itself a pointer(Entry *) to the head of linked list chain
}HashTable;

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

int main(){
    HashTable ht = create_table(10);
    insert(&ht, "name", "jeet");
    insert(&ht, "age", "19");
    insert(&ht, "hobby", "coding");
    insert(&ht, "book", "programming");
    insert(&ht, "AI", "claude");
    insert(&ht, "purpose", "learning");

    print_all(&ht);

    printf("existing key : %s\n", get(&ht, "hobby"));
    printf("missing key : %s\n", get(&ht, "money"));

    cleanup(&ht);
    return 0;
}