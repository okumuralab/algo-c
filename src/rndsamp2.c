/***********************************************************
    rndsamp2.c -- 無作為抽出
***********************************************************/

/***** 一様乱数 (線形合同法) ******************************/

#include <limits.h>
static unsigned long seed = 1;

void init_rnd(unsigned long x)
{
    seed = x;
}

unsigned long irnd(void)
{
    seed = seed * 1566083941UL + 1;
    return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

#include <stdio.h>

int rndsamp(int m, int s[])
{
    int i, n, x;

    n = 0;
    while (scanf("%d", &x) == 1) {
        if (++n <= m) s[n - 1] = x;
        else {
            i = (int)(n * rnd());
            if (i < m) s[i] = x;
        }
    }
    return n;
}

#include <stdlib.h>
#include <time.h>
#define M 1000

int main(void)
{
    int i, n, m;
    static int s[M];

    init_rnd((unsigned long) time(NULL));
    fprintf(stderr, "標準入力から, 標本の大きさと母集団の要素 (整数値)"
        "を読み込み, 標準出力に標本の要素を出力します.\n");
    if (scanf("%d", &m) != 1) return 1;
    fprintf(stderr, "標本の大きさ = %d\n", m);
    if (m > M) {
        fprintf(stderr, "標本の大きさは %d 以下でなければなりません\n", M);
        return 1;
    }
    n = rndsamp(m, s);
    fprintf(stderr, "母集団の大きさ = %d\n", n);
    for (i = 0; i < m && i < n; i++)
        printf("%8d", s[i]);
    printf("\n");

    return 0;
}
