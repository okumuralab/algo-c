/***********************************************************
    complex.c -- 複素数
***********************************************************/
#include <stdio.h>  /* {\tt sprintf()} */
#include <math.h>

typedef struct {  double re, im;  } complex;  /* 複素数型 */

complex c_conv(double x, double y)  /* $x$, $y$ を複素数 $z = x + iy$ に変換 */
{
    complex z;

    z.re = x;  z.im = y;
    return z;
}

char *c_string(complex z)  /* 複素数 $z = x + iy$ を文字列に変換 */
{
    static char s[40];

    sprintf(s, "%g%+gi", z.re, z.im);
    return s;
}

complex c_conj(complex z)  /* 共役複素数 $\overline{z}$ */
{
    z.im = - z.im;
    return z;
}

double c_abs(complex z)  /* 絶対値 $|z|$ */
{
    double t;

    if (z.re == 0) return fabs(z.im);
    if (z.im == 0) return fabs(z.re);
    if (fabs(z.im) > fabs(z.re)) {
        t = z.re / z.im;
        return fabs(z.im) * sqrt(1 + t * t);
    } else {
        t = z.im / z.re;
        return fabs(z.re) * sqrt(1 + t * t);
    }
}

double c_arg(complex z)  /* 偏角 ($-\pi \le \varphi \le \pi$) */
{
    return atan2(z.im, z.re);
}

complex c_add(complex x, complex y)  /* 和 $x + y$ */
{
    x.re += y.re;
    x.im += y.im;
    return x;
}

complex c_sub(complex x, complex y)  /* 差 $x - y$ */
{
    x.re -= y.re;;
    x.im -= y.im;
    return x;
}

complex c_mul(complex x, complex y)  /* 積 $xy$ */
{
    complex z;

    z.re = x.re * y.re - x.im * y.im;
    z.im = x.re * y.im + x.im * y.re;
    return z;
}

#if 0
complex c_div(complex x, complex y)  /* 商 $x / y$ (単純版) */
{
    double r2;
    complex z;

    r2 = y.re * y.re + y.im * y.im;
    z.re = (x.re * y.re + x.im * y.im) / r2;
    z.im = (x.im * y.re - x.re * y.im) / r2;
    return z;
}
#endif

complex c_div(complex x, complex y)  /* 商 $x / y$ (上位桁あふれ対策版) */
{
    double w, d;
    complex z;

    if (fabs(y.re) >= fabs(y.im)) {
        w = y.im / y.re;  d = y.re + y.im * w;
        z.re = (x.re + x.im * w) / d;
        z.im = (x.im - x.re * w) / d;
    } else {
        w = y.re / y.im;  d = y.re * w + y.im;
        z.re = (x.re * w + x.im) / d;
        z.im = (x.im * w - x.re) / d;
    }
    return z;
}

complex c_exp(complex x)  /* 指数関数 $e^x$ */
{
    double a;

    a = exp(x.re);
    x.re = a * cos(x.im);
    x.im = a * sin(x.im);
    return x;
}

complex c_log(complex x)  /* 自然対数 $\log_e x$ */
{
    complex z;

    z.re = 0.5 * log(x.re * x.re + x.im * x.im);
    z.im = atan2(x.im, x.re);
    return z;
}

complex c_pow(complex x, complex y)  /* 累乗 $x^y$ */
{
    return c_exp(c_mul(y, c_log(x)));
}

complex c_sin(complex x)  /* 正弦 $\sin x$ */
{
    double e, f;

    e = exp(x.im);  f = 1 / e;
    x.im = 0.5 * cos(x.re) * (e - f);
    x.re = 0.5 * sin(x.re) * (e + f);
    return x;
}

complex c_cos(complex x)  /* 余弦 $\cos x$ */
{
    double e, f;

    e = exp(x.im);  f = 1 / e;
    x.im = 0.5 * sin(x.re) * (f - e);
    x.re = 0.5 * cos(x.re) * (f + e);
    return x;
}

complex c_tan(complex x)  /* 正接 $\tan x$ */
{
    double e, f, d;

    e = exp(2 * x.im);  f = 1 / e;
    d = cos(2 * x.re) + 0.5 * (e + f);
    x.re = sin(2 * x.re) / d;
    x.im = 0.5 * (e - f) / d;
    return x;
}

complex c_sinh(complex x)  /* 双曲線正弦 $\sinh x$ */
{
    double e, f;

    e = exp(x.re);  f = 1 / e;
    x.re = 0.5 * (e - f) * cos(x.im);
    x.im = 0.5 * (e + f) * sin(x.im);
    return x;
}

complex c_cosh(complex x)  /* 双曲線余弦 $\cosh x$ */
{
    double e, f;

    e = exp(x.re);  f = 1 / e;
    x.re = 0.5 * (e + f) * cos(x.im);
    x.im = 0.5 * (e - f) * sin(x.im);
    return x;
}

complex c_tanh(complex x)  /* 双曲線正接 $\tanh x$ */
{
    double e, f, d;

    e = exp(2 * x.re);  f = 1 / e;
    d = 0.5 * (e + f) + cos(2 * x.im);
    x.re = 0.5 * (e - f) / d;
    x.im = sin(2 * x.im) / d;
    return x;
}

#define SQRT05 0.707106781186547524  /* $\sqrt{0.5}$ */

complex c_sqrt(complex x)  /* 平方根 $\sqrt{x}$ */
{
    double r, w;

    r = c_abs(x);
    w = sqrt(r + fabs(x.re));
    if (x.re >= 0) {
        x.re = SQRT05 * w;
        x.im = SQRT05 * x.im / w;
    } else {
        x.re = SQRT05 * fabs(x.im) / w;
        x.im = (x.im >= 0) ? SQRT05 * w : -SQRT05 * w;
    }
    return x;
}

#include <stdlib.h>

int main(void)  /* テスト (ごく一部) */
{
    double x, y;
    complex z;

    printf("x, y ? ");  scanf("%lf%lf", &x, &y);
    z = c_conv(x, y);
    printf("z = %s\n", c_string(z));
    z = c_exp(z);
    printf("exp(z) = %s\n", c_string(z));
    z = c_log(z);
    printf("log(exp(z)) = %s\n", c_string(z));
    return 0;
}
