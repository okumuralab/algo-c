/***********************************************************
    goldsect.c -- 黄金分割法
***********************************************************/
#include <math.h>

double goldsect(double a, double b,
                double tolerance, double (*f)(double x))
{
    const double r = 2 / (3 + sqrt(5));
    double c, d, fc, fd, t;

    if (a > b) {  t = a;  a = b;  b = t;  }
    t = r * (b - a);  c = a + t;  d = b - t;
    fc = f(c);  fd = f(d);
    for ( ; ; ) {
        if (fc > fd) {
            a = c;  c = d;  fc = fd;  d = b - r * (b - a);
            if (d - c <= tolerance) return c;
            fd = f(d);
        } else {
            b = d;  d = c;  fd = fc;  c = a + r * (b - a);
            if (d - c <= tolerance) return d;
            fc = f(c);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>
#define TEST  1

double func(double x)  /* 最小化する関数 */
{
    static int count = 0;
    const double xmin = 0.314;
    double value;

    value = (x - xmin) * (x - xmin);
    #if TEST
        printf("%4d:  f(%g) = %g\n", ++count, x, value);
    #endif
    return value;
}

int main(void)
{
    printf("x = %g\n", goldsect(0, 1, 1e-6, func));
    return 0;
}
