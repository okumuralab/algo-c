/***********************************************************
    sieve2.c -- Eratosthenes (エラトステネス) のふるい
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE  1
#define S 1000
#define N 5000
#define L  100
#define M  167

/* Counts primes less than 2LN.
   S = sqrt(2LN).
   M >= number of (odd primes <= S). */

char flag[N];
int  kk[M], pp[M];

int main(void)
{
    int  i, j, k, m, n, p, count;

    for (i = 0; i < N; i++) flag[i] = TRUE;
    count = 1;  /* 2 is prime */
    m = 0;
    for (i = 1; i < N; i++) {
        if (flag[i]) {
            p = i + i + 1;  /* p is prime */
            count++;
            if (p <= S) {
                k = i + p;
                while (k < N) {
                    flag[k] = FALSE;  k += p;
                }
                /* assert(m < M); */
                pp[m] = p;  kk[m] = k - N;
                m++;
            }
        } else flag[i] = TRUE;
    }
    printf("      1 -   10000: %4d\n", count);
    for (n = 1; n < L; n++) {
        count = 0;
        for (j = 0; j < m; j++) {
            p = pp[j];  k = kk[j];
            while (k < N) {
                flag[k] = FALSE;  k += p;
            }
            kk[j] = k - N;
        }
        for (i = 0; i < N; i++)
            if (flag[i]) count++;  /* 2Nn+2i+1 is prime */
            else flag[i] = TRUE;
        printf("%3d0001 - %3d0000: %4d\n", n, n + 1, count);
    }
    return 0;
}
