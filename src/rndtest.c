/***********************************************************
    rndtest.c -- 乱数
***********************************************************/
/* 乱数のごく簡単なテスト */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define rnd() (1.0 / (RAND_MAX + 1.0)) * rand()

int main(void)
{
    unsigned seed;
    unsigned long i, n;
    double r, s1, s2, x, x0, xprev;

    printf("乱数の種? ");  scanf("%u", &seed);
    srand(seed);  /* 任意の unsigned int で初期化. */
    printf("個数? ");  scanf("%lu", &n);

    s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
    for (i = 1; i < n; i++) {
        x = rnd() - 0.5;
        s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
    }
    r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

    printf("以下は期待値との差を標準誤差で割ったもの.\n");
    printf("20回中19回は±2以内に入るはず.\n");
    printf("平均値………………… %6.3f\n", s1 * sqrt(12.0 / n));
    printf("隣どうしの相関係数… %6.3f\n",
        ((n - 1) * r + 1) * sqrt((n + 1.0) / (n * (n - 3.0))));

    return 0;
}
