/***********************************************************
    chaos.c -- カオスとアトラクタ
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int i;
    double p, k;

    printf("比例定数: ");  scanf("%lf", &k);
    printf("初期値  : ");  scanf("%lf", &p);
    for (i = 1; i <= 100; i++) {
        printf("%10.3f", p);
        if (i % 4 == 0) printf("\n");
        p += k * p * (1 - p);
    }
    return 0;
}
