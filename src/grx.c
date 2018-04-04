/***********************************************************
    grx.c -- Basic Graphics Routines for X
***********************************************************/
#include <stdio.h>   /* fputc, fputs, stderr */
#include <stdlib.h>  /* exit, atexit */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "gr.h"

static unsigned char color_table[256];
static unsigned long pixels[8];

static Display *disp;
static Window win;
static Colormap cmap;
static GC gc;

void beep(void)  /* "beep" sound */
{
    fputc('\a', stderr);
}

int dgetc(void)  /* direct console input */
{
    /* difficult to implement in UNIX */
}

void hitanykey(void)  /* wait for any key */
{
    beep();
    while (dgetc() != 0) ;  /* flush key buffer */
    while (dgetc() == 0) ;  /* wait for any key */
}

void gr_dot(unsigned int x, unsigned int y, unsigned int color)
{
    static unsigned int sta_color = WHITE;

    if (sta_color != color) {
        sta_color = color;
        XSetForeground(disp, gc, pixels[sta_color]);
    }
    XDrawPoint(disp, win, gc, x, y);
}

void gr_off(void)  /* close window */
{
    XUnmapWindow(disp, win);
}

static void set_palette(int color,
     unsigned int r, unsigned int g, unsigned int b)
{
    XColor xc;

    xc.pixel = pixels[color];
    xc.red = 256 * r;
    xc.green = 256 * g;
    xc.blue = 256 * b;
    xc.flags = DoRed | DoGreen | DoBlue;
    XStoreColor(disp, cmap, &xc);
}

void gr_on(void)  /* open window, clear screen */
{
    static int not_first = 0;
    int i;
    unsigned long plane_mask[1];

    if (not_first) {
        XClearWindow(disp, win);
        return;
    }
    not_first = 1;
    disp = XOpenDisplay(NULL);
    win = XCreateSimpleWindow(disp, RootWindow(disp, 0), 0, 0,
            XMAX, YMAX, 1, 0, BlackPixel(disp, 0));
    cmap = DefaultColormap(disp, 0);
    XStoreName(disp, win, "grX");
    XAllocColorCells(disp, cmap, False, plane_mask, 0, pixels, 8);
    for (i = 0; i < 8; i++) color_table[pixels[i]] = i;
    gc = XCreateGC(disp, win, 0, NULL);
    XSetForeground(disp, gc, pixels[WHITE]);
    gc = XCreateGC(disp, win, 0, NULL);
    set_palette(BLACK,     0,   0,   0);
    set_palette(BLUE,      0,   0, 255);
    set_palette(RED,     255,   0,   0);
    set_palette(MAGENTA, 255,   0, 255);
    set_palette(GREEN,     0, 255,   0);
    set_palette(CYAN,      0, 255, 255);
    set_palette(YELLOW,  255, 255,   0);
    set_palette(WHITE,   255, 255, 255);
    XMapWindow(disp, win);
    XFlush(disp);
}
