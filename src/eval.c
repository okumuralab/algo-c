/***********************************************************
    eval.c -- 式の評価
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int ch;

void error(char *s)  /* エラー処理 */
{
    printf("%s\n", s);  exit(1);
}

void readch(void)  /* 1文字を読む. 空白は読み飛ばす. */
{
    do {
        if ((ch = getchar()) == EOF) return;
    } while (ch == ' ' || ch == '\t');
}

double number(void)  /* 数 */
{
    double x, a;
    int sign = '+';

    if (ch == '+' || ch == '-') {
        sign = ch;  readch();
    }
    if (! isdigit(ch)) error("数か '(' がありません");
    x = ch - '0';
    while (readch(), isdigit(ch))
        x = 10 * x + ch - '0';
    if (ch == '.') {
        a = 1;
        while (readch(), isdigit(ch))
            x += (a /= 10) * (ch - '0');
    }
    if (sign == '-') return -x;  else return x;
}

double expression(void);  /* 式 */

double factor(void)  /* 因子 */
{
    double x;

    if (ch != '(') return number();
    readch();  x = expression();
    if (ch != ')') error("')' がありません");
    readch();  return x;
}

double term(void)  /* 項 */
{
    double x, y;

    x = factor();
    for ( ; ; )
        if (ch == '*') {
            readch();  x *= factor();
        } else if (ch == '/') {
            readch();  y = factor();
            if (y == 0) error("0 では割れません");
            x /= y;
        } else break;
    return x;
}

double expression(void)  /* 式 */
{
    double x;

    x = term();
    for ( ; ; )
        if (ch == '+') {
            readch();  x += term();
        } else if (ch == '-') {
            readch();  x -= term();
        } else break;
    return x;
}

int main(void)
{
    double x;

    readch();  x = expression();
    if (ch != '\n') error("文法の間違いがあります");
    printf("%g\n", x);
    return 0;
}
