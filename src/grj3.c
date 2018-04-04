/***********************************************************
    grj3.c -- グラフィックス
************************************************************
    グラフィックス基本ルーチン (J-3100)
    ラージモデル, コンパクトモデル, ヒュージモデルなど,
    データ用ポインタの幅が32ビットのモードでコンパイル
    してください.
***********************************************************/
#ifndef GRJ3_C
#define GRJ3_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <string.h>  /* memset */
#include <dos.h>     /* union REGS, int86 */

#define XMAX  640U  /* 横ドット数 */
#define YMAX  400U  /* 縦ドット数 */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};  /* 色コード */

#define PLANE ((unsigned char *)0xb8000000L)

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
            unsigned int color)  /* 点を表示 (colorはダミー) */
{
    static unsigned char
        count = 100,
        mask[] = { 128, 64, 32, 16,  8,  4,  2,  1 };

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(0);  /* ESC */
        count = 100;
    }
    if (x >= XMAX || y >= YMAX) return;
    PLANE[(((x >> 3) + (y >> 2) * 80 + offset) & 0x1FFF)
        + (y & 3) * 0x2000] |= mask[x & 7];
}

void gr_off(void)  /* グラフィック画面クリア */
{
    memset(PLANE, 0, 0x8000);
}

void gr_on(void)  /* グラフィック画面初期化 */
{
    static int first = 1;

    if (first) {
        atexit(gr_off);
        regs.x.ax = 0x8300;
        int86(0x10, &regs, &regs);
        offset = regs.x.ax;
        first = 0;
    }
    gr_off();                  /* グラフィック画面クリア */
    fputs("\x1b[2J", stderr);  /* テキスト画面クリア */
}

#endif  /* GRJ3_C */

#if 0  /* テスト */
int main(void)
{
    int i, j;

    gr_on();
    for (j = 0; j < 400; j++)
        for (i = 0; i < 640; i++)
            gr_dot(i, j, 1);
    hitanykey();
    return 0;
}
#endif /* テスト */
