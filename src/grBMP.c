/***********************************************************
    grBMP.c -- グラフィックス
***********************************************************/
#ifndef GRBMP_C
#define GRBMP_C

#include <stdio.h>

#define XMAX  640  /* 横ピクセル数 */
#define YMAX  400  /* 縦ピクセル数 */

#define BLACK 0x000000
#define WHITE 0xffffff
#define RED   0xff0000
#define GREEN 0x00ff00
#define BLUE  0x0000ff

long gr_screen[YMAX][XMAX];

void putbytes(FILE *f, int n, unsigned long x)  /* xの末尾からnバイト出力 */
{
    while (--n >= 0) {
        fputc(x & 255, f);  x >>= 8;
    }
}

void gr_dot(int x, int y, long color)  /* 点(x,y)を色colorで塗る */
{
    if (x >= 0 && x < XMAX && y >= 0 && y < YMAX)
        gr_screen[y][x] = color;
}

void gr_clear(long color)  /* 色 color でクリア */
{
    int x, y;

    for (x = 0; x < XMAX; x++)
        for (y = 0; y < YMAX; y++)
            gr_dot(x, y, color);
}    

void gr_BMP(char *filename)  /* BMPファイル出力 */
{
    int x, y;
    
    FILE *f = fopen(filename, "wb");
    fputs("BM", f);  /* ファイルタイプ */
    putbytes(f, 4, XMAX * YMAX * 4 + 54);  /* ファイルサイズ */
    putbytes(f, 4, 0);  /* 予約領域 */
    putbytes(f, 4, 54); /* ファイル先端から画像までのオフセット */
    putbytes(f, 4, 40); /* 情報ヘッダサイズ */
    putbytes(f, 4, XMAX);  /* 画像の幅 */
    putbytes(f, 4, YMAX);  /* 画像の高さ */
    putbytes(f, 2, 1);  /* プレーン数（1） */
    putbytes(f, 2, 32);  /* 色ビット数 */
    putbytes(f, 4, 0);  /* 圧縮形式（無圧縮） */
    putbytes(f, 4, XMAX * YMAX * 4);  /* 画像データサイズ */
    putbytes(f, 4, 3780);  /* 水平解像度（dot/m） */
    putbytes(f, 4, 3780);  /* 垂直解像度（dot/m） */
    putbytes(f, 4, 0);  /* 格納パレット数 */
    putbytes(f, 4, 0);  /* 重要色数 */
    for (y = 0; y < YMAX; y++)
        for (x = 0; x < XMAX; x++)
            putbytes(f, 4, gr_screen[y][x]);  /* 画像データ */
    fclose(f);
}

#endif  /* GRBMP_C */

#if 0  /* テスト */
int main(void)
{
    int x, y;

    for (x = 0; x < XMAX / 2; x++)
        for (y = 0; y < YMAX / 2; y++)
            gr_dot(x, y, GREEN);
    for (x = XMAX / 2; x < XMAX; x++)
        for (y = 0; y < YMAX / 2; y++)
            gr_dot(x, y, BLUE);
    for (x = 0; x < XMAX / 2; x++)
        for (y = YMAX / 2; y < YMAX; y++)
            gr_dot(x, y, RED);
    for (x = XMAX / 2; x < XMAX; x++)
        for (y = YMAX / 2; y < YMAX; y++)
            gr_dot(x, y, WHITE);
    gr_BMP("test.bmp");
    return 0;
}
#endif /* テスト */
