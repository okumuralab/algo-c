/***********************************************************
    stemleaf.c -- 幹葉表示
***********************************************************/
#include "statutil.c"
#define MAXLINES  60

void stem_and_leaf(int n, vector x)
{
    int h, i, j, k, kmin, kmax;
    static int histo[10 * MAXLINES];
    double xmin, xmax, factor;

    xmin = xmax = x[0];
    for (i = 1; i < n; i++)
        if      (x[i] < xmin) xmin = x[i];
        else if (x[i] > xmax) xmax = x[i];
    factor = 1;
    while (factor * xmax > 32767 || factor * xmin < -32767)
        factor /= 10;
    for ( ; ; ) {
        kmin = (int)(factor * xmin) / 10 - (xmin < 0);
        kmax = (int)(factor * xmax) / 10;
        if (kmax - kmin + 1 <= MAXLINES) break;
        factor /= 10;
    }
    printf("10 * 幹 + 葉 = %.1g * データ\n", factor);
    for (k = 0; k < 10 * MAXLINES; k++) histo[k] = 0;
    for (i = 0; i < n; i++)
        histo[(int)(factor * x[i]) - (x[i] < 0) - 10 * kmin]++;
    if (kmin < 0 && kmax > 0) {
        k = 0;
        for (i = 0; i < n; i++) if (x[i] == 0) k++;
        histo[-10 * kmin    ] -= k / 2;
        histo[-10 * kmin - 1] += k / 2;
    }
    for (k = kmin; k <= kmax; k++) {
        if (k != -1) printf("%5d | ", k + (k < 0));
        else         printf("   -0 | ");
        for (j = 0; j <= 9; j++) {
            if (k >= 0) h = histo[10 * (k - kmin) + j];
            else h = histo[10 * (k - kmin) + 9 - j];
            for (i = 0; i < h; i++) printf("%d", j);
        }
        printf("\n");
    }
}

#define NMAX  5000

int main(void)
{
    int n;
    double t;
    static double x[NMAX];

    n = 0;
    while (! readerror(t = getnum(stdin)))
        if (missing(t)) continue;
        else if (n >= NMAX) error("多すぎます");
        else x[n++] = t;
    stem_and_leaf(n, x);
    return 0;
}
