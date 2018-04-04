/***********************************************************
    knapsack.c -- ナップザックの問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000  /* ナップザックの大きさの上限 */
#define MAXITEM  100  /* 品目数の上限 */
int maxsofar[MAXSIZE + 1], newitem[MAXSIZE + 1];
int size[MAXITEM], price[MAXITEM];

int main(void)
{
    int i, n, knapsize, s, space, newvalue, smallest;

    printf("ナップザックの大きさ? ");  scanf("%d", &knapsize);
    if (knapsize <= 0 || knapsize > MAXSIZE) return 1;
    printf("品目数? ");  scanf("%d", &n);
    if (n <= 0 || n > MAXITEM) return 1;
    for (i = 0; i < n; i++) {
        printf("品目 %d の大きさ? ", i);  scanf("%d", &size[i]);
        printf("品目 %d の価格  ? ", i);  scanf("%d", &price[i]);
    }

    smallest = knapsize + 1;
    for (i = 0; i < n; i++)
        if (size[i] < smallest) smallest = size[i];

    for (s = 0; s <= knapsize; s++) maxsofar[s] = 0;
    for (i = 0; i < n; i++) {
        for (s = size[i]; s <= knapsize; s++) {
            space = s - size[i];
            newvalue = maxsofar[space] + price[i];
            if (newvalue > maxsofar[s]) {
                maxsofar[s] = newvalue;  newitem[s] = i;
            }
        }
    }

    printf("品目  価格\n");
    for (s = knapsize; s >= smallest; s -= size[newitem[s]])
        printf("%4d %5d\n", newitem[s], price[newitem[s]]);
    printf("合計 %5d\n", maxsofar[knapsize]);

    return 0;
}
