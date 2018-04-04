/***********************************************************
    gauss3.c -- 3重対角な連立方程式
***********************************************************/
#include "matutil.c"

void gauss3(int n, vector diag,
            vector sub, vector sup, vector b)
{
    int i;
    double t;

    for (i = 0; i < n - 1; i++) {  /* 消去法 */
        t = sub[i] / diag[i];
        diag[i + 1] -= t * sup[i];
        b   [i + 1] -= t * b  [i];
    }
    b[n - 1] /= diag[n - 1];       /* 後退代入 */
    for (i = n - 2; i >= 0; i--)
        b[i] = (b[i] - sup[i] * b[i + 1]) / diag[i];
}

int main(void)  /* テスト */
{
    int i, n;
    vector diag, sub, sup, b;

    printf("n = ");  scanf("%d", &n);
    if (n < 2) return 1;
    diag = new_vector(n);
    sub  = new_vector(n);
    sup  = new_vector(n);
    b    = new_vector(n);
    /* 例題.  正解はすべて 1 */
    for (i = 0; i < n; i++) {
        diag[i] = 4;  sub[i] = 1;  sup[i] = 2;  b[i] = 7;
    }
    b[0] = 6;  b[n - 1] = 5;
    gauss3(n, diag, sub, sup, b);
    vecprint(b, n, 8, "%9.6f");
    printf("正解はすべて 1\n");
    return 0;
}
