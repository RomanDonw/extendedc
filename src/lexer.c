#include "lexer.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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