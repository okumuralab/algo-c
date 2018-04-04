/***********************************************************
    water.c -- 水をはかる問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

int gcd(int x, int y)  /* 最大公約数 */
{
    if (x == 0) return y;  else return gcd(y % x, x);
}

int main(void)
{
    int a, b, v, x, y;

    printf("容器Ａの容積? ");  scanf("%d", &a);
    printf("容器Ｂの容積? ");  scanf("%d", &b);
    printf("はかりたい容積? ");  scanf("%d", &v);
    if (v > a && v > b || v % gcd(a, b) != 0) {
        printf("はかれません\n");  return 1;
    }
    x = y = 0;
    do {
        if (x == 0) {
            printf("Ａに水を満たします\n");  x = a;
        } else if (y == b) {
            printf("Ｂを空にします\n");  y = 0;
        } else if (x < b - y) {
            printf("Ａの水をすべてＢに移します\n");
            y += x;  x = 0;
        } else {
            printf("Ａの水をＢがいっぱいになるまで"
                "Ｂに移します\n");  x -= b - y;  y = b;
        }
    } while (x != v && y != v);
    if      (x == v) printf("Ａにはかれました\n");
    else if (y == v) printf("Ｂにはかれました\n");
    return 0;
}
