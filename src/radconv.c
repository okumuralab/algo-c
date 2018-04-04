/***********************************************************
    radconv.c -- 基数の変換
***********************************************************/

int conv1(int x, int d, int m, int c[])
{
    int i;

    for (i = 0; x != 0 && i < m; i++) {
        c[i] = x % d;  x /= d;
    }
    if (x == 0) return i;   /* 桁数 */
    else        return -1;  /* エラー */
}

int conv2(int d1, int m1, int x1[], int d2, int m2, int x2[])
{
    int i, j, r, t;

    for (i = 0; m1 > 0 && i < m2; i++) {
        r = 0;
        for (j = m1 - 1; j >= 0; j--) {
            t = d1 * r + x1[j];  x1[j] = t / d2;  r = t % d2;
        }
        x2[i] = r;
        while (m1 > 0 && x1[m1 - 1] == 0) m1--;
    }
    if (m1 == 0) return i;   /* 桁数 */
    else         return -1;  /* エラー */
}

#include <stdio.h>
#include <stdlib.h>

#define M 1000

int main(void)
{
    int i, x, m1, m2;
    static int x1[M], x2[M];

    printf("x = ");  scanf("%d", &x);

    m1 = conv1(x, 8, M, x1);
    if (m1 < 0) {
        printf("conv1: error\n");  return 1;
    }

    printf("8進(octal): ");
    for (i = m1 - 1; i >= 0; i--) printf("%d", x1[i]);
    printf("\n");

    m2 = conv2(8, m1, x1, 2, M, x2);
    if (m1 < 0) {
        printf("conv2: error\n");  return 1;
    }

    printf("2進(binary): ");
    for (i = m2 - 1; i >= 0; i--) printf("%d", x2[i]);
    printf("\n");

    return 0;
}
