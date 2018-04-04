/***********************************************************
    crc32t.c -- CRC
***********************************************************/
#include <limits.h>
#define CRCPOLY1 0x04C11DB7UL
    /* x^{32}+x^{26}+x^{23}+x^{22}+x^{16}+x^{12}+x^{11]+
       x^{10}+x^8+x^7+x^5+x^4+x^2+x^1+1 */
#define CRCPOLY2 0xEDB88320UL  /* 左右逆転 */
typedef unsigned char byte;
unsigned long crctable[UCHAR_MAX + 1];

void makecrctable1(void)
{
    unsigned int i, j;
    unsigned long r;

    for (i = 0; i <= UCHAR_MAX; i++) {
        r = (unsigned long)i << (32 - CHAR_BIT);
        for (j = 0; j < CHAR_BIT; j++)
            if (r & 0x80000000UL) r = (r << 1) ^ CRCPOLY1;
            else                  r <<= 1;
        crctable[i] = r & 0xFFFFFFFFUL;
    }
}

unsigned long crc1(int n, byte c[])
{
    unsigned long r;

    r = 0xFFFFFFFFUL;
    while (--n >= 0)
        r = (r << CHAR_BIT) ^ crctable[(byte)(r >> (32 - CHAR_BIT)) ^ *c++];
    return ~r & 0xFFFFFFFFUL;
}

void makecrctable2(void)
{
    unsigned int i, j;
    unsigned long r;

    for (i = 0; i <= UCHAR_MAX; i++) {
        r = i;
        for (j = 0; j < CHAR_BIT; j++)
            if (r & 1) r = (r >> 1) ^ CRCPOLY2;
            else       r >>= 1;
        crctable[i] = r;
    }
}

unsigned long crc2(int n, byte c[])
{
    unsigned long r;

    r = 0xFFFFFFFFUL;
    while (--n >= 0)
        r = (r >> CHAR_BIT) ^ crctable[(byte)r ^ *c++];
    return r ^ 0xFFFFFFFFUL;
}

#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    static byte s[] = "Hello, world!";

    makecrctable1();
    printf("crc1(%s) = %08lX\n", s, crc1(13, s));
    makecrctable2();
    printf("crc2(%s) = %08lX\n", s, crc2(13, s));
    return 0;
}
