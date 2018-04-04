/***********************************************************
    simplex.c -- 線形計画法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define EPS     1E-6    /* 無限小 */
#define LARGE   1E+30   /* 無限大 */
#define MMAX    20      /* 行 (条件) の数の上限 */
#define NMAX    100     /* 列 (変数) の数の上限 */

double a[MMAX + 1][NMAX + 1],    /* 条件式の係数 */
       c[NMAX + 1],              /* 目的関数の係数 */
       q[MMAX + 1][MMAX + 1],    /* 変換行列 */
       pivotcolumn[MMAX + 1];    /* ピボット列 */
int m, n,       /* 行 (条件), 列 (変数) の数 */
    n1,         /* {\tt n} $+$ 負のスラック変数の数 */
    n2,         /* {\tt n1} $+$ 正のスラック変数の数 */
    n3,         /* {\tt n2} $+$ 人為変数の数 */
    jmax,       /* 最右列の番号 */
    col[MMAX + 1],  /* 各行の基底変数の番号 */
    row[NMAX + 2*MMAX + 1],
                /* その列が基底なら対応する条件の番号, そうでなければ0 */
    nonzero_row[NMAX + 2*MMAX + 1]; /* スラック・人為変数の0でない行 */
char inequality[MMAX + 1];  /*  <, >, =  */

void error(char *message)  /* エラー表示, 終了 */
{
    fprintf(stderr, "\n%s\n", message);  exit(1);
}

double getnum(void)  /* 実数を標準入力から読む */
{
    int r;
    double x;

    while ((r = scanf("%lf", &x)) != 1) {
        if (r == EOF) error("入力エラー");
        scanf("%*[^\n]");  /* エラー回復のため行末まで読み飛ばす */
    }
    return x;
}

void readdata(void)  /* データを読む */
{
    int i, j;
    char s[2];

    m = (int)getnum();  n = (int)getnum();
    if (m < 1 || m > MMAX || n < 1 || n > NMAX)
        error("条件の数 m または変数の数 n が範囲外です");
    for (j = 1; j <= n; j++) c[j] = getnum();
    c[0] = -getnum();  /* {\tt c[0]}の符号を逆にする */
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) a[i][j] = getnum();
        if (scanf(" %1[><=]", s) != 1) error("入力エラー");
        inequality[i] = s[0];
        a[i][0] = getnum();
        if (a[i][0] < 0) {
            if      (inequality[i] == '>') inequality[i] = '<';
            else if (inequality[i] == '<') inequality[i] = '>';
            for (j = 0; j <= n; j++) a[i][j] = -a[i][j];
        } else if (a[i][0] == 0 && inequality[i] == '>') {
            inequality[i] = '<';
            for (j = 1; j <= n; j++) a[i][j] = -a[i][j];
        }
    }
}

void prepare(void)  /* 準備 */
{
    int i;

    n1 = n;
    for (i = 1; i <= m; i++)
        if (inequality[i] == '>') {  /* 係数が$-1$のスラック変数 */
            n1++;  nonzero_row[n1] = i;
        }
    n2 = n1;
    for (i = 1; i <= m; i++)
        if (inequality[i] == '<') {  /* 係数が$+1$のスラック変数 */
            n2++;  col[i] = n2;
            nonzero_row[n2] = row[n2] = i;
        }
    n3 = n2;
    for (i = 1; i <= m; i++)
        if (inequality[i] != '<') {  /* 人為変数 */
            n3++;  col[i] = n3;
            nonzero_row[n3] = row[n3] = i;
        }
    for (i = 0; i <= m; i++) q[i][i] = 1;
}

double tableau(int i, int j)
{
    int k;
    double s;

    if (col[i] < 0) return 0;  /* 消した行 */
    if (j <= n) {
        s = 0;
        for (k = 0; k <= m; k++) s += q[i][k] * a[k][j];
        return s;
    }
    s = q[i][nonzero_row[j]];
    if (j <= n1) return -s;
    if (j <= n2 || i != 0) return s;
    return s + 1;  /* j > n2 && i == 0 */
}

void writetableau(int ipivot, int jpivot)
    /* デモンストレーションのためシンプレックス表を出力 */
{
    int i, j;

    for (i = 0; i <= m; i++)
        if (col[i] >= 0) {
            printf("%2d: ", i);
            for (j = 0; j <= jmax; j++)
                printf("%7.2f%c", tableau(i, j),
                    (i == ipivot && j == jpivot) ? '*' : ' ');
            printf("\n");
        }
}

void pivot(int ipivot, int jpivot)  /* 掃き出し */
{
    int i, j;
    double u;

    printf("ピボット位置 (%d, %d)\n", ipivot, jpivot);
    u = pivotcolumn[ipivot];
    for (j = 1; j <= m; j++) q[ipivot][j] /= u;
    for (i = 0; i <= m; i++)
        if (i != ipivot) {
            u = pivotcolumn[i];
            for (j = 1; j <= m; j++)
                q[i][j] -= q[ipivot][j] * u;
        }
    row[col[ipivot]] = 0;
    col[ipivot] = jpivot;  row[jpivot] = ipivot;
}

void minimize(void)  /* 最小化 */
{
    int i, ipivot, jpivot;
    double t, u;

    for ( ; ; ) {
        /* ピボット列 jpivot を見つける */
        for (jpivot = 1; jpivot <= jmax; jpivot++)
            if (row[jpivot] == 0) {
                pivotcolumn[0] = tableau(0, jpivot);
                if (pivotcolumn[0] < -EPS) break;
            }
        if (jpivot > jmax) break;  /* 最小化完了 */
        /* ピボット行 ipivot を見つける */
        u = LARGE;  ipivot = 0;
        for (i = 1; i <= m; i++) {
            pivotcolumn[i] = tableau(i, jpivot);
            if (pivotcolumn[i] > EPS) {
                t = tableau(i, 0) / pivotcolumn[i];
                if (t < u) {  ipivot = i;  u = t;  }
            }
        }
        if (ipivot == 0) {
            printf("目的関数は下限がありません\n");
            exit(0);
        }
        writetableau(ipivot, jpivot);
        pivot(ipivot, jpivot);
    }
    writetableau(-1, -1);
    printf("最小値は %g です\n", -tableau(0, 0));
}

void phase1(void)  /* フェーズ１ */
{
    int i, j;
    double u;

    printf("フェーズ１\n");
    jmax = n3;
    for (i = 0; i <= m; i++)
        if (col[i] > n2) q[0][i] = -1;
    minimize();
    if (tableau(0, 0) < -EPS) {
        printf("可能な解はありません\n");
        exit(0);
    }
    for (i = 1; i <= m; i++)
        if (col[i] > n2) {
            printf("条件 %d は冗長です\n", i);
            col[i] = -1;
        }
    q[0][0] = 1;
    for (j = 1; j <= m; j++) q[0][j] = 0;
    for (i = 1; i <= m; i++)
        if ((j = col[i]) > 0 && j <= n && (u = c[j]) != 0)
            for (j = 1; j <= m; j++)
                q[0][j] -= q[i][j] * u;
}

void phase2(void)
{
    int j;

    printf("フェーズ２\n");  jmax = n2;
    for (j = 0; j <= n; j++) a[0][j] = c[j];  /* 目的関数 */
    minimize();
}

void report(void)  /* 結果の出力 */
{
    int i, j;

    printf("0 でない変数の値:\n");
    for (j = 1; j <= n; j++)
        if ((i = row[j]) != 0)
            printf("x[%d] = %g\n", j, tableau(i, 0));
}

int main(void)
{
    readdata();                 /* データを読む */
    prepare();                  /* 下ごしらえ */
    if (n3 != n2) phase1();     /* フェーズ1 */
    phase2();                   /* フェーズ2 */
    report();                   /* 結果の出力 */
    return 0;
}
