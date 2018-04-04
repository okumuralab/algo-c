/***********************************************************
    srchmat.c -- 2次元の探索
***********************************************************/
typedef int keytype;
typedef keytype matrix[10][10];

enum {NOT_FOUND, FOUND} searchmat(
    keytype x, matrix a,
    int imin, int imax,
    int jmin, int jmax,
    int *i, int *j)
{
    *i = imax;  *j = jmin;
    while (a[*i][*j] != x) {
        if (a[*i][*j] < x) (*j)++;  else (*i)--;
        if (*i < imin || *j > jmax) return NOT_FOUND;
    }
    return FOUND;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i, j, x;
    static matrix a = {{1, 2, 3, 4}, {2, 4, 6, 8}, {3, 6, 9, 12}};

    printf("    1  2  3  4\n"
           "A = 2  4  6  8  (i = 0, 1, 2; j = 0, 1, 2, 3)\n"
           "    3  6  9 12\n"
           "何を探しますか? ");
    scanf("%d", &x);
    if (searchmat(x, a, 0, 2, 0, 3, &i, &j) == FOUND)
        printf("(i, j) = (%d, %d)\n", i, j);
    else
        printf("見つかりません\n");
    return 0;
}
