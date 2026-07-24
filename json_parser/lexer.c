
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include <ctype.h>

Lexer create_lexer(char *source){
    Lexer l;
    l.source = source;
    l.pos = 0;
    l.length = strlen(source);
    return l;
}

char current(Lexer *l){
    if(l -> pos >= l -> length){
        return '\0';
    }else{
        return l -> source[l -> pos];
    }
}

void skip_whitespace(Lexer *l){
    while(current(l) == ' ' || current(l) == '\n' || current(l) == '\t' || current(l) == '\r'){ // space, newline, tab, carraige return
        l -> pos++;
    }
}

Token make_token(TokenType type, char *value){
    Token t;
    t.type = type;
    t.value = value;
    return t;
}

Token next_token(Lexer *l){
    skip_whitespace(l);
    char c = current(l);
    switch (c)
    {
    case '{':
        l -> pos++;
        return make_token(TOKEN_LBRACE, NULL);
        break;
    
    case '}':
        l -> pos++;
        return make_token(TOKEN_RBRACE, NULL);
        break;

    case '[':
        l -> pos++;
        return make_token(TOKEN_LBRACKET,NULL);
        break;

    case ']':
        l -> pos++;
        return make_token(TOKEN_RBRACKET,NULL);
        break;

    case ':':
        l -> pos++;
        return make_token(TOKEN_COLON,NULL);
        break;

    case ',':
        l -> pos++;
        return make_token(TOKEN_COMMA,NULL);
        break;

    case '\0':
        l -> pos++;
        return make_token(TOKEN_EOF,NULL);
        break;

    default:
        break;
    }

    if(current(l) == '"'){
        l -> pos++;
        int start = l -> pos;
        while(current(l) != '"' && current(l) != '\0'){
            l -> pos++;
            
        }
        int current_length = l -> pos - start;
        char *buffer = malloc(current_length + 1);
        memcpy(buffer, l -> source + start, current_length);
        buffer[current_length] = '\0';
        if(current(l) == '"'){
            l -> pos++;
        }
        return make_token(TOKEN_STRING,buffer);
    }
    if(isdigit(current(l)) || current(l) == '-'){
        int start = l -> pos; // record start position
        if(current(l) == '-'){
            l -> pos++;
        }
        while(isdigit(current(l)) || isdigit(current(l))){
            l -> pos++;
        }
        int current_length = l -> pos - start;
        char *buffer = malloc(current_length + 1);
        memcpy(buffer, l -> source + start, current_length);
        buffer[current_length] = '\0';
        return make_token(TOKEN_NUMBER,buffer);
    }
    if(current(l) == 't'){
        if(strncmp(l -> source + l -> pos, "true", 4) == 0){
            l -> pos += 4;
        }
        return make_token(TOKEN_TRUE, NULL);
    }
    if(current(l) == 'f'){
        if(strncmp(l -> source + l -> pos, "false", 5) == 0){
            l -> pos += 5;
        }
        return make_token(TOKEN_FALSE, NULL);
    }
    if(current(l) == 'n'){
        if(strncmp(l -> source + l -> pos, "null", 4) == 0){
            l -> pos += 4;
        }
        return make_token(TOKEN_NULL, NULL);
    }
}
