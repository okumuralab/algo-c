/***********************************************************
    nim.c -- 三山くずし
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int a[4], i, j, imax, max, n, r, x, my_turn;

    for (i = 1; i <= 3; i++) {
        printf("%d 番の山の石の数? ", i);  scanf("%d", &a[i]);
        if (a[i] <= 0) return 1;
    }
    for (my_turn = 1; ; my_turn ^= 1) {
        max = 0;
        for (i = 1; i <= 3; i++) {
            printf(" %d ", i);
            for (j = 1; j <= a[i]; j++) printf("*");
            printf("\n");
            if (a[i] > max) {
                max = a[i];  imax = i;
            }
        }
        if (max == 0) break;
        if (my_turn) {
            printf("私の番です.\n");
            x = a[1] ^ a[2] ^ a[3];  /* 排他的論理和 */
            j = 0;
            for (i = 1; i <= 3; i++)
                if (a[i] > (a[i] ^ x)) j = i;
            if (j != 0) a[j] ^= x;  else a[imax]--;
        } else {
            do {
                printf("何番の山からとりますか? ");
                r = scanf("%d", &i);  scanf("%*[^\n]");
            } while (r != 1 || i < 1 || i > 3 || a[i] == 0);
            do {
                printf("何個とりますか? ");
                r = scanf("%d", &n);  scanf("%*[^\n]");
            } while (r != 1 || n <= 0 || n > a[i]);
            a[i] -= n;
        }
    }
    if (my_turn) printf("あなたの勝ちです!\n");
    else         printf("私の勝ちです!\n");
    return 0;
}
