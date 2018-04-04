/***********************************************************
    ishi1.c -- 石取りゲーム 1
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n, m, x, r, my_turn;

    printf("最後に石を取った側が負けです. パスはできません.\n");
    printf("石の数? ");  scanf("%d", &n);
    printf("１回に取れる最大の石の数? ");  scanf("%d", &m);
    if (n < 1 || m < 1) return 1;
    for (my_turn = 1; n != 0; my_turn ^= 1) {
        if (my_turn) {
            x = (n - 1) % (m + 1);  if (x == 0) x = 1;
            printf("私は %d 個の石を取ります.\n", x);
        } else do {
            printf("何個取りますか? ");
            r = scanf("%d", &x);  scanf("%*[^\n]");
        } while (r != 1 || x <= 0 || x > m || x > n);
        n -= x;  printf("残りは %d 個です.\n", n);
    }
    if (my_turn) printf("あなたの負けです!\n");
    else         printf("私の負けです!\n");
    return 0;
}
