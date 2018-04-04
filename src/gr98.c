/***********************************************************
    gr98.c -- グラフィックス
************************************************************
    グラフィックス基本ルーチン (PC-9801)
    ラージモデル, コンパクトモデル, ヒュージモデルなど,
    データ用ポインタの幅が32ビットのモードでコンパイル
    してください.
***********************************************************/
#ifndef GR98_C
#define GR98_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <string.h>  /* memset */
#include <dos.h>     /* union REGS, int86 */

#define XMAX  640U  /* 横ドット数 */
#define YMAX  400U  /* 縦ドット数 */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};  /* 色コード */

#define PLANE1 ((unsigned char *)0xa8000000L) /* 青プレーン */
#define PLANE2 ((unsigned char *)0xb0000000L) /* 赤プレーン */
#define PLANE3 ((unsigned char *)0xb8000000L) /* 緑プレーン */

static union REGS regs;  /* 8086レジスタ */

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
    unsigned int i;
    unsigned char m1, m2;
    static unsigned char
        count = 100,
        mask1[] = { 128, 64, 32, 16,  8,  4,  2,  1 },
        mask2[] = { 127,191,223,239,247,251,253,254 };

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(0);  /* ESC */
        count = 100;
    }
    if (x >= XMAX || y >= YMAX) return;
    i = 80 * y + (x >> 3);
    m1 = mask1[x & 7];  m2 = mask2[x & 7];
    if (color & 1) PLANE1[i] |= m1;  else PLANE1[i] &= m2;
    if (color & 2) PLANE2[i] |= m1;  else PLANE2[i] &= m2;
    if (color & 4) PLANE3[i] |= m1;  else PLANE3[i] &= m2;
}

void gr_off(void)  /* グラフィック画面表示停止 */
{
    regs.h.ah = 0x41;
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
    fputs("\x1b[>5l", stderr);  /* カーソル表示 */
}

void gr_on(void)  /* グラフィック画面初期化・表示開始 */
{
    static int first = 1;

    if (first) {  atexit(gr_off);  first = 0;  }
    memset(PLANE1, 0, 32000);  /* グラフィック画面クリア */
    memset(PLANE2, 0, 32000);
    memset(PLANE3, 0, 32000);
    /* 画面クリア, カーソル非表示, 最下行ユーザ使用 */
    fputs("\x1b[2J\x1b[>5h\x1b[>1h", stderr);
    regs.h.ah = 0x42;  /* スクリーンモード設定 */
    regs.h.ch = 0xc0;  /* 640×400 カラーモード */
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
    regs.h.ah = 0x40;  /* グラフィック画面表示開始 */
    int86(0x18, &regs, &regs);  /* PC-9801 BIOS */
}

#endif  /* GR98_C */

#if 0  /* テスト */
int main(void)
{
    int i, j, k, c;

    gr_on();  k = 0;
    for (c = BLACK; c < WHITE; c++) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++) gr_dot(k + i, k + j, c);
        k += 20;
    }
    for (c = WHITE; c >= BLACK; c--) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++) gr_dot(k + i, k + j, c);
        k += 20;
    }
    hitanykey();
    return 0;
}
#endif /* テスト */
