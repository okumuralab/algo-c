/***********************************************************
    matmult.c -- 行列の積
***********************************************************/
#define N 3
#define L 5
#define M 4

typedef double matNL[N][L];
typedef double matLM[L][M];
typedef double matNM[N][M];
void multiply(matNM c, matNL a, matLM b)
{
    int i, j, k;
    double s;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++) {
            s = 0;
            for (k = 0; k < L; k++) s += a[i][k] * b[k][j];
            c[i][j] = s;
        }
}

typedef double matNN[N][N];
void mult2(matNN a, matNN b)
{
    int i, j, k;
    double s, temp[N];

    for (i = 0; i < N; i++) {
        for (k = 0; k < N; k++) temp[k] = a[i][k];
        for (j = 0; j < N; j++) {
            s = 0;
            for (k = 0; k < N; k++) s += temp[k] * b[k][j];
            a[i][j] = s;
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

void matprint(int nrow, int ncol, double *a)
{
    int i, j;

    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) printf("%8.1f", *a++);
        printf("\n");
    }
}

int main(void)
{
    int i, j;
    static matNL a;
    static matLM b;
    static matNM c;
    static matNN d, e;

    for (i = 0; i < N; i++)
        for (j = 0; j < L; j++)
            a[i][j] = rand() / (RAND_MAX / 10 + 1);
    for (i = 0; i < L; i++)
        for (j = 0; j < M; j++)
            b[i][j] = rand() / (RAND_MAX / 10 + 1);
    printf("A\n");  matprint(N, L, (double *)a);
    printf("B\n");  matprint(L, M, (double *)b);
    multiply(c, a, b);
    printf("AB\n");  matprint(N, M, (double *)c);

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) {
            d[i][j] = rand() / (RAND_MAX / 10 + 1);
            e[i][j] = rand() / (RAND_MAX / 10 + 1);
        }
    printf("D\n");  matprint(N, N, (double *)d);
    printf("E\n");  matprint(N, N, (double *)e);
    mult2(d, e);
    printf("DE\n");  matprint(N, N, (double *)d);

    return 0;
}
