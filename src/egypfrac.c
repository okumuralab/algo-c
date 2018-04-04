/***********************************************************
    egypfrac.c -- エジプトの分数
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int m, n, q;

    printf(" 分子 m = ");  scanf("%d", &m);
    printf(" 分母 n = ");  scanf("%d", &n);
    printf("%d/%d = ", m, n);
    while (n % m != 0) {
        q = n / m + 1;
        printf("1/%d + ", q);
        m = m * q - n;  n *= q;
    }
    printf("1/%d\n", n / m);
    return 0;
}
