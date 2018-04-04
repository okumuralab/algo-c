/***********************************************************
    grj3.c -- グラフィックス
************************************************************
    グラフィックス基本ルーチン (J-3100, LSI C-86, far使用)
***********************************************************/
#ifndef GRJ3_C
#define GRJ3_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <string.h>  /* memset */
#include <dos.h>     /* union REGS, int86 */
#include <farstr.h>  /* LSI C-86 far functions */

#define XMAX  640U  /* 横ドット数 */
#define YMAX  400U  /* 縦ドット数 */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};
    /* 色コード (実際は BLACK 以外はすべて白) */

#define PLANE ((unsigned char far *)0xb8000000L)

static union REGS regs;  /* 8086レジスタ */
static unsigned int offset;  /* GVRAM のオフセット */

static int dgetc(void)  /* ctrl-C で止まらない1文字入力 */
{                       /* キーが押されていなければ0を返す */
    regs.h.ah = 6;  regs.h.dl = 0xff;
    int86(0x21, &regs, &regs);  /* DOS call */
    return regs.h.al;
}

void hitanykey(void)  /* キーを押すまで待つ */
{
    fputc('\a', stderr);    /* beep */
    while (dgetc() != 0) ;  /* flush key buffer */
    while (dgetc() == 0) ;  /* wait for any key */
}

void gr_dot(unsigned int x, unsigned int y,
            unsigned int color)  /* 点を表示 */
{
    static unsigned char
        count = 100,
        mask1[] = { 128, 64, 32, 16,  8,  4,  2,  1 },
        mask2[] = { 127,191,223,239,247,251,253,254 };

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(0);  /* ESC */
        count = 100;
    }
    if (x >= XMAX || y >= YMAX) return;
    if (color)
        PLANE[(((x >> 3) + (y >> 2) * 80 + offset) & 0x1FFF)
            + (y & 3) * 0x2000] |= mask1[x & 7];
    else
        PLANE[(((x >> 3) + (y >> 2) * 80 + offset) & 0x1FFF)
            + (y & 3) * 0x2000] &= mask2[x & 7];
}

void gr_off(void)  /* グラフィック画面クリア */
{
    far_memset(PLANE, 0, 0x8000);  /* グラフィック画面クリア */
    fputs("\x1b[>5l", stderr);  /* カーソル表示 */
}

void gr_on(void)  /* グラフィック画面初期化 */
{
    static int first = 1;

    if (first) {  atexit(gr_off);  first = 0;  }
    far_memset(PLANE, 0, 0x8000);  /* グラフィック画面クリア */
    /* 画面クリア, カーソル非表示, 最下行ユーザ使用 */
    fputs("\x1b[2J\x1b[>5h\x1b[>1h", stderr);
    regs.x.ax = 0x8300;
    int86(0x10, &regs, &regs);
    offset = regs.x.ax;
}

#endif  /* GRJ3_C */

#if 0  /* テスト */
int main(void)
{
    int i, j, k, c, d;

    gr_on();  d = 0;
    for (k = 0; k < 320; k += 20) {
        c = (k / 10) & 3;
        for (i = 0; i < 40; i++) {
            c ^= 1;
            for (j = 0; j < 40; j++) gr_dot(k + i, k + j, c);
        }
    }
    hitanykey();
    return 0;
}
#endif /* テスト */
