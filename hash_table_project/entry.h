#ifndef ENTRY_H
#define ENTRY_H

typedef struct Entry{
    char *key;
    char *value;
    struct Entry *next;
}Entry;

#endif