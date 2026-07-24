#include <stdio.h>
#include "lexer.h"

int main(){
    char *source = "{\"name\":\"Jeet\",\"age\":19,\"learning\":true,\"address\":null}";
    Lexer l = create_lexer(source);
    
    Token t;
    do {
        t = next_token(&l);
        printf("type: %d, value: %s\n", t.type, t.value ? t.value : "NULL");
    } while(t.type != TOKEN_EOF);
    
    return 0;
}