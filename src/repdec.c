/***********************************************************
    repdec.c -- 小数の循環節
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define N 1000   /* 分母の上限 */
#define BASE 10  /* 何進法か */

int main(void)
{
    unsigned int i, k, m, n;
    static unsigned int a[N + 1], p[N];

    for (i = 0; i < N; i++) p[i] = 0;
    do {
        printf("分母 n = ");  scanf("%u", &n);
        if (n > N) printf("%u 以下にしてください.\n", N);
    } while (n > N);
    printf("分子 m = ");  scanf("%u", &m);
    a[0] = m / n;  m %= n;  k = 0;
    do {
        p[m] = ++k;
        m *= BASE;  a[k] = m / n;  m %= n;
    } while (p[m] == 0);
    printf("%u.", a[0]);
    for (i = 1; i < p[m]; i++) printf("%u", a[i]);
    if (p[m] < k || a[k] != 0) {
        printf("{");
        for (i = p[m]; i <= k; i++) printf("%u", a[i]);
        printf("}");
    }
    printf("\n");
    return 0;
}
