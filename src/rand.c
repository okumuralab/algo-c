/***********************************************************
    rand.c -- rand()
***********************************************************/

#define RAND_MAX  32767
static unsigned long next = 1;

int rand(void)
{
    next = next * 1103515245L + 12345;
    return (unsigned)(next / 65536L) % 32768U;
}

void srand(unsigned seed)
{
    next = seed;
}

/**********************************************************/

#include <stdio.h>

int main(void)
{
    int i, j;

    printf("乱数表\n");
    for (i = 0; i < 20; i++) {
        for (j = 0; j < 8; j++) printf("%8d", rand());
        printf("\n");
    }
    return 0;
}
