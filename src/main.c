#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "lexer.h"

int main(int argc, char *argv[])
{
    const char *fname;
    {
        int p;
        while ((p = getopt(argc, argv, "s:")) != -1)
        {
            switch (p)
            {
                case 's':
                    fname = optarg;
                    break;
            }
        }
    }

    FILE *f = fopen(fname, "r");
    if (!f) { printf("unable to open file \"%s\"\n", fname); return 1; }

    Token t;
    for (lexer_next(f, &t); t.type != TOKEN_EOF; lexer_next(f, &t))
    {
        switch (t.type)
        {
            case TOKEN_UNKNOWN:
                puts("<UNKNOWN>");
                break;

            case TOKEN_EQUALS:
                puts("=");
                break;
            
            case TOKEN_PLUS:
                puts("+");
                break;

            case TOKEN_MINUS:
                puts("-");
                break;

            case TOKEN_STAR:
                puts("*");
                break;

            case TOKEN_SLASH:
                puts("/");
                break;

            case TOKEN_BACKSLASH:
                puts("\\");
                break;

            case TOKEN_LBRACE:
                puts("{");
                break;

            case TOKEN_RBRACE:
                puts("}");
                break;

            case TOKEN_LPAREN:
                puts("(");
                break;
            
            case TOKEN_RPAREN:
                puts(")");
                break;

            case TOKEN_SEMICOLON:
                puts(";");
                break;

            case TOKEN_DOT:
                puts(".");
                break;

            case TOKEN_COMMA:
                puts(",");
                break;

            case TOKEN_STRING_LITERAL:
                printf("[%zu]: ", t.size);
                bool reqln = false;
                for (size_t i = 0; i < t.size; i++)
                {
                    unsigned char c = ((unsigned char *)t.data)[i];
                    if (isprint(c)) { putchar(c); reqln = true; }
                    else { printf("\n  %hhu\n", c); reqln = false; }
                }
                if (reqln) putchar('\n');

                free(t.data);
                break;

            case TOKEN_LITERAL:
                printf("(%zu): %s\n", t.size, t.data);
                free(t.data);
                break;

            case TOKEN_LT: puts("<"); break;
            case TOKEN_GT: puts(">"); break;
            case TOKEN_EXCL: puts("!"); break;
            case TOKEN_AMP: puts("&"); break;
            case TOKEN_PIPE: puts("|"); break;
            case TOKEN_PREC: puts("%"); break;
            case TOKEN_CIRCFLEX: puts("^"); break;
            case TOKEN_COLON: puts(":"); break;
            case TOKEN_TILDE: puts("~"); break;

            default: puts("<undefined>"); break;
        }
    }

    fclose(f);
    return 0;
}