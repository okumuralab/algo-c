/***********************************************************
    postfix.c -- 後置記法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int ch;

void readch(void)  /* １文字を読む. 空白は読み飛ばす. */
{
    do {
        if ((ch = getchar()) == EOF) return;
    } while (ch == ' ' || ch == '\t');
}

void expression(void);  /* 式 */

void factor(void)  /* 因子 */
{
    if (ch == '(') {
        readch();  expression();
        if (ch == ')') readch();  else putchar('?');
    } else if (isgraph(ch)) {
        putchar(ch);  readch();
    } else putchar('?');
}

void term(void) /* 項 */
{
    factor();
    for ( ; ; )
        if (ch == '*') {
            readch();  factor();  putchar('*');
        } else if (ch == '/') {
            readch();  factor();  putchar('/');
        } else break;
}

void expression(void)  /* 式 */
{
    term();
    for ( ; ; )
        if (ch == '+') {
            readch();  term();  putchar('+');
        } else if (ch == '-') {
            readch();  term();  putchar('-');
        } else break;
}

int main(void)
{
    do {
        readch();  expression();
        while (ch != '\n' && ch != EOF) {
            putchar('?');  readch();
        }
        putchar('\n');
    } while (ch != EOF);
    return 0;
}
