/***********************************************************
    gf2fact.c -- 有限体
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
typedef unsigned int poly;        /* 多項式の型 */
poly quo, quo_low, res, res_low;  /* 商, 余り */
#define MSB (~(~0U >> 1))         /* 最上位ビット */
/*
  多項式を出力するルーチン.
  たとえば $x^3 + x + 1$ は {\tt 1011} と出力する.
*/
void write_poly(poly p, poly p_low)
{
    poly q;

    q = MSB;
    while (q >= p_low) {
        putchar((p & q) ? '1' : '0');
        q >>= 1;
    }
}
/*
  多項式の割り算のルーチン.
  多項式 {\tt a} を多項式 {\tt b} で割り, 商 {\tt quo},
  余り {\tt res} を求める.
  名前が {\TT \_low} で終わる変数は最下位ビットの位置を表す.
  割り切れるかどうかだけ分かればよいので余り {\tt res} は左寄せにしない.
  余りを左寄せにするにはこのルーチンの
  最後に \lq\lq {\TT res\_low} が {\tt MSB} で
  なければ {\TT res\_low} と {\tt res} を左に1桁シフトする'' という
  命令を入れる.
  ちなみに, 中ほどの \verb"res ^= b;" を \verb"res -= b;" とすると
  普通の (桁借りをする) 割り算になる.
*/
void divide(poly a, poly a_low, poly b, poly b_low)
{
    quo = 0;  quo_low = MSB;  res = a;  res_low = a_low;
    if (res_low > b_low) return;
    for ( ; ; ) {
        if (res & MSB) {
            quo |= quo_low;  res ^= b;
        }
        if (res_low == b_low) break;
        res_low <<= 1;  res <<= 1;  quo_low >>= 1;
    }
}
/*
  多項式 {\tt p} を因数分解するルーチン.
*/
void factorize(poly p, poly p_low)
{
    poly d, d_low;

    d = MSB;  d_low = MSB >> 1; /* 多項式 {\tt d} を $1x + 0$ に初期化 */
    while (d_low > p_low) {
        divide(p, p_low, d, d_low);  /* {\tt p} を {\tt d} で割る */
        if (res == 0) {  /* 割り切れれば\ldots\ */
            write_poly(d, d_low);  printf("*");  /* 因子 {\tt d} を出力 */
            p = quo;  p_low = quo_low;  /* 商をさらに割る */
        } else {  /* 割り切れなければ次の多項式 {\tt d} を試す */
            d += d_low;  /* 次の多項式 {\tt d} を生成する */
            if (d == 0) {
                d = MSB;  d_low >>= 1;
            }
        }
    }  /* {\tt d} の次数が {\tt p} の次数以上になったら脱出 */
    write_poly(p, p_low);  /* 残った多項式 {\tt p} を出力 */
}

int main(void)
{
    poly p, p_low;

    p = MSB;  p_low = MSB >> 1;    /* {\tt p} を $1x + 0$ に初期化 */
    while (p_low != 0) {
        write_poly(p, p_low);  printf(" = ");
        factorize(p, p_low);  printf("\n");  /* {\tt p} を因数分解 */
        p += p_low;            /* 次の多項式 {\tt p} を生成する */
        if (p == 0) {
            p = MSB;  p_low >>= 1;
        }
    }
    return 0;
}
