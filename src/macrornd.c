/***********************************************************
    macrornd.c -- 線形合同法
***********************************************************/
/* C言語のマクロで実現した簡単な線形合同法乱数. */

#include <limits.h>
static unsigned long seed = 1;  /* 奇数 */
#define rnd() (seed *= 69069UL, seed / (ULONG_MAX + 1.0))
#define init_rnd(x) (seed = (unsigned long)(x) | 1)

/************ 以下はテスト用 *************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    unsigned long i, n;
    double r, s1, s2, x, x0, xprev;

    printf("乱数の種? ");  scanf("%lu", &i);
    init_rnd(i);  /* 任意の unsigned long で初期化. */
    printf("個数? ");  scanf("%lu", &n);

    s1 = x0 = xprev = rnd() - 0.5;  s2 = x0 * x0;  r = 0;
    for (i = 1; i < n; i++) {
        x = rnd() - 0.5;
        s1 += x;  s2 += x * x;  r += xprev * x;  xprev = x;
    }
    r = (n * (r + x * x0) - s1 * s1) / (n * s2 - s1 * s1);

    printf("以下は期待値との差を標準誤差で割ったもの.\n");
    printf("20回中19回は±2以内に入るはず.\n");
    printf("平均値……………… %6.3f\n", s1 * sqrt(12.0 / n));
    printf("隣同士の相関係数… %6.3f\n",
        ((n - 1) * r + 1) * sqrt((n + 1.0) / (n * (n - 3.0))));

    return 0;
}
