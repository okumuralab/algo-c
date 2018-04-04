/***********************************************************
    roundoff.c -- 四捨五入
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
unsigned round1000(unsigned long a, unsigned long b)
{                               /* $0 \le a \le b$, $b \ne 0$ */
    unsigned d;
    unsigned long bl, bh, rp, rm;

    if (a <= ULONG_MAX / 2000) {
        d = (unsigned)(a * 2000 / b);
    } else {
        bl = b % 2000; bh = b / 2000;
        d = (unsigned)(a / bh);
        rp = (a % bh) * 2000;  rm = bl * d;
        if (rp < rm) {
            d--;  rm -= rp;
            while (rm > b) {  d--;  rm -= b;  }
        }
    }
    return (d + 1) / 2;
}

int main(void)
{
    unsigned long a, b;
    unsigned r;

    printf("a = ");  scanf("%lu", &a);
    printf("b = ");  scanf("%lu", &b);
    r = round1000(a, b);
    printf("a / b = %u.%03u\n", r / 1000, r % 1000);
    return 0;
}
