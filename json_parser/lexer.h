#ifndef LEXER_H
#define LEXER_H


typedef enum{
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_STRING,
    TOKEN_NUMBER,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_EOF
}TokenType;

typedef struct{
    TokenType type;
    char *value;
}Token;

typedef struct lexer{
    char *source;
    int pos;
    int length;
}Lexer;

Lexer create_lexer(char *source);
char current(Lexer *l);
void skip_whitespace(Lexer *l);
Token make_token(TokenType type, char *value);
Token next_token(Lexer *l);

#endif