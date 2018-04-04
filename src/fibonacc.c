/***********************************************************
    fibonacc.c -- Fibonacci (フィボナッチ) 探索
***********************************************************/

double fibonacci(double a, double b,
                 double tolerance, double (*f)(double x))
{
    long int ic, id, ib, ia;
    double fc, fd, t;

    if (a > b) {  t = a;  a = b;  b = t;  }
    ia = (long int)((b - a) / tolerance);
    ic = 1;  id = 2;  ib = 3;
    while (ib < ia) {  ic = id;  id = ib;  ib = ic + id;  }
    ia = 0;  tolerance = (b - a) / ib;
    fc = f(a + ic * tolerance);  fd = f(a + id * tolerance);
    for ( ; ; ) {
        if (fc > fd) {
            ia = ic;  ic = id;  id = ib - (ic - ia);
            if (ic == id) return a + id * tolerance;
            fc = fd;  fd = f(a + id * tolerance);
        } else {
            ib = id;  id = ic;  ic = ia + (ib - id);
            if (ic == id) return a + ic * tolerance;
            fd = fc;  fc = f(a + ic * tolerance);
        }
    }
}

#include <stdio.h>
#include <stdlib.h>

double func(double x)
{
    static int count = 0;
    const double xmin = 0.314;
    double value;

    value = (x - xmin) * (x - xmin);
    printf("%4d:  f(%g) = %g\n", ++count, x, value);
    return value;
}

int main(void)
{
    printf("x = %g\n", fibonacci(0, 1, 1e-6, func));
    return 0;
}
