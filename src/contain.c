/***********************************************************
    contain.c -- 区間の包含関係
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
typedef enum {FALSE, TRUE} boolean;
typedef struct {  int left, right;  } interval;

int cmp(const void *x, const void *y)
{
    if (((interval *)x)->left  > ((interval *)y)->left)  return  1;
    if (((interval *)x)->left  < ((interval *)y)->left)  return -1;
    if (((interval *)x)->right > ((interval *)y)->right) return  1;
    if (((interval *)x)->right < ((interval *)y)->right) return -1;
    return 0;
}

void mark(int n, interval a[], boolean contained[])
{
    int i, maxright;

    qsort(a, n, sizeof(interval), cmp);
    maxright = a[0].right;
    contained[0] = FALSE;
    for (i = 1; i < n; i++)
        if (a[i].right <= maxright)
            contained[i] = TRUE;
        else {
            maxright = a[i].right;
            contained[i] = FALSE;
        }
}

#define N 20
interval a[N];
boolean contained[N];

int main(void)
{
    int i, x, y;

    i = 0;
    while (i < N) {
        x = rand() / (RAND_MAX / 100 + 1);
        y = rand() / (RAND_MAX / 100 + 1);
        if (x < y) {  a[i].left = x;  a[i].right = y;  i++;  }
    }
    mark(N, a, contained);
    for (i = 0; i < N; i++)
        printf("(%2d, %2d) %c\n",
            a[i].left, a[i].right, (contained[i]) ? '*' : ' ');
    return 0;
}
