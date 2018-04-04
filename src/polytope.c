/***********************************************************
    polytope.c -- ポリトープ法
***********************************************************/
/*
  最小化する関数
*/
#define N 11  /* number of data points */
double x[N] = {-10, -8, -6, -4, -2, 0, 2, 4, 6, 8, 10};
double y[N] = {
    2.127, 2.520, 2.629, 2.938, 3.414, 4.669,
    8.014, 6.372, 4.596, 4.296, 4.291
};
double func(double parameter[])
{
    int i;
    double f, g2, dx, d;

    f = 0.0;  g2 = parameter[1] * parameter[1];
    for (i = 0; i < N; i++) {
        dx = x[i] - parameter[0];
        d = parameter[2] * g2 / (dx * dx + g2)
            + parameter[3] + parameter[4] * x[i] - y[i];
        f += d * d;
    }
    return f;
}
/*
  最小化
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define M 5           /* number of parameters  */
#define MAXITER 1000  /* max number of iterations */
#define ALPHA 1.0     /* reflection coefficient  */
#define BETA  2.0     /* expansion coefficient   */
#define GAMMA 0.5     /* contraction coefficient */

double vertex[M + 1][M] = {0.0, 1.0, 6.0, 3.5, 0.2};
double scalefactor[M] = {1.0, 1.0, 1.0, 1.0, 0.1};
double tolerance[M] = {0.001, 0.001, 0.001, 0.001, 0.001};

void initialize_vertices(void)
{
    int j, k;
    const double c = 1 / (sqrt(M + 1) + 2);
    double t;

    for (j = 0; j < M; j++) {
        t = vertex[0][j] + c * scalefactor[j];
        for (k = 1; k <= M; k++) vertex[k][j] = t;
        vertex[j + 1][j] = vertex[0][j] + scalefactor[j];
    }
}

int main(void)
{
    int j, k, iter, kbest, kworst1, kworst2;
    double x, fnew, *vbest, *vworst;
    static double f[M + 1];  /* func values at vertices */
    static double vcenter[M], vnew[M];

    initialize_vertices();
    kbest = kworst1 = 0;  kworst2 = 1;
    f[0] = func(vertex[0]);
    for (k = 1; k <= M; k++) {
        f[k] = func(vertex[k]);
        if (f[k] < f[kbest]) kbest = k;
        else if (f[k] >= f[kworst1]) {
            kworst2 = kworst1;  kworst1 = k;
        } else if (f[k] >= f[kworst2]) kworst2 = k;
    }
    vbest = vertex[kbest];  vworst = vertex[kworst1];
    printf("iter   value\n");
    printf("    1  %-14g", f[kbest]);
    iter = 1;
    while (f[kbest] != f[kworst1]) {
        for (j = 0; j < M; j++)
            if (fabs(vbest[j] - vworst[j]) > tolerance[j])
                break;
        if (j == M) break;
        if (++iter > MAXITER) {
            printf("\n収束しません\n");  break;
        }
        for (j = 0; j < M; j++) {
            x = 0.0;
            for (k = 0; k <= M; k++)
                if (k != kworst1) x += vertex[k][j];
            vcenter[j] = x / M;
            vnew[j] = vcenter[j] +
                ALPHA * (vcenter[j] - vworst[j]);
        }
        fnew = func(vnew);
        if (fnew < f[kbest]) {
            /* vnew is the new best point */
            for (j = 0; j < M; j++)
                vworst[j] = vcenter[j] +
                    BETA * (vnew[j] - vcenter[j]);
            f[kworst1] = func(vworst);
            if (f[kworst1] >= fnew) {
                printf("R");  /* reflection */
                for (j = 0; j < M; j++) vworst[j] = vnew[j];
                f[kworst1] = fnew;
            } else printf("E");  /* expansion */
            kbest = kworst1;  vbest = vworst;
            printf("\n%5d  %-14g", iter, f[kbest]);
            kworst1 = kworst2;  vworst = vertex[kworst1];
            kworst2 = kbest;
            for (k = 0; k <= M; k++)
                if (k != kworst1 && f[k] > f[kworst2])
                    kworst2 = k;
        } else if (fnew <= f[kworst2]) {
            /* vnew is not the new worst point */
            printf("R");  /* reflection */
            for (j = 0; j < M; j++) vworst[j] = vnew[j];
            f[kworst1] = fnew;
            kworst1 = kworst2;  vworst = vertex[kworst1];
            kworst2 = kbest;
            for (k = 0; k <= M; k++)
                if (k != kworst1 && f[k] > f[kworst2])
                    kworst2 = k;
        } else {
            if (fnew < f[kworst1]) {
                for (j = 0; j < M; j++)
                    vworst[j] = vnew[j];
                f[kworst1] = fnew;
            }
            do {
                printf("C");  /* contraction */
                for (j = 0; j < M; j++)
                    vworst[j] += (1 - GAMMA) *
                        (vbest[j] - vworst[j]);
                fnew = func(vworst);
            } while (fnew >= f[kworst1]);
            f[kworst1] = fnew;
            if (fnew < f[kbest]) {
                kbest = kworst1;  f[kbest] = fnew;
                vbest = vworst;
                printf("\n%5d  %-14g", iter, fnew);
            }
            if (fnew < f[kworst2]) {
                kworst1 = kworst2;
                vworst = vertex[kworst1];
                kworst2 = kbest;
                for (k = 0; k <= M; k++)
                    if (k != kworst1 && f[k] > f[kworst2])
                        kworst2 = k;
            }
        }
    }
    printf("\n\niterations: %d\n", iter);
    printf("minimum value: %g\n", f[kbest]);
    printf("parameters:\n");
    for (j = 0; j < M; j++)
        printf("%5d  %g\n", j, vbest[j]);
    return 0;
}
