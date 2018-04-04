/***********************************************************
    skanji.c -- シフトJISコード
***********************************************************/

void shift(int *ph, int *pl)  /* JISをシフトJISに */
{
    if (*ph & 1) {
        if (*pl < 0x60)  *pl += 0x1F;
        else             *pl += 0x20;
    } else               *pl += 0x7E;
    if (*ph < 0x5F)      *ph = (*ph + 0xE1) >> 1;
    else                 *ph = (*ph + 0x161) >> 1;
}

#include <stdio.h>
#include <stdlib.h>
#define ESC  0x1B  /* エスケープ文字 */

int main(void)
{
    int c, d;
    enum {FALSE, TRUE} jiskanji = FALSE;

    while ((c = getchar()) != EOF) {
        if (c == ESC) {
            if ((c = getchar()) == '$') {
                if ((c = getchar()) == '@' || c == 'B') {
                    jiskanji = TRUE;  /* JIS開始 */
                } else {
                    putchar(ESC);  putchar('$');
                    if (c != EOF) putchar(c);
                }
            } else if (c == '(') {
                if ((c = getchar()) == 'H' || c == 'J') {
                    jiskanji = FALSE;  /* JIS終了 */
                } else {
                    putchar(ESC);  putchar('(');
                    if (c != EOF) putchar(c);
                }
            } else if (c == 'K') {
                jiskanji = TRUE;   /* NECJIS開始 */
            } else if (c == 'H') {
                jiskanji = FALSE;  /* NECJIS終了 */
            } else {
                putchar(ESC);  if (c != EOF) putchar(c);
            }
        } else if (jiskanji && c >= 0x21 && c <= 0x7E) {
            if ((d = getchar()) >= 0x21 && d <= 0x7E)
                shift(&c, &d);
            putchar(c);  if (d != EOF) putchar(d);
        } else if (c >= 0xA1 && c <= 0xFE) {
            if ((d = getchar()) >= 0xA1 && d <= 0xFE) {
                d &= 0x7F;  c &= 0x7F;  shift(&c, &d);
            }
            putchar(c);  if (d != EOF) putchar(d);
        } else putchar(c);
    }
    return 0;
}
