#include "hash_table.h"
#include <stdio.h>

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