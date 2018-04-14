/***********************************************************
    weights.c -- 秤の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int k, x, r;
    char *side[2] = { "左", "右" };

    printf("何グラムをはかりますか? ");  scanf("%d", &x);
    printf("はかるものを左の皿に乗せてください.\n");
    k = 1;
    while (x > 0) {
        r = x % 3;  x /= 3;
        if (r != 0) {
            printf("%5dグラムの重りを%sの皿に乗せます.\n",
                k, side[r - 1]);
            if (r == 2) x++;
        }
        k *= 3;
    }
    return 0;
}
