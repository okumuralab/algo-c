/***********************************************************
    arith.c -- 算術圧縮
***********************************************************/
#include "bitio.c"  /* \see\ Huffman法 */
#include <limits.h>
#ifdef max
    #undef max
#endif
#define max(x, y) ((x) > (y) ? (x) : (y))  /* 2数の最大値 */
#define N  256      /* 文字の種類 (文字コード{\tt = 0..N-1}) */
#define USHRT_BIT (CHAR_BIT * sizeof(unsigned short))
                    /* {\tt unsigned short} のビット数 */
#define Q1 (1U << (USHRT_BIT - 2))
#define Q2 (2U * Q1)
#define Q3 (3U * Q1)

unsigned cum[N + 1];  /* 累積度数 */
int ns;  /* 次の {\tt output()} で出力する補数のカウンタ */

static void output(int bit)  /* {\tt bit} に続いてその補数を {\tt ns} 個出力 */
{
    putbit(bit);  /* 1ビット書き出す */
    while (ns > 0) {  putbit(! bit);  ns--;  }  /* その補数を書き出す */
}

void encode(void)  /* 圧縮 */
{
    int c;
    unsigned long range, maxcount, incount, cr, d;
    unsigned short low, high;
    static unsigned long count[N];

    for (c = 0; c < N; c++) count[c] = 0;  /* 頻度の初期化 */
    while ((c = getc(infile)) != EOF) count[c]++;  /* 各文字の頻度 */
    incount = 0;  maxcount = 0;  /* 原文の大きさ, 頻度の最大値 */
    for (c = 0; c < N; c++) {
        incount += count[c];
        if (count[c] > maxcount) maxcount = count[c];
    }
    if (incount == 0) return;  /* 0バイトのファイル */
    /* 頻度合計が {\tt Q1} 未満, 各頻度が1バイトに収まるよう規格化 */
    d = max((maxcount + N - 2) / (N - 1),
            (incount + Q1 - 257) / (Q1 - 256));
    if (d != 1)
        for (c = 0; c < N; c++)
            count[c] = (count[c] + d - 1) / d;
    cum[0] = 0;
    for (c = 0; c < N; c++) {
        fputc((int)count[c], outfile);  /* 頻度表の出力 */
        cum[c + 1] = cum[c] + (unsigned)count[c];  /* 累積頻度 */
    }
    outcount = N;
    rewind(infile);  incount = 0;  /* 巻き戻して再走査 */
    low = 0;  high = USHRT_MAX;  ns = 0;
    while ((c = getc(infile)) != EOF) {  /* 各文字を符号化 */
        range = (unsigned long)(high - low) + 1;
        high = (unsigned short)
               (low + (range * cum[c + 1]) / cum[N] - 1);
        low  = (unsigned short)
               (low + (range * cum[c    ]) / cum[N]);
        for ( ; ; ) {
            if      (high < Q2) output(0);
            else if (low >= Q2) output(1);
            else if (low >= Q1 && high < Q3) {
                ns++;  low -= Q1;  high -= Q1;
            } else break;
            low <<= 1;  high = (high << 1) + 1;
        }
        if ((++incount & 1023) == 0) printf("%12lu\r", incount);
    }
    ns += 8;  /* 最後の7ビットはバッファフラッシュのため */
    if (low < Q1) output(0);  else output(1);  /* 01または10 */
    printf("In : %lu bytes\n", incount);  /* 原文の大きさ */
    printf("Out: %lu bytes (table: %d)\n", outcount, N);
    cr = (1000 * outcount + incount / 2) / incount;  /* 圧縮比 */
    printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
}

int binarysearch(unsigned x)  /* $\mbox{\tt cum[i]} \le x < \mbox{\tt cum[i+1]}$ となる {\tt i} を二分探索で求める */
{
    int i, j, k;

    i = 1;  j = N;
    while (i < j) {
        k = (i + j) / 2;
        if (cum[k] <= x) i = k + 1;  else j = k;
    }
    return i - 1;
}

void decode(unsigned long size)  /* 復元 */
{
    int c;
    unsigned char count[N];
    unsigned short low, high, value;
    unsigned long i, range;

    if (size == 0) return;  /* 0バイトのファイル */
    cum[0] = 0;
    for (c = 0; c < N; c++) {
        count[c] = fgetc(infile);  /* 頻度分布を読む */
        cum[c + 1] = cum[c] + count[c];  /* 累積頻度を求める */
    }
    value = 0;
    for (c = 0; c < USHRT_BIT; c++)
        value = 2 * value + getbit();  /* バッファを満たす */
    low = 0;  high = USHRT_MAX;
    for (i = 0; i < size; i++) {  /* 各文字を復元する */
        range = (unsigned long)(high - low) + 1;
        c = binarysearch((unsigned)((((unsigned long)
            (value - low) + 1) * cum[N] - 1) / range));
        high = (unsigned short)
               (low + (range * cum[c + 1]) / cum[N] - 1);
        low  = (unsigned short)
               (low + (range * cum[c    ]) / cum[N]);
        for ( ; ; ) {
            if      (high < Q2) { /* 何もしない */ }
            else if (low >= Q2) { /* 何もしない */ }
            else if (low >= Q1 && high < Q3) {
                value -= Q1;  low -= Q1;  high -= Q1;
            } else break;
            low <<= 1;  high = (high << 1) + 1;
            value = (value << 1) + getbit();  /* 1ビット読む */
        }
        putc(c, outfile);  /* 復元した文字を書き出す */
        if ((i & 1023) == 0) printf("%12lu\r", i);
    }
    printf("%12lu\n", size);  /* 原文のバイト数 */
}

int main(int argc, char *argv[])
{
    int c;
    unsigned long size;  /* 元のバイト数 */

    if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
                                && c != 'D' && c != 'd'))
        error("使用法は本文を参照してください");
    if ((infile  = fopen(argv[2], "rb")) == NULL)
        error("入力ファイルが開きません");
    if ((outfile = fopen(argv[3], "wb")) == NULL)
        error("出力ファイルが開きません");
    if (c == 'E' || c == 'e') {
        fseek(infile, 0L, SEEK_END);  /* infile の末尾を探す */
        size = ftell(infile);         /* infile のバイト数 */
        fwrite(&size, sizeof size, 1, outfile);
        rewind(infile);
        encode();       /* 圧縮 */
    } else {
        fread(&size, sizeof size, 1, infile);  /* 元のバイト数 */
        decode(size);   /* 復元 */
    }
    fclose(infile);  fclose(outfile);
    return 0;
}
