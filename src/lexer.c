#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if 0
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
#endif

bool lexer_next(FILE *file, Token *token)
{
    if (feof(file)) goto handleEOF;
    
    char *buffdata = NULL;
    size_t buffsize = 0;
    char c;
    TokenType state = TOKEN_UNKNOWN;
    while (true)
    {
        fread(&c, 1, 1, file);
        if (feof(file)) { free(buffdata); goto handleEOF; }
        if (ferror(file)) { free(buffdata); return false; }

        if (state == TOKEN_STRING_LITERAL)
        {
            switch (c)
            {
                case '"':
                    *token = (Token)
                    {
                        .type = TOKEN_STRING_LITERAL,
                        .data = buffdata,
                        .size = buffsize
                    };
                    return true;

                case '\\':
                    fread(&c, 1, 1, file);
                    if (feof(file)) { free(buffdata); goto handleEOF; }
                    if (ferror(file)) { free(buffdata); return false; }

                    switch (c)
                    {
                        case '0':
                            c = 0;
                            break;

                        case 'a':
                            c = 7;
                            break;

                        case 'b':
                            c = 8;
                            break;

                        case 't':
                            c = 9;
                            break;

                        case 'n':
                            c = 10;
                            break;

                        case 'f':
                            c = 12;
                            break;

                        case 'r':
                            c = 13;
                            break;

                        default:
                            free(buffdata);
                            return false;
                    }

                default:
                {
                    void *new = realloc(buffdata, buffsize + 1);
                    if (!new) { free(buffdata); return false; }
                    buffdata = new;
                    buffdata[buffsize++] = c;
                }
            }
        }
        else if (state == TOKEN_LITERAL)
        {
            
        }
        else
        {
            if (isspace(c)) continue;
            switch (c)
            {
                case '"':
                    state = TOKEN_STRING_LITERAL;
                    goto loop_continue;

                case '+':
                    *token = (Token){ .type = TOKEN_PLUS };
                    break;

                case '-':
                    *token = (Token){ .type = TOKEN_MINUS };
                    break;

                case '=':
                    *token = (Token){ .type = TOKEN_EQUALS };
                    break;

                default:
                    *token = (Token){ .type = TOKEN_UNKNOWN };
                    break;
            }
            break;
        }

        loop_continue:
        continue;
    }

    free(buffdata);
    return true;
    handleEOF:
        *token = (Token){ .type = TOKEN_EOF };
    return true;
}