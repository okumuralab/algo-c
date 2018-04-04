/***********************************************************
    lucas.c -- 素数のLucasテスト
***********************************************************/
#define N 1000
char a[N + 1], x[N];

int prime(int p)
{
    int h, i, j, k, s;

    for (i = 0; i < p; i++) a[i] = 0;
    a[2] = 1;  /* a = 4 */
    for (k = 2; k < p; k++) {
        for (i = 0; i < p; i++) {
            x[i] = a[i];  a[i] = 1;
        }
        a[1] = 0;  /* a = -2 mod M_p */
        for (i = 0; i < p; i++)
            if (x[i]) {
                s = 0;  h = i;
                for (j = 0; j < p; j++) {
                    s = (s >> 1) + a[h] + x[j];
                    a[h] = s & 1;  h = (h + 1) % p;
                }
                if (s > 1) {
                    while (a[h]) {
                        a[h] = 0;  h = (h + 1) % p;
                    }
                    a[h] = 1;
                }
            }
    }
    a[p] = 1 - a[0];  /* 番人 */
    i = 1;
    while (a[i] == a[0]) i++;
    return (i == p);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int p;

    printf("2^p - 1 は素数かどうか調べます (p: 素数).\n");
    printf("p? ");  scanf("%d", &p);
    if (p < 3 || p > N) return 1;
    if (prime(p)) printf("2^%d - 1 は素数です.\n", p);
    else          printf("2^%d - 1 は合成数です.\n", p);
    return 0;
}
