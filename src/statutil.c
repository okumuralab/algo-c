/***********************************************************
    statutil.c -- 多変量データ
***********************************************************/
#include "matutil.c"   /* 行列用の小道具集 */
#include <errno.h>     /* {\tt errno} */
#include <limits.h>    /* {\TT INT\_MAX} */
#include <math.h>      /* {\tt fabs()} */
#include <string.h>    /* {\tt strchr()} */

#define READERROR -1.00E+37;  /* 読込エラー */
#define MISSING   -0.98E+37;  /* 欠測値 */
#define readerror(x) ((x) < -0.99E+37)
#define missing(x)   ((x) < -0.97E+37)

double getnum(FILE *datafile)
{
    double x;
    char *rest, s[83];

    errno = 0;
    do {
        if (fscanf(datafile, "%81s%*[^ \t\n]", s) != 1)
            return READERROR;
    } while (strchr("0123456789+-.", s[0]) == NULL);
    if (s[0] == '.' && s[1] == '\0') return MISSING;
    s[81] = '?';  s[82] = '\0';  x = strtod(s, &rest);
    if (errno == 0 && *rest == '\0' && fabs(x) <= 0.97E+37)
        return x;
    return READERROR;
}

FILE *open_data(char *filename, int *addr_n, int *addr_m)
{
    FILE *datafile;
    double x, y;

    *addr_n = *addr_m = 0;
    if ((datafile = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "データファイルが開きません.\n");
        return NULL;
    }
    x = getnum(datafile);  y = getnum(datafile);
    if (x <= 0 || x > INT_MAX || y <= 0 || y > INT_MAX) {
        fprintf(stderr, "行数・列数が読めません.\n");
        fclose(datafile);  return NULL;
    }
    *addr_n = (int)x;  *addr_m = (int)y;
    fprintf(stderr, "%d 行 %d 列のデータです.\n",
        *addr_n, *addr_m);
    return datafile;
}

int read_data(FILE *datafile, int n, int m, matrix x)
{
    int i, j, err;
    unsigned long missings;
    double t;

    err = 0;  missings = 0;
    for (i = 0; i < n; i++) for (j = 0; j < m; j++) {
        if (err) {  x[j][i] = READERROR;  continue;  }
        t = getnum(datafile);  x[j][i] = (SCALAR)t;
        if (! missing(t)) continue;
        if (readerror(t)) {
            fprintf(stderr, "読込みエラー(%d,%d)\n", i+1, j+1);
            err = 2;
        } else missings++;
    }
    fprintf(stderr, "読込み終了 (欠測値 %lu 個)\n", missings);
    return err | (missings != 0);
}

#ifdef TEST  /* 以下は使用例 */

int main(void)
{
    int i, j, n, m;
    matrix x;  /* {\tt matrix} 型は {\tt matutil.c} で定義 */
    FILE *datafile;
    char filename[256];

    printf("データファイル名? ");
    scanf("%255s", filename);
    datafile = open_data(filename, &n, &m);     /* データファイルを開く */
    if (datafile == NULL) return 1;  /* 失敗 */
    x = new_matrix(m, n);                       /* 行列を生成 */
    read_data(datafile, n, m, x);               /* データを読む */
    fclose(datafile);
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            if (readerror(x[j][i]))    printf(" E");  /* 読込失敗 */
            else if (missing(x[j][i])) printf(" .");  /* 欠測値 */
            else             printf(" %g", x[j][i]);  /* 正常 */
        printf("\n");
    }
    return 0;
}

#endif  /* #ifdef TEST */
