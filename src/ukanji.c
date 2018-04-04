/***********************************************************
    ukanji.c -- シフトJISコード
***********************************************************/
#define iskanji(c) \
    ((c)>=0x81 && (c)<=0x9F || (c)>=0xE0 && (c)<=0xFC)
    /* シフトJIS 1バイト目 */
#define iskanji2(c) ((c)>=0x40 && (c)<=0xFC && (c)!=0x7F)
    /* シフトJIS 2バイト目 */

void jis(int *ph, int *pl)  /* シフトJISをJISに */
{
    if (*ph <= 0x9F) {
        if (*pl < 0x9F)  *ph = (*ph << 1) - 0xE1;
        else             *ph = (*ph << 1) - 0xE0;
    } else {
        if (*pl < 0x9F)  *ph = (*ph << 1) - 0x161;
        else             *ph = (*ph << 1) - 0x160;
    }
    if      (*pl < 0x7F) *pl -= 0x1F;
    else if (*pl < 0x9F) *pl -= 0x20;
    else                 *pl -= 0x7E;
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int c, d;

    while ((c = getchar()) != EOF) {
        if (iskanji(c)) {
            d = getchar();
            if (iskanji2(d)) {
                jis(&c, &d);
                putchar(c | 0x80);  putchar(d | 0x80);
            } else {
                putchar(c);
                if (d != EOF) putchar(d);
            }
        } else putchar(c);
    }
    return 0;
}
