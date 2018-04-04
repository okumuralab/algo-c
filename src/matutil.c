/***********************************************************
    matutil.c -- 行列
***********************************************************/
/* 行列操作の小道具集 */

#ifndef MATUTIL
#define MATUTIL

#include <stdio.h>
#include <stdlib.h>
#ifndef SCALAR
    #define SCALAR double
#endif
typedef SCALAR *vector, **matrix;

void error(char *message)
{
    fprintf(stderr, "\n%s\n", message);  exit(1);
}

vector newvec(int n)
{
    return malloc(sizeof(SCALAR) * n);
}

matrix newmat(int nrow, int ncol)
{
    int i;
    matrix a;

    a = malloc((nrow + 1) * sizeof(void *));
    if (a == NULL) return NULL;  /* 記憶領域不足 */
    for (i = 0; i < nrow; i++) {
        a[i] = malloc(sizeof(SCALAR) * ncol);
        if (a[i] == NULL) {
            while (--i >= 0) free(a[i]);
            free(a);  return NULL;  /* 記憶領域不足 */
        }
    }
    a[nrow] = NULL;  /* 行の数を自動判断するための工夫 */
    return a;
}

vector new_vector(int n)
{
    vector v;

    v = newvec(n);
    if (v == NULL) error("記憶領域不足.");
    return v;
}

matrix new_matrix(int nrow, int ncol)
{
    matrix a;

    a = newmat(nrow, ncol);
    if (a == NULL) error("記憶領域不足.");
    return a;
}

void free_vector(vector v)
{
    free(v);
}

void free_matrix(matrix a)
{
    matrix b;

    b = a;
    while (*b != NULL) free(*b++);
    free(a);
}

double innerproduct(int n, vector u, vector v)
{
    int i, n5;
    double s;

    s = 0;  n5 = n % 5;
    for (i = 0; i < n5; i++) s += u[i]*v[i];
    for (i = n5; i < n; i += 5)
        s += u[i]*v[i] + u[i+1]*v[i+1] + u[i+2]*v[i+2]
                       + u[i+3]*v[i+3] + u[i+4]*v[i+4];
    return s;
}

void vecprint(vector v, int n, int perline, char *format)
{
    int j, k;

    k = 0;
    for (j = 0; j < n; j++) {
        printf(format, v[j]);
        if (++k >= perline) {  k = 0;  printf("\n");  }
    }
    if (k != 0) printf("\n");
}

void matprint(matrix a, int ncol, int perline, char *format)
{
    int i;

    for (i = 0; a[i] != NULL; i++) {
        vecprint(a[i], ncol, perline, format);
        if (ncol > perline) printf("\n");
    }
}

#if 0    /******** 以下は簡単な使用例 ********/
#include <time.h>
int main(void)
{
    int i, j, nrow, ncol;
    matrix a;

    srand((unsigned int) time(NULL));  /* 乱数の種を設定 */
    nrow = rand() % 10 + 1;            /* 行の数 */
    ncol = rand() % 10 + 1;            /* 列の数 */
    a = new_matrix(nrow, ncol);        /* 行列を作る */
    for (i = 0; i < nrow; i++)         /* 乱数を代入 */
        for (j = 0; j < ncol; j++)
            a[i][j] = 10.0 * rand() / RAND_MAX;
    printf("%d × %d 行列:\n", nrow, ncol);
    matprint(a, ncol, 4, "  % -14g");    /* 出力 */
    return 0;
}
#endif
#endif  /* 最初の #ifndef ... に対応する */
