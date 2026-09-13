#include "lexer.h"

#include <stdlib.h>
#include <string.h>

/*
enum LargeLiteralType
{
    LLTYPE_
} typedef LargeLiteralType;
*/

bool lexer_next(Token *token, FILE *file)
{   
    char *tok = NULL;
    size_t toksz = 0;
    TokenType toktype = TOKEN_UNKNOWN;
    while (true)
    {
        char c;
        fread(&c, 1, 1, file);
        if (ferror(file)) goto errorquit;
        if (feof(file))
        {
            
        }

        switch (toktype)
        {
            case TOKEN_STRING_LITERAL:
                switch (c)
                {
                    case '"':
                        c = '\0';

                    default:
                        char *new_tok = realloc(tok, toksz + 1);
                        if (!new_tok) { free(tok); return false; }
                        tok = new_tok;
                        tok[toksz++] = c;

                        if (!c) { *token = (Token){ .type = TOKEN_STRING_LITERAL, .value = tok }; return true; }
                }

            default:
                switch (c)
                {
                    
                    case '(':
                        //if (tok) { toktype = }
                        *token = (Token){ .type = TOKEN_LPAREN };
                        return true;

                    case ')':
                        *token = (Token){ .type = TOKEN_RPAREN };
                        return true;

                    case '{':
                        *token = (Token){ .type = TOKEN_LBRACE };
                        return true;

                    case '}':
                        *token = (Token){ .type = TOKEN_RBRACE };
                        return true;
                }
        }

        /*
        quit_largetokend:
            fseek(file, -1, SEEK_CUR);
            *token = (Token){ .type =  };
            return true;
        */
    }

    errorquit:
        free(tok);
    return false;

    endliteralorEOF:
        switch (toktype)
        {
            case TOKEN_STRING_LITERAL:
                *token = (Token){ .type = TOKEN_STRING_LITERAL, .value = tok, .size = toksz };
                return true;

            case TOKEN_INTEGER_LITERAL:
                *token = (Token){ .type = TOKEN_INTEGER_LITERAL, .value = (void *)toksz };
                return true;

            default:
                *token = (Token){ .type = TOKEN_EOF };
                return true;
        }
}

void lexer_token_free(Token *token) { if (token->type == TOKEN_STRING_LITERAL) free(token->value); }