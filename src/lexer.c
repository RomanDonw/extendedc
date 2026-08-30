#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

Token lex(FILE *file)
{
    if (feof(file)) return (Token){ .type = TOKEN_EOF };

    char *tok = NULL;
    size_t size = 0;
    while (true)
    {
        char c;
        if (fread(&c, 1, 1, file) < 1); // im bored :(
        
        //char *
    }

    char *new_tok = realloc(tok, );
}