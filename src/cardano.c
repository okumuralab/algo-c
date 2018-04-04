/***********************************************************
    cardano.c -- 3次方程式
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI  3.14159265358979323846264  /* 円周率 */
#define CHECK

double cuberoot(double x)  /* $\sqrt[3]{x}$ */
{
    double s, prev;
    int pos;

    if (x == 0) return 0;
    if (x > 0) pos = 1;  else {  pos = 0;  x = -x;  }
    if (x > 1) s = x;  else s = 1;
    do {
        prev = s;  s = (x / (s * s) + 2 * s) / 3;
    } while (s < prev);
    if (pos) return prev;  else return -prev;
}

void cardano(double a, double b, double c, double d)
            /* $ax^3 + bx^2 + cx + d = 0$, $a \ne 0$ */
{
    double p, q, t, a3, b3, x1, x2, x3;

    b /= (3 * a);  c /= a;  d /= a;
    p = b * b - c / 3;
    q = (b * (c - 2 * b * b) - d) / 2;
    a = q * q - p * p * p;
    if (a == 0) {
        q = cuberoot(q);  x1 = 2 * q - b;  x2 = -q - b;
        printf("x = %g, %g (重解)\n", x1, x2);
#ifdef CHECK
        printf("f(x1) = %g\n", x1 * (x1 * (x1 + 3 * b) + c) + d);
        printf("f(x2) = %g\n", x2 * (x2 * (x2 + 3 * b) + c) + d);
#endif
    } else if (a > 0) {
        if (q > 0) a3 = cuberoot(q + sqrt(a));
        else       a3 = cuberoot(q - sqrt(a));
        b3 = p / a3;
        x1 = a3 + b3 - b;  x2 = -0.5 * (a3 + b3) - b;
        x3 = fabs(a3 - b3) * sqrt(3.0) / 2;
        printf("x = %g; %g +- %g i\n", x1, x2, x3);
#ifdef CHECK
        printf("f(x1) = %g\n", x1 * (x1 * (x1 + 3 * b) + c) + d);
        printf("f(x2+-x3i) = %g +- %g i\n",
            ((x2+3*b)*x2-x3*x3+c)*x2-(2*x2+3*b)*x3*x3+d,
            ((3*x2+6*b)*x2-x3*x3+c)*x3);
#endif
    } else {
        a = sqrt(p);  t = acos(q / (p * a));  a *= 2;
        x1 = a * cos( t           / 3) - b;
        x2 = a * cos((t + 2 * PI) / 3) - b;
        x3 = a * cos((t + 4 * PI) / 3) - b;
        printf("x = %g, %g, %g\n", x1, x2, x3);
#ifdef CHECK
        printf("f(x1) = %g\n", x1 * (x1 * (x1 + 3 * b) + c) + d);
        printf("f(x2) = %g\n", x2 * (x2 * (x2 + 3 * b) + c) + d);
        printf("f(x3) = %g\n", x3 * (x3 * (x3 + 3 * b) + c) + d);
#endif
    }
}

int main(void)
{
    double a, b, c, d;

    printf("a b c d = ");
    scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
    if (a == 0) {
        printf("3次方程式ではありません.\n");
        return 1;
    }
    cardano(a, b, c, d);
    return 0;
}
