#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "value.h"

int main(){
    char *source = "{\"name\":\"Jeet\",\"age\":19,\"learning\":true,\"friends\":[\"Alice\",\"Bob\"],\"address\":null}";

    Parser p = create_parser(source);
    JsonValue *root = parse_value(&p);
    
    print_value(root,0);
    printf("\n");

    free_value(root);
    return 0;
}