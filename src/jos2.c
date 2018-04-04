/***********************************************************
    jos2.c -- Josephus (ヨセフス) の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int k, n, p;

    printf("人数? ");  scanf("%d", &n);
    printf("何人ごと? ");  scanf("%d", &p);
    k = p - 1;
    while (k < (p - 1) * n)
        k = (p * k) / (p - 1) + 1;
    printf("%d 番の人が残ります\n", p * n - k);
    return 0;
}
