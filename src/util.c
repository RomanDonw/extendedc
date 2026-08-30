#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool fullreadfile(char **str, size_t *size, const char *filepath)
{
    char *ret = NULL;
    size_t sz = 0;

    FILE *f = fopen(filepath, "r");
    if (!f) return false;

    char buffer[512];

    size_t readbytes;
    while ((readbytes = fread(buffer, 1, sizeof(buffer), f)))
    {
        {
            char *new_ret = realloc(ret, sz + readbytes);
            if (!new_ret) goto errorquit;
            ret = new_ret;
        }

        memcpy(ret + sz, buffer, readbytes);

        sz += readbytes;
    }

    fclose(f);
    *str = ret;
    if (size) *size = sz;
    return true;

    errorquit:
        if (ret) free(ret);
        fclose(f);
    return false;
}