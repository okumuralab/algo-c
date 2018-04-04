/***********************************************************
    primroot.c -- 原始根
***********************************************************/
#define N 168
int prime[N];

void generate_primes(void)
{
    int j, k, x;

    prime[0] = 2;  x = 1;  k = 1;
    while (k < N) {
        x += 2;  j = 0;
        while (j < k && x % prime[j] != 0) j++;
        if (j == k) prime[k++] = x;
    }
}

int modpower(int n, int r, int m)  /* pow(n, r) % m */
{
    int t;

    t = 1;
    while (r != 0) {
        if (r & 1) t = (int)(((long)n * t) % m);
        n = (int)(((long)n * n) % m);  r /= 2;
    }
    return t;
}

int primitive_root(int k)
{
    int a, i, j, n, p;

    i = 0;  p = prime[k];  n = p - 1;
    for (i = 0; i < k; i++) {
        a = prime[i];
        for (j = 0; j < k; j++)
            if (n % prime[j] == 0 &&
                modpower(a, n / prime[j], p) == 1) break;
        if (j == k) return a;
    }
    return 0;  /* error, primitive root not found */
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    generate_primes();
    printf("素数と原始根\n");
    printf("%5d( -)", prime[0]);
    for (i = 1; i < N; i++) {
        if (i % 7 == 0) printf("\n");
        printf("%5d(%2d)", prime[i], primitive_root(i));
    }
    printf("\n");
    return 0;
}
