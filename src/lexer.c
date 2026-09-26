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
        if (ferror(file)) goto errorquit_generic;

        if (state == TOKEN_STRING_LITERAL)
        {
            if (feof(file)) goto errorquit_generic;
            switch (c)
            {
                case '"':
                    goto returnbuffer;

                case '\\':
                    fread(&c, 1, 1, file);
                    if (feof(file) || ferror(file)) goto errorquit_generic;
                    
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

                        case 'v':
                            c = 11;
                            break;

                        case 'f':
                            c = 12;
                            break;

                        case 'r':
                            c = 13;
                            break;

                        case 'e':
                            c = 27;
                            break;

                        case '"':
                            c = '"';
                            break;

                        case '/':
                            continue;

                        default:
                            goto errorquit_generic;
                    }
                    goto applybuffer;

                default:
                    if (isprint((unsigned char)c)) goto applybuffer;
                    continue;
            }
        }
        else if (state == TOKEN_LITERAL)
        {
            if (feof(file)) goto returnliteral;
            if (!isalnum((unsigned char)c)) { fseek(file, -1, SEEK_CUR); goto returnliteral; }
            goto applybuffer;
        }
        else
        {
            if (feof(file)) goto handleEOF;
            if (isspace((unsigned char)c)) continue;
            if (isalnum((unsigned char)c)) { state = TOKEN_LITERAL; goto applybuffer; };

            switch (c)
            {
                case '"':
                    state = TOKEN_STRING_LITERAL;
                    continue;

                case '+':
                    *token = (Token){ .type = TOKEN_PLUS };
                    break;

                case '-':
                    *token = (Token){ .type = TOKEN_MINUS };
                    break;

                case '=':
                    *token = (Token){ .type = TOKEN_EQUALS };
                    break;

                case '*':
                    *token = (Token){ .type = TOKEN_STAR };
                    break;

                case '/':
                    *token = (Token){ .type = TOKEN_SLASH };
                    break;

                case '\\':
                    *token = (Token){ .type = TOKEN_BACKSLASH };
                    break;

                case '{':
                    *token = (Token){ .type = TOKEN_LBRACE };
                    break;

                case '}':
                    *token = (Token){ .type = TOKEN_RBRACE };
                    break;

                case '(':
                    *token = (Token){ .type = TOKEN_LPAREN };
                    break;

                case ')':
                    *token = (Token){ .type = TOKEN_RPAREN };
                    break;

                case ';':
                    *token = (Token){ .type = TOKEN_SEMICOLON };
                    break;

                case '.':
                    *token = (Token){ .type = TOKEN_DOT };
                    break;

                case ',':
                    *token = (Token){ .type = TOKEN_COMMA };
                    break;

                case '<':
                    *token = (Token){ .type = TOKEN_LT };
                    break;

                case '>':
                    *token = (Token){ .type = TOKEN_GT };
                    break;

                case '!':
                    *token = (Token){ .type = TOKEN_EXCL };
                    break;

                case '&':
                    *token = (Token){ .type = TOKEN_AMP };
                    break;

                case '|':
                    *token = (Token){ .type = TOKEN_PIPE };
                    break;

                case '%':
                    *token = (Token){ .type = TOKEN_PREC };
                    break;

                case '^':
                    *token = (Token){ .type = TOKEN_CIRCFLEX };
                    break;

                case ':':
                    *token = (Token){ .type = TOKEN_COLON };
                    break;

                case '~':
                    *token = (Token){ .type = TOKEN_TILDE };
                    break;

                default:
                    *token = (Token){ .type = TOKEN_UNKNOWN };
                    break;
            }
            return true;
        }
        
        continue;
        // =================================
        applybuffer:
            void *new = realloc(buffdata, buffsize + 1);
            if (!new) goto errorquit_generic;
            buffdata = new;
            buffdata[buffsize++] = c;
    }

    // =================================

    errorquit_generic:
        free(buffdata);
    return false;

    // =================================

    handleEOF:
        free(buffdata);
        *token = (Token){ .type = TOKEN_EOF };
    return true;

    // =================================

    returnliteral:
        void *new = realloc(buffdata, buffsize + 1);
        if (!new) { free(buffdata); return false; }
        buffdata = new;
        buffdata[buffsize++] = '\0';
    returnbuffer:
        *token = (Token)
        {
            .type = state,
            .data = buffdata,
            .size = buffsize
        };
    return true;

}