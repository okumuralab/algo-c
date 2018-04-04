/***********************************************************
    ishi2.c -- 石取りゲーム 2
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, max, n, x, f[21], r, my_turn;

    f[1] = f[2] = 1;
    for (i = 3; i <= 20; i++) f[i] = f[i - 1] + f[i - 2];
    printf("石の数 (2..10000)? ");  scanf("%d", &n);
    if (n < 2 || n > 10000) return 1;
    max = n - 1;
    for (my_turn = 1; n != 0; my_turn ^= 1) {
        printf("%d 個まで取れます.\n", max);
        if (my_turn) {
            x = n;
            for (i = 20; x != f[i]; i--) if (x > f[i]) x -= f[i];
            if (x > max) x = 1;
            printf("私は %d 個の石をとります.\n", x);
        } else do {
            printf("何個とりますか? ");
            r = scanf("%d", &x);  scanf("%*[^\n]");
        } while (r != 1 || x < 1 || x > max);
        n -= x;  max = 2 * x;  if (max > n) max = n;
        printf("残りは %d 個です.\n", n);
    }
    if (my_turn) printf("あなたの勝ちです!\n");
    else         printf("私の勝ちです!\n");
    return 0;
}
