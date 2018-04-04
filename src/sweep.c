/***********************************************************
    sweep.c -- SWEEP演算子法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define SCALAR double   /* メモリ不足なら float に */
#include "statutil.c"   /* 多変量データ入力ルーチン */

int n, m, ndf;          /* データの件数, 変数の数, 自由度 */
char *added;            /* 説明変数に採用したか */
matrix a;               /* 積和行列 */

void sweep(int k)  /* 掃き出し演算 */
{
    int i, j;
    double b, d;

    if ((d = a[k][k]) == 0) {
        printf("変数 %d: 一次従属.\n", k);  return;
    }
    for (j = 0; j <= m; j++) a[k][j] /= d;
    for (j = 0; j <= m; j++) {
        if (j == k) continue;
        b = a[j][k];
        for (i = 0; i <= m; i++) a[j][i] -= b * a[k][i];
        a[j][k] = -b / d;
    }
    a[k][k] = 1 / d;
    if (added[k]) {  added[k] = 0;  ndf++;  }
    else          {  added[k] = 1;  ndf--;  }
}

void regress(int k)  /* 基準変数 k について回帰係数などを出力 */
{
    int j;
    double s, rms;

    if (added[k]) {  printf("???\n");  return;  }
    rms = (ndf > 0 && a[k][k] >= 0) ? sqrt(a[k][k] / ndf) : 0;
    printf("変数  回帰係数       標準誤差        t\n");
    for (j = 0; j <= m; j++) {
        if (! added[j]) continue;
        s = (a[j][j] >= 0) ? sqrt(a[j][j]) * rms : 0;
        printf("%4d  % #-14g % #-14g", j, a[j][k], s);
            if (s > 0) printf("  % #-11.3g", fabs(a[j][k] / s));
        printf("\n");
    }
    printf("基準変数: %d  残差2乗和: %g  自由度: %d  "
           "残差RMS: %g\n", k, a[k][k], ndf, rms);
}

void residuals(void)  /* 残差の積和行列を出力 */
{
    int i, j, k;

    for (i = 0; i <= m; i += 5) {
        for (k = i; k < i + 5 && k <= m; k++)
            printf("      %-8d", k);
        printf("\n");
        for (j = 0; j <= m; j++) {
            printf("%4d  ", j);
            for (k = i; k < i + 5 && k <= m; k++)
                printf("% -14g", a[j][k]);
            printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int i, j, k, c;
    FILE *datafile;
    vector x;

    printf("********** 対話型回帰分析 **********\n\n");
    if (argc != 2) error("使用法: reg datafile");
    datafile = fopen(argv[1], "r");
    if (datafile == NULL) error("ファイルが読めません.");
    n = ndf = getnum(datafile);  m = getnum(datafile);
    printf("%d 件 × %d 変数\n", n, m);
    if (n < 1 || m < 1) error("データ不良");
    if ((added = malloc(m + 1)) == NULL
     || (a = newmat(m + 1, m + 1)) == NULL
     || (x = newvec(m + 1)) == NULL) error("記憶領域不足");
    for (j = 0; j <= m; j++) {
        added[j] = 0;
        for (k = j; k <= m; k++) a[j][k] = 0;
    }
    for (i = 0; i < n; i++) {
        printf(".");  x[0] = 1;
        for (j = 1; j <= m; j++) {
            x[j] = getnum(datafile);
            if (missing(x[j])) error("データ不良");
        }
        for (j = 0; j <= m; j++)
            for (k = j; k <= m; k++) a[j][k] += x[j] * x[k];
    }
    printf("\n");  fclose(datafile);
    for (j = 0; j <= m; j++)
        for (k = 0; k < j; k++) a[j][k] = a[k][j];
    c = '\n';
    do {
        if (c == 'X' || c == 'Y')
            if (scanf("%d", &j) != 1 || j < 0 || j > m)
                c = '\0';
        switch (c) {
        case 'X':  sweep(j);  break;
        case 'Y':  regress(j);  break;
        case 'R':  residuals();  break;
        case '\n': printf("命令(Xj/Yj/R/Q)? ");
                   break;
        default:   printf("???\n");  break;
        }
    } while ((c = toupper(getchar())) != EOF && c != 'Q');
    return 0;
}
