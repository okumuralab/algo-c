/***********************************************************
    isbn.c -- ISBN番号
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, c, d[11];

    printf("ISBN book number: ");
    for (i = 1; i <= 10; i++) {
        c = getchar();
        if (c >= '0' && c <= '9')
            d[i] = c - '0';
        else if (i == 10 && (c == 'x' || c == 'X'))
            d[i] = 10;
        else
            return 1;
    }
    d[0] = 0;
    for (i = 1; i <= 10; i++) d[i] += d[i - 1];
    for (i = 1; i <= 10; i++) d[i] += d[i - 1];
    if (d[10] % 11 == 0) puts("Valid");  /* 有効な番号 */
    else                 puts("Wrong");  /* 無効な番号 */
    return 0;
}
