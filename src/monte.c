/***********************************************************
    monte.c -- モンテカルロ法
***********************************************************/

/***** 一様乱数 (線形合同法) ******************************/

#include <limits.h>
static unsigned long seed = 1;

void init_rnd(unsigned long x)
{
    seed = x;
}

unsigned long irnd(void)
{
    seed = seed * 1566083941UL + 1;
    return seed;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    return (1.0 / (ULONG_MAX + 1.0)) * irnd();
}

/**********************************************************/

#include <stdio.h>
#include <math.h>

void monte1(int n)
{
    int i, hit;
    double x, y, p;

    hit = 0;
    for (i = 0; i < n; i++) {
        x = rnd();  y = rnd();
        if (x * x + y * y < 1) hit++;
    }
    p = (double) hit / n;
    printf("pi = %6.4f +- %6.4f\n",
        4 * p, 4 * sqrt(p * (1 - p) / (n - 1)));
}

void monte2(int n)
{
    int i;
    double x, y, sum, sumsq, mean, sd;

    sum = sumsq = 0;
    for (i = 0; i < n; i++) {
        x = rnd();
        y = sqrt(1 - x * x);
        sum += y;  sumsq += y * y;
    }
    mean = sum / n;
    sd = sqrt((sumsq / n - mean * mean) / (n - 1));
    printf("pi = %6.4f +- %6.4f\n", 4 * mean, 4 * sd);
}

void monte3(int n)
{
    int i;
    const double a = (sqrt(5) - 1) / 2;
    double x, sum;

    x = sum = 0;
    for (i = 0; i < n; i++) {
        if ((x += a) >= 1) x--;
        sum += sqrt(1 - x * x);
    }
    printf("pi = %6.4f\n", 4 * sum / n);
}

#include <stdlib.h>

int main(void)
{
    init_rnd(123456789UL);
    monte1(10000);

    init_rnd(123456789UL);
    monte2(10000);

    monte3(10000);

    return 0;
}
