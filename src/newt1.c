/***********************************************************
    newt1.c -- Newton (ニュートン) 法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double b, c, d;

double f(double x)  /* $f(x) = 0$ を解く関数 $f(x)$ */
{
    return ((b + x) * x + c) * x + d;
}

double f_prime(double x)  /* $f(x)$ の導関数 */
{
    return (2 * b + 3 * x) * x + c;
}

double newton(double x)  /* 初期値 $x$ を与えて $f(x) = 0$ の解を返す */
{
    double fx, fp, xprev, xprev2 = x;

    do {
        fx = f(x);
        printf("  x = % -24.16g  f(x) = % -.2g\n", x, fx);
        if ((fp = f_prime(x)) == 0) fp = 1;  /* 強引にずらす */
        xprev2 = xprev;  xprev = x;  x -= fx / fp;
    } while (x != xprev && x != xprev2);  /* 振動の回避 */
    return (x + xprev) / 2;  /* 振動した場合は平均を返す */
}

int main(void)
{
    double a, x1, x2, x3;

    printf("ax^3+bx^2+cx+d=0を解きます。\na b c d ? ");
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
    b /= a;  c /= a;  d /= a;
    a = b * b - 3 * c;
    if (a > 0) {
        a = (2.0 / 3.0) * sqrt(a);
        x1 = newton(-a - b / 3);  /* 左側から */
        printf("x1 = %g\n", x1);
        x2 = newton(a - b / 3);   /* 右側から */
        if (x2 == x1) return 0;
        printf("x2 = %g\n", x2);
        x3 = newton(b / (-3));    /* 変曲点から */
        printf("x3 = %g\n", x3);
    } else {
        x1 = newton(0);           /* 適当な点から */
        printf("x = %g\n", x1);
    }
    return 0;
}
