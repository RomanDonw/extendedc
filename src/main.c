#include <getopt.h>
#include <stdio.h>

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

    

    fclose(f);
    return 0;
}