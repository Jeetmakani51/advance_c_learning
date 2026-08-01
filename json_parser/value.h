#ifndef VALUE_H
#define VALUE_H
#include "lexer.h"

typedef enum{
    JSON_STRING,
    JSON_NUMBER,
    JSON_BOOL,
    JSON_NULL,
    JSON_ARRAY,
    JSON_OBJECT
}JsonType;

typedef struct JsonValue{
    JsonType type;
    union{
        char *string;
        double number;
        int boolean;
        struct{
            struct JsonValue **items;
            int count;
            int capacity;
        }array;
        struct{
            char **keys;
            struct JsonValue **values;
            int count;
            int capacity;
        }object;
    }value;
}JsonValue;

JsonValue *make_string(char *s);
JsonValue *make_number(double n);
JsonValue *make_bool(int b);
JsonValue *make_null();
JsonValue *make_array();
JsonValue *make_object();
void array_push(JsonValue *arr, JsonValue *item);
void object_push(JsonValue *obj, char *key, JsonValue *val);
void free_value(JsonValue *v);
void print_value(JsonValue *v, int indent);

#endif