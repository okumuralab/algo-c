/***********************************************************
    sieve1.c -- Eratosthenes (エラトステネス) のふるい
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE  1
#define N 8190
char flag[N + 1];  /* flag[i]=TRUE if 2i+3 is prime */

int main(void)
{
    int i, p, k, count;

    printf("%8d", 2);
    count = 1;
    for (i = 0; i <= N; i++) flag[i] = TRUE;
    for (i = 0; i <= N; i++)
        if (flag[i]) {
            p = i + i + 3;
            printf("%8d", p);
            for (k = i + p; k <= N; k += p) flag[k] = FALSE;
            count++;
        }
    printf("\n%d primes\n", count);
    return 0;
}
