/***********************************************************
    maxmin.c -- 最大値・最小値
***********************************************************/
#define MAX2(x, y) ((x) > (y) ? (x) : (y))
#define MIN2(x, y) ((x) < (y) ? (x) : (y))

int findmax(int n, int a[])
{
    int i, max;

    max = a[0];
    for (i = 1; i < n; i++)
        if (a[i] > max) max = a[i];
    return max;
}

int findmin(int n, int a[])
{
    int i, min;

    min = a[0];
    for (i = 1; i < n; i++)
        if (a[i] < min) min = a[i];
    return min;
}

void findmaxmin(int n, int a[], int *pmax, int *pmin)
{
    int i, max, min, a1, a2;

    if (n & 1)               max = min = a[0];
    else if (a[0] > a[1]) {  max = a[0];  min = a[1];  }
    else                  {  max = a[1];  min = a[0];  }
    for (i = 2 - (n & 1); i < n; i += 2) {
        a1 = a[i];  a2 = a[i + 1];
        if (a1 > a2) {
            if (a1 > max) max = a1;
            if (a2 < min) min = a2;
        } else {
            if (a2 > max) max = a2;
            if (a1 < min) min = a1;
        }
    }
    *pmax = max;  *pmin = min;
}

#include <limits.h>
#include <stdarg.h>           /* 不定個の引数を使う */

int maxn(int n, ...)          /* n 個の int の最大値 */
{
    va_list ap;               /* 不定個の引数へのポインタ */
    int max, x;

    va_start(ap, n);          /* ap の初期化 */
    max = INT_MIN;
    while (--n >= 0) {
        x = va_arg(ap, int);  /* ap から int を取り出す */
        if (x > max) max = x;
    }
    va_end(ap);               /* ap の後始末 */
    return max;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int max, min;
    static int a[] = { 1, 7, 4 };

    printf("MAX2(1, 7) = %d\n", MAX2(1, 7));
    printf("MIN2(1, 7) = %d\n", MIN2(1, 7));

    printf("a[] = { 1, 7, 4 };\n");
    printf("findmax(3, a) = %d\n", findmax(3, a));
    printf("findmin(3, a) = %d\n", findmin(3, a));

    findmaxmin(3, a, &max, &min);
    printf("findmaxmin(3, a, &max, &min);\n");
    printf("max = %d, min = %d\n", max, min);

    printf("maxn(3, 1, 7, 4) = %d\n", maxn(3, 1, 7, 4));

    return 0;
}
