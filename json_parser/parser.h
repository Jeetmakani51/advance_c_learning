#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "value.h"

typedef struct{
    Lexer lexer;
    Token current;
}Parser;

Parser create_parser(char *source);
JsonValue *parse_value(Parser *p);
void advance(Parser *p);
#endif