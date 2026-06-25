#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_RECORDS 100

typedef struct{
    char key[32];
    char value[64];
}Record;

typedef struct{
    Record records[MAX_RECORDS];
    int count;
}Database;

char *my_strcpy(char *dest, const char *src){
    const char *ptr = src;
    char *ptr2 = dest;
    char c;
    do{
        c = *ptr;
        *ptr2 = c;
        ptr++;
        ptr2++;
    }while(c != '\0');
    return dest;
}

void insert(Database *db, char *key, char *value){
    if(db -> count >= MAX_RECORDS){
        printf("Database is full\n");
        return;
    }else{
        memset(&db->records[db->count], 0, sizeof(Record));
        my_strcpy(db -> records[db -> count].key, key);
        my_strcpy(db -> records[db -> count].value, value);
        db -> count++;
    }
}

void print_all(Database *db){
    for(int i = 0; i < db -> count; i++){
        printf("key : %s\n", db -> records[i].key);
        printf("value : %s\n", db -> records[i].value);
    }
}

void save(Database *db, char *binary_file){
    FILE *fp;
    fp = fopen(binary_file,"wb");
    if(fp == NULL){
        perror("fopen failed");
        return;
    }
    fwrite(db -> records, sizeof(Record), db -> count, fp);
    fclose(fp);
}

void load(Database *db, char *binary_file){
    FILE *fp;
    fp = fopen(binary_file,"rb");
    if(fp == NULL){
        printf("cannot open file\n");
        return;
    }
    db -> count = fread(db -> records, sizeof(Record), MAX_RECORDS, fp);
    fclose(fp);
}

char *get(Database *db, char *key){
    for(int i = 0; i < db -> count; i++){
        if(strcmp(db -> records[i].key, key) == 0){
            return db -> records[i].value;
        }
    }
    return NULL;
}

int main(){
    Database db;
    db.count = 0;
    load(&db, "database.bin");
    insert(&db, "name", "jeet");
    insert(&db, "age", "19");
    insert(&db, "hobby", "coding");
    insert(&db, "learning" , "c-advance");

    print_all(&db);

    char *result = get(&db, "name");
    if(result != NULL){
        printf("name : %s\n", result);
    }else{
        printf("key not found\n");
    }
    save(&db, "database.bin");
    return 0;
}