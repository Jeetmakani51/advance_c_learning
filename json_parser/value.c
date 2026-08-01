#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "value.h"

JsonValue *make_string(char *s){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_STRING;
    v->value.string = s;
    return v;
}

JsonValue *make_number(double n){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_NUMBER;
    v->value.number = n;
    return v;
}

JsonValue *make_bool(int b){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_BOOL;
    v->value.boolean = b;
    return v;
}

JsonValue *make_null(){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_NULL;
    return v;
}

JsonValue *make_array(){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_ARRAY;
    v->value.array.items = NULL; // no items yet
    v->value.array.count = 0;
    v->value.array.capacity = 0;
    return v;
}

JsonValue *make_object(){
    JsonValue *v = malloc(sizeof(JsonValue));
    if(v == NULL){
        return NULL;
    }
    v->type = JSON_OBJECT;
    v->value.object.keys = NULL; // no items yet
    v->value.object.values = NULL;
    v->value.object.count = 0;
    v->value.object.capacity = 0;
    return v;
}

void array_push(JsonValue *arr, JsonValue *items){
    if(arr->value.array.count == arr -> value.array.capacity){
        int new_capacity = arr->value.array.capacity == 0 ? 4 : arr->value.array.capacity * 2; // if full double the capacity
        arr->value.array.items = realloc(arr->value.array.items, new_capacity * sizeof(JsonValue *)); // realloc to new capacity
        arr->value.array.capacity = new_capacity;
    }
    arr->value.array.items[arr->value.array.count] = items;
    arr->value.array.count++;
}

void object_push(JsonValue *obj, char *key, JsonValue *val){
    if(obj->value.object.count == obj -> value.object.capacity){
        int new_capacity = obj->value.object.capacity == 0 ? 4 : obj->value.object.capacity * 2; // if full double the capacity
        obj->value.object.keys = realloc(obj->value.object.keys, new_capacity * sizeof(char *)); // realloc to new capacity
        obj->value.object.values = realloc(obj->value.object.values, new_capacity * sizeof(JsonValue *)); // realloc to new capacity
        obj->value.object.capacity = new_capacity;
    }
    obj->value.object.keys[obj->value.object.count] = key;
    obj->value.object.values[obj->value.object.count] = val;
    obj->value.object.count++;
}

void free_value(JsonValue *v){
    if(v == NULL)return;
    switch (v->type)
    {
    case JSON_STRING:
        free(v->value.string);
        break;
    
    case JSON_ARRAY:
        for(int i = 0; i < v->value.array.count; i++){
            free_value(v->value.array.items[i]); // recursively free each item
        }
        free(v->value.array.items);
        break;

    case JSON_OBJECT:
        for(int i = 0; i < v->value.object.count; i++){
            free(v->value.object.keys[i]); //individual elements
            free_value(v->value.object.values[i]);
        }
        free(v->value.object.keys);
        free(v->value.object.values);
        break;
    default:
        break;
    }
    free(v);
}

void print_value(JsonValue *v, int indent){ // recursively walks the JsonValue tree and prints it
    if(v == NULL) return;
    switch(v -> type){
        case JSON_STRING:
            printf("\"%s\"", v->value.string);
            break;

        case JSON_NUMBER:
            printf("%g", v->value.number);
            break;

        case JSON_BOOL:
            printf("%s", v->value.boolean ? "true" : "false");
            break;

        case JSON_NULL:
            printf("null");
            break;

        case JSON_ARRAY:
            printf("[\n");
            for(int i = 0; i < v->value.array.count; i++){
                print_value(v->value.array.items[i],indent+2);
                if(i < v->value.array.count - 1){
                    printf(",");
                    printf("\n");
                }
            }
            printf("\n]");
            break;

        case JSON_OBJECT:
            printf("{\n");
            for(int i = 0; i < v->value.object.count; i++){
                printf("\"%s\": ", v->value.object.keys[i]);
                print_value(v->value.object.values[i],indent + 2);
                if(i < v -> value.object.count - 1){
                    printf(",");
                    printf("\n");
                }
            }
            printf("\n}");
            break;
    }
}