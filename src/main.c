#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

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
    while (lexer_next(f, &t))
    {
        if (t.type == TOKEN_EOF) { puts("reached EOF"); break; }
        else if (t.type == TOKEN_STRING_LITERAL) { puts(t.data); free(t.data); }
        else printf("%u\n", t.type);
    }

    fclose(f);
    return 0;
}