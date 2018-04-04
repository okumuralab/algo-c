/***********************************************************
    huffman.c -- Huffman (ハフマン) 法
***********************************************************/
#include "bitio.c"              /* ビット入出力 */

#define N       256             /* 文字の種類 */
#define CHARBITS  8             /* 1バイトのビット数 */
int heapsize, heap[2*N-1],      /* 優先待ち行列用ヒープ */
    parent[2*N-1], left[2*N-1], right[2*N-1];  /* Huffman木 */
unsigned long int freq[2*N-1];  /* 各文字の出現頻度 */

static void downheap(int i)  /* 優先待ち行列に挿入 */
{
    int j, k;

    k = heap[i];
    while ((j = 2 * i) <= heapsize) {
        if (j < heapsize && freq[heap[j]] > freq[heap[j + 1]])
            j++;
        if (freq[k] <= freq[heap[j]]) break;
        heap[i] = heap[j];  i = j;
    }
    heap[i] = k;
}

void writetree(int i)  /* 枝を出力 */
{
    if (i < N) {  /* 葉 */
        putbit(0);
        putbits(CHARBITS, i);  /* 文字そのもの */
    } else {      /* 節 */
        putbit(1);
        writetree(left[i]);  writetree(right[i]);  /* 左右の枝 */
    }
}

void encode(void)  /* 圧縮 */
{
    int i, j, k, avail, tablesize;
    unsigned long int incount, cr;
    static char codebit[N];  /* 符号語 */

    for (i = 0; i < N; i++) freq[i] = 0;  /* 頻度の初期化 */
    while ((i = getc(infile)) != EOF) freq[i]++;  /* 頻度数え */
    heap[1] = 0;  /* 長さ0のファイルに備える */
    heapsize = 0;
    for (i = 0; i < N; i++)
        if (freq[i] != 0) heap[++heapsize] = i;  /* 優先待ち行列に登録 */
    for (i = heapsize / 2; i >= 1; i--) downheap(i);  /* ヒープ作り */
    for (i = 0; i < 2 * N - 1; i++) parent[i] = 0;  /* 念のため */
    k = heap[1];  /* 以下のループが1回も実行されない場合に備える */
    avail = N;  /* 以下のループでハフマン木を作る */
    while (heapsize > 1) {  /* 2個以上残りがある間 */
        i = heap[1];  /* 最小の要素を取り出す */
        heap[1] = heap[heapsize--];  downheap(1);  /* ヒープ再構成 */
        j = heap[1];  /* 次に最小の要素を取り出す */
        k = avail++;  /* 新しい節を生成する */
        freq[k] = freq[i] + freq[j];  /* 頻度を合計 */
        heap[1] = k;  downheap(1);  /* 待ち行列に登録 */
        parent[i] = k;  parent[j] = -k;  /* 木を作る */
        left[k] = i;  right[k] = j;      /* 〃 */
    }
    writetree(k);  /* 木を出力 */
    tablesize = (int) outcount;  /* 表の大きさ */
    incount = 0;  rewind(infile);  /* 再走査 */
    while ((j = getc(infile)) != EOF) {
        k = 0;
        while ((j = parent[j]) != 0)
            if (j > 0) codebit[k++] = 0;
            else {     codebit[k++] = 1;  j = -j;  }
        while (--k >= 0) putbit(codebit[k]);
        if ((++incount & 1023) == 0)
            printf("%12lu\r", incount);  /* 状況報告 */
    }
    putbits(7, 0);  /* バッファの残りをフラッシュ */
    printf("In : %lu bytes\n", incount);  /* 結果報告 */
    printf("Out: %lu bytes (table: %d bytes)\n",
        outcount, tablesize);
    if (incount != 0) {  /* 圧縮比を求めて報告 */
        cr = (1000 * outcount + incount / 2) / incount;
        printf("Out/In: %lu.%03lu\n", cr / 1000, cr % 1000);
    }
}

int readtree(void)  /* 木を読む */
{
    int i;
    static int avail = N;

    if (getbit()) {  /* bit=1: 葉でない節 */
        if ((i = avail++) >= 2 * N - 1) error("表が間違っています");
        left [i] = readtree();  /* 左の枝を読む */
        right[i] = readtree();  /* 右の枝を読む */
        return i;               /* 節を返す */
    } else return (int) getbits(CHARBITS);  /* 文字 */
}

void decode(unsigned long int size)  /* 復元 */
{
    int j, root;
    unsigned long int k;

    root = readtree();  /* 木を読む */
    for (k = 0; k < size; k++) {  /* 各文字を復元 */
        j = root;  /* 根 */
        while (j >= N)
            if (getbit()) j = right[j];  else j = left[j];
        putc(j, outfile);
        if ((k & 1023) == 0) printf("%12lu\r", k);  /* 出力バイト数 */
    }
    printf("%12lu\n", size);  /* 復元したバイト数 */
}

int main(int argc, char *argv[])
{
    int c;
    unsigned long int size;  /* 元のバイト数 */

    if (argc != 4 || ((c = *argv[1]) != 'E' && c != 'e'
                                && c != 'D' && c != 'd'))
        error("使用法は本文を参照してください");
    if ((infile  = fopen(argv[2], "rb")) == NULL)
        error("入力ファイルが開きません");
    if ((outfile = fopen(argv[3], "wb")) == NULL)
        error("出力ファイルが開きません");
    if (c == 'E' || c == 'e') {
        fseek(infile, 0L, SEEK_END);  /* infile の末尾を探す */
        size = ftell(infile);     /* infile のバイト数 */
        fwrite(&size, sizeof size, 1, outfile);
        rewind(infile);
        encode();  /* 圧縮 */
    } else {
        fread(&size, sizeof size, 1, infile);  /* 元のバイト数 */
        decode(size);  /* 復元 */
    }
    fclose(infile);  fclose(outfile);
    return 0;
}
