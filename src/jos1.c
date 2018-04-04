/***********************************************************
    jos1.c -- Josephus (ヨセフス) の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int j, k, n, p;

    printf("人数? ");  scanf("%d", &n);
    printf("何人ごと? ");  scanf("%d", &p);
    k = 1;
    for (j = 2; j <= n; j++) {
        k = (k + p) % j;
        if (k == 0) k = j;
    }
    printf("%d 番の人が残ります\n", k);
    return 0;
}
