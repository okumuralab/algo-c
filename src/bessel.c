/***********************************************************
    bessel.c -- Bessel (ベッセル) 関数
***********************************************************/
#include <stdio.h>
#include <math.h>

#define EPS      1e-10                /* 許容相対誤差 */
#define odd(x)   ((x) & 1)            /* 奇数? */
#define PI       3.14159265358979324  /* $\pi$ */
#define EULER    0.577215664901532861 /* Eulerの定数 $\gamma$ */

double BesJ(int n, double x)   /* $J_n(x)$ */
{
    int k;
    double a, b, r, s;
    const double x_2 = x / 2;

    if (x < 0) {
        if (odd(n)) return -BesJ(n, -x);
        /* else */  return  BesJ(n, -x);
    }
    if (n < 0) {
        if (odd(n)) return -BesJ(-n, x);
        /* else */  return  BesJ(-n, x);
    }
    if (x == 0) return (n == 0);
    a = s = 0;  b = 1;
    k = n;  if (k < x) k = x;
    do {  k++;  } while ((b *= x_2 / k) > EPS);
    if (odd(k)) k++;  /* 奇数なら偶数にする */
    while (k > 0) {
        s += b;
        a = 2 * k * b / x - a;  k--;  /* $a = J_k(x)$ */
        if (n == k) r = a;            /* $k$ 奇数 */
        b = 2 * k * a / x - b;  k--;  /* $b = J_k(x)$ */
        if (n == k) r = b;            /* $k$ 偶数 */
    }
    return r / (2 * s + b);
        /* $J_0 + 2(J_2 + J_4 + \cdots) = 1$ となるように規格化 */
}

#if 0  /***** 参考: 級数展開版 *****/

double BesJ2(int n, double x)  /* $J_n(x)$ */
{
    int k;
    double result, term, previous;

    if (x < 0) {
        if (odd(n)) return -BesJ2(n, -x);
        /* else */  return  BesJ2(n, -x);
    }
    if (n < 0) {
        if (odd(n)) return -BesJ2(-n, x);
        /* else */  return  BesJ2(-n, x);
    }
    x /= 2;  result = 1;
    for (k = 1; k <= n; k++) result *= x / k;
    x = - x * x;  term = result;
    for (k = 1; k < 500; k++) {
        term *= x / (k * (n + k));
        previous = result;  result += term;
        if (result == previous) return result;
    }
    printf("BesJ2(n, x): 収束しません.\n");
    return result;
}

#endif

double BesY(int n, double x)   /* $Y_n(x)$ */
{
    int k;
    double a, b, s, t, u;
    const double x_2 = x / 2;
    const double log_x_2 = log(x_2);

    if (x <= 0) {
        printf("BesY(n, x): x は正でなければなりません.\n");
        return 0;
    }
    if (n < 0) {
        if (odd(n)) return -BesY(-n, x);
        /* else */  return  BesY(-n, x);
    }
    k = x;  b = 1;
    do {  k++;  } while ((b *= x_2 / k) > EPS);
    if (odd(k)) k++;   /* 奇数なら偶数にする */
    a = 0;  /* $a = J_{k+1}(x) = 0$, $b = J_k(x)$, $k$ 偶数 */
    s = 0;  /* 規格化の因子 */
    t = 0;  /* $Y_0(x)$ */
    u = 0;  /* $Y_1(x)$ */
    while (k > 0) {
        s += b;  t = b / (k / 2) - t;
        a = 2 * k * b / x - a;  k--;  /* $a = J_k(x)$, $k$ 奇数 */
        if (k > 2) u = (k * a) / ((k / 2) * (k / 2 + 1)) - u;
        b = 2 * k * a / x - b;  k--;  /* $b = J_k(x)$, $k$ 偶数 */
    }
    s = 2 * s + b;
    a /= s;  b /= s;  t /= s;  u /= s;  /* $a = J_1(x)$, $b = J_0(x)$ */
    t = (2 / PI) * (2 * t + (log_x_2 + EULER) * b);  /* $Y_0(x)$ */
    if (n == 0) return t;
    u = (2 / PI) * (u + ((EULER - 1) + log_x_2) * a - b / x);  /* $Y_1(x)$ */
    for (k = 1; k < n; k++) {
        s = (2 * k) * u / x - t;  t = u;  u = s;
    }
    return u;
}

#include <stdlib.h>

int main(void)
{
    int x;

    printf(" x   %-13s %-13s %-13s %-13s\n",
        "J_0(x)", "J_1(x)", "J_2(x)", "J_3(x)");
    for (x = 0; x <= 20; x++)
            printf("%2d %13.10f %13.10f %13.10f %13.10f\n",
                x, BesJ(0, x), BesJ(1, x),
                   BesJ(2, x), BesJ(3, x));
    printf("\n x   %-13s %-13s %-13s %-13s\n",
        "Y_0(x)", "Y_1(x)", "Y_2(x)", "Y_3(x)");
    for (x = 1; x <= 20; x++)
            printf("%2d %13.10f %13.10f %13.10f %13.10f\n",
                x, BesY(0, x), BesY(1, x),
                   BesY(2, x), BesY(3, x));
    return 0;
}
