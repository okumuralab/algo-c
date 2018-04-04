/***********************************************************
    sum.c -- 情報落ち
***********************************************************/

float sum1(int n, float a[])  /* 通常の方法 */
{
    int i;
    float s;

    s = 0;
    for (i = 0; i < n; i++) s += a[i];
    return s;
}

float sum2(int n, float a[])  /* 情報落ち対策 */
{
    int i;
    float r, s, t;

    r = 0;  s = 0;    /* s は和, r は積み残し */
    for (i = 0; i < n; i++) {
        r += a[i];    /* 積み残し + 加えたい値 */
        t = s;        /* 前回までの和 */
        s += r;       /* 和を更新 */
        t -= s;       /* 実際に積まれた値の符号を変えたもの */
        r += t;       /* 積み残し */
    }
    return s;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    static float a[10001];

    printf("1 + 0.0001 + ... + 0.0001 = 2\n");
    a[0] = 1;
    for (i = 1; i <= 10000; i++) a[i] = 0.0001;
    printf("方法1: %.6f\n", sum1(10001, a));
    printf("方法2: %.6f\n", sum2(10001, a));
    return 0;
}
