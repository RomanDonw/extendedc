#include "lexer.h"

#include <stdlib.h>
#include <string.h>

bool lexer_next(Token *token, FILE *file)
{
    if (feof(file))
    {
        *token = (Token){ .type = TOKEN_EOF };
        return true;
    }

    /*
    char *tok = NULL;
    size_t size = 0;
    while (true)
    {
        if (feof(file)) return (Token){ .type = TOKEN_EOF };
        char c;
        if (fread(&c, 1, 1, file) < 1); // im bored :(
        
        //char *
    }

    char *new_tok = realloc(tok, );
    */

    bool returnvalue = true;

    char *tok = NULL;
    size_t size = 0;
    while (true)
    {
        char c;
        if (!fread(&c, 1, 1, file))
        {
            free(tok);
            if (feof(file))
            {
                *token = (Token){ .type = TOKEN_EOF };
                return true;
            }
            return false;
        }

        switch (c)
        {
            case '(':
                
        }
        
        {
            register char *new_tok = realloc(tok, size + 1);
            if (!new_tok) { free(tok); return false; }
            tok = new_tok;
        }
    }

    //free
    //return 
}

void lexer_token_free(Token *token) { free(token->value); }