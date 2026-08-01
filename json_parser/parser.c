#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

Parser create_parser(char *source){
    Parser p;
    p.lexer = create_lexer(source);
    p.current = next_token(&p.lexer);
    return p;
}

void advance(Parser *p){
    p -> current = next_token(&p -> lexer);
}

JsonValue *parse_value(Parser *p){
    switch(p -> current.type){
        case TOKEN_STRING:{

            JsonValue *v = make_string(p -> current.value);
            advance(p);
            return v;
        }
        
        case TOKEN_NUMBER:{

            double val = atof(p -> current.value);
            free(p->current.value); // free the "19 string from lexer"
            p->current.value = NULL;
            JsonValue *v = make_number(val);
            advance(p);
            return v;
        }

        case TOKEN_TRUE:{

            JsonValue *v = make_bool(1);
            advance(p);
            return v;
        }

        case TOKEN_FALSE:{

            JsonValue *v = make_bool(0);
            advance(p);
            return v;
        }

        case TOKEN_NULL:{
            
            JsonValue *v = make_null();
            advance(p);
            return v;
        }

        case TOKEN_LBRACE:
            advance(p);
            JsonValue *obj = make_object();
            while(p -> current.type != TOKEN_RBRACE && p -> current.type != TOKEN_EOF){
                printf("DEBUG token type: %d\n", p->current.type);
                char *key = p -> current.value;
                advance(p); // skip the key
                advance(p); // skip the :
                JsonValue *val = parse_value(p);
                object_push(obj,key,val);
                if(p -> current.type == TOKEN_COMMA){
                    advance(p);
                }
            }
            advance(p); //skip the }
            return obj;

        case TOKEN_LBRACKET:
            advance(p); ///skip the [
            JsonValue *arr = make_array();
            while(p -> current.type != TOKEN_RBRACKET && p -> current.type != TOKEN_EOF){
                JsonValue *item = parse_value(p);
                array_push(arr, item);
                if(p -> current.type == TOKEN_COMMA){
                    advance(p);
                }
            }
            advance(p); // skip ]
            return arr;
    }
}