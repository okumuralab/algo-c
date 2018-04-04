/***********************************************************
    koch.c -- Koch (コッホ) 曲線
***********************************************************/
#include "svgplot.c"  /* または epsplot.c */
#include <math.h>
#define PI 3.141592653589793
#define DMAX 3
unsigned int a;
double d;

void koch(void)
{
    if (d > DMAX) {
        d /= 3;  koch();  a++;  koch();
        a += 4;  koch();  a++;  koch();
        d *= 3;
    } else {
        draw_rel(d * cos((a % 6) * PI / 3), d * sin((a % 6) * PI / 3));
    }
}

int main(void)
{
    plot_start(400, 120);
    move(0, 0);  d = 400;  a = 0;  koch();
    plot_end(0);
    return 0;
}
