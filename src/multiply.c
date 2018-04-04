/***********************************************************
    multiply.c -- 整数の積
***********************************************************/

unsigned int multiply(unsigned int a, unsigned int b)
{
    unsigned int c;

    c = 0;
    while (a != 0) {
        if (a & 1) c += b;
        b <<= 1;  a >>= 1;
    }
    return c;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    unsigned int x, y;

    printf("x = ");  scanf("%u", &x);
    printf("y = ");  scanf("%u", &y);
    printf("multiply(x, y) = %u\n", multiply(x, y));
    return 0;
}
