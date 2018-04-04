/***********************************************************
    utmult.c -- 行列の積
***********************************************************/
#include <stdio.h>

void matprint(int nrow, int ncol, double *a)
{
    int i, j;

    for (i = 0; i < nrow; i++) {
        for(j = 0; j < ncol; j++) printf("%8.1f", *a++);
        printf("\n");
    }
}

#define N 4
typedef double matrix[N][N];

void utmult(matrix a, matrix b)  /* 上三角行列の積 */
{
    int i, j, k;
    double s;

    for (i = N - 1; i >= 0; i--)
        for (j = N - 1; j >= i; j--) {
            s = 0;
            for (k = i; k <= j; k++) s += a[i][k] * b[k][j];
            a[i][j] = s;
        }
}

#include <stdlib.h>
int main(void)
{
    int i, j;
    static matrix a, b;

    for (i = 0; i < N; i++)
        for (j = i; j < N; j++) {
            a[i][j] = rand() / (RAND_MAX / 10 + 1) + 1;
            b[i][j] = rand() / (RAND_MAX / 10 + 1) + 1;
        }
    printf("A\n");  matprint(N, N, (double *)a);
    printf("B\n");  matprint(N, N, (double *)b);
    utmult(a, b);
    printf("AB\n");  matprint(N, N, (double *)a);
    return 0;
}
