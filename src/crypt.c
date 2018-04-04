/***********************************************************
    crypt.c -- 暗号
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int c, r;
    FILE *infile, *outfile;

    if (argc < 3 || argc > 4 ||
     (infile  = fopen(argv[1], "rb")) == NULL ||
     (outfile = fopen(argv[2], "wb")) == NULL) {
        fputs("使用法: crypt infile outfile [key]\n", stderr);
        return 1;
    }
    if (argc == 4) srand(atoi(argv[3]));
    while ((c = getc(infile)) != EOF) {
        do {
            r = rand() / ((RAND_MAX + 1U) / 256);
        } while (r >= 256);
        putc(c ^ r, outfile);
    }
    return 0;
}
