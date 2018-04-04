/***********************************************************
    whrnd.c -- Wichmann--Hillの乱数発生法
***********************************************************/
static int ix = 1, iy = 1, iz = 1;  /* 1--30000の任意の整数 */

void init_rnd(int x, int y, int z)  /* x, y, z = 1..30000 */
{
    ix = x;  iy = y;  iz = z;
}

double rnd(void)  /* 0 <= rnd() < 1 */
{
    double r;

    ix = 171 * (ix % 177) -  2 * (ix / 177);
    iy = 172 * (iy % 176) - 35 * (iy / 176);
    iz = 170 * (iz % 178) - 63 * (iz / 178);
    if (ix < 0) ix += 30269;
    if (iy < 0) iy += 30307;
    if (iz < 0) iz += 30323;
    r = ix / 30269.0 + iy / 30307.0 + iz / 30323.0;
    while (r >= 1) r = r - 1;
    return r;
}

/**********************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;

    init_rnd(12345, 23451, 13579);  /* 1..30000 の任意の整数で初期化. */
    for (i = 0; i < 160; i++) printf("%10.7f", rnd());
    return 0;
}
