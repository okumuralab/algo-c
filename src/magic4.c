/***********************************************************
    magic4.c -- 魔方陣
***********************************************************/
/* 4次の魔方陣 */

#include <stdio.h>
#include <stdlib.h>
#define B(x) if (ok[x]) { ok[x]=0;
#define E(x) } ok[x]=1;
#define forall(x) for (x = 1; x <= 16; x++)
#define FORMAT \
    "%4d%4d%4d%4d\n%4d%4d%4d%4d\n%4d%4d%4d%4d\n%4d%4d%4d%4d\n"
int main(void)
{
    int a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p,
        x, count = 0,
        ok11[40], *ok = ok11 + 11;  /* ok[-11..28] */

    for (x = -11; x <= 0; x++) ok[x] = 0;
    for (x =  1; x <= 16; x++) ok[x] = 1;
    for (x = 17; x <= 28; x++) ok[x] = 0;
    forall(a) {  ok[a] = 0;
    for (d = a + 1; d <= 16; d++) {  ok[d] = 0;
    for (m = d + 1; m <= 16; m++) {  ok[m] = 0;
    p = 34 - a - d - m;
    if (ok[p] && a < p) {  ok[p] = 0;
    forall(b) B(b) c = 34 - a - b - d; B(c)
    forall(f) B(f) k = 34 - a - f - p; B(k)
    forall(g) B(g) j = 34 - d - g - m;
    B(j) n = 34 - b - f - j; B(n) o = 34 - c - g - k; B(o)
    forall(e) B(e) i = 34 - a - e - m;
    B(i) h = 34 - e - f - g; B(h) l = 34 - i - j - k;
    if (ok[l]) {
        printf("解 %d\n", ++count);
        printf(FORMAT, a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
        E(h) E(i) E(e) E(o) E(n) E(j) E(g) E(k)
        E(f) E(c) E(b) E(p) E(m) E(d) E(a)
    }
    return 0;
}
