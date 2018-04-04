/***********************************************************
    grega.c -- グラフィックス
    Basic Graphics Routines for IBM PC (EGA)
***********************************************************/
#ifndef GREGA_C
#define GREGA_C

#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <dos.h>     /* union REGS, int86 */

#define XMAX  640U  /* columns */
#define YMAX  400U  /* rows */

/* EGA actual colors */
enum {EGA_BLACK, EGA_BLUE, EGA_GREEN, EGA_CYAN, EGA_RED,
      EGA_MAGENTA, EGA_LIGHTGRAY = 7, EGA_BROWN = 20,
      EGA_DARKGRAY = 56, EGA_LIGHTBLUE, EGA_LIGHTGREEN,
      EGA_LIGHTCYAN, EGA_LIGHTRED, EGA_LIGHTMAGENTA,
      EGA_YELLOW, EGA_WHITE };

/* color palettes */
enum {BLACK, BLUE, RED, MAGENTA, GREEN, CYAN, YELLOW, WHITE};

static union REGS regs;  /* 80x86 registers */

static int dgetc(void)  /* direct console input */
{
    regs.h.ah = 6;  regs.h.dl = 0xff;
    int86(0x21, &regs, &regs);  /* DOS call */
    return regs.h.al;
}

void hitanykey(void)  /* wait for any key */
{
    fputc('\a', stderr);    /* beep */
    while (dgetc() != 0) ;  /* flush key buffer */
    while (dgetc() == 0) ;  /* wait for any key */
}

void gr_dot(unsigned int x, unsigned int y,
            unsigned int color)
{
    static unsigned char count = 100;

    if (--count == 0) {
        if (dgetc() == 0x1b) exit(0);  /* ESC */
        count = 100;
    }
    if (x < XMAX && y < YMAX) {
        regs.h.ah = 0x0c;  /* write pixel */
        regs.h.al = color;
        regs.h.bh = 0;     /* display page number */
        regs.x.cx = x;
        regs.x.dx = (31 * y) / 40;
        int86(0x10, &regs, &regs);  /* BIOS call */
    }
}

void gr_off(void)  /* text mode */
{
    regs.x.ax = 0x0003;  /* 80 x 25 text mode */
    int86(0x10, &regs, &regs);  /* BIOS call */
}

void set_palette(int palette, int color)
{
    regs.x.ax = 0x1000;
    regs.h.bl = palette;
    regs.h.bh = color;
    int86(0x10, &regs, &regs);  /* BIOS call */
}

void gr_on(void)  /* graphics mode */
{
    static int first = 1;

    if (first) {  atexit(gr_off);  first = 0;  }
    regs.x.ax = 0x0010;  /* 640 x 350, 16 colors */
    int86(0x10, &regs, &regs);  /* BIOS call */
    set_palette(BLACK, EGA_BLACK);
    set_palette(BLUE, EGA_LIGHTBLUE);
    set_palette(RED, EGA_LIGHTRED);
    set_palette(MAGENTA, EGA_LIGHTMAGENTA);
    set_palette(GREEN, EGA_LIGHTGREEN);
    set_palette(CYAN, EGA_LIGHTCYAN);
    set_palette(YELLOW, EGA_YELLOW);
    set_palette(WHITE, EGA_WHITE);
}

#endif  /* GREGA_C */

#if 0  /* test */
int main(void)
{
    int i, j, k, c;

    gr_on();  k = 0;
    for (c = BLACK; c < WHITE; c++) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++)
                gr_dot(k + i, k + j, c);
        k += 20;
    }
    for (c = WHITE; c >= BLACK; c--) {
        for (i = 0; i < 40; i++)
            for (j = 0; j < 40; j++)
                gr_dot(k + i, k + j, c);
        k += 20;
    }
    hitanykey();
    return 0;
}
#endif /* test */
