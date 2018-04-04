/***********************************************************
    crc32.c -- CRC
***********************************************************/
#include <limits.h>
#define CRCPOLY1 0x04C11DB7UL
    /* x^{32}+x^{26}+x^{23}+x^{22}+x^{16}+x^{12}+x^{11]+
       x^{10}+x^8+x^7+x^5+x^4+x^2+x^1+1 */
#define CRCPOLY2 0xEDB88320UL  /* 左右逆転 */
typedef unsigned char byte;

unsigned long crc1(int n, byte c[])
{
    unsigned int i, j;
    unsigned long r;

    r = 0xFFFFFFFFUL;
    for (i = 0; i < n; i++) {
        r ^= (unsigned long)c[i] << (32 - CHAR_BIT);
        for (j = 0; j < CHAR_BIT; j++)
            if (r & 0x80000000UL) r = (r << 1) ^ CRCPOLY1;
            else                  r <<= 1;
    }
    return ~r & 0xFFFFFFFFUL;
}

unsigned long crc2(int n, byte c[])
{
    unsigned int i, j;
    unsigned long r;

    r = 0xFFFFFFFFUL;
    for (i = 0; i < n; i++) {
        r ^= c[i];
        for (j = 0; j < CHAR_BIT; j++)
            if (r & 1) r = (r >> 1) ^ CRCPOLY2;
            else       r >>= 1;
    }
    return r ^ 0xFFFFFFFFUL;
}

#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    static byte s[] = "Hello, world!";

    printf("crc1(%s) = %08lX\n", s, crc1(13, s));
    printf("crc2(%s) = %08lX\n", s, crc2(13, s));
    return 0;
}
