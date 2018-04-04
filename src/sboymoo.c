/***********************************************************
    sboymoo.c -- Boyer--Moore法
***********************************************************/
/* 簡略Boyer-Moore法 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>  /* #define UCHAR_MAX 255 */
#define DEMO         /* デモンストレーション */

int position(unsigned char text[], unsigned char pattern[])
{
    int i, j, k, len;
    static int skip[UCHAR_MAX + 1];
    unsigned char c, tail;

    len = strlen((char *)pattern);  /* 文字列の長さ */
    if (len == 0) return -1;        /* エラー: 長さ0 */
    tail = pattern[len - 1];        /* 最後の文字 */
    if (len == 1) {                 /* 長さ1なら簡単! */
        for (i = 0; text[i] != '\0'; i++)
            if (text[i] == tail) return i;
    } else {                        /* 長さ2以上なら表を作って… */
        for (i = 0; i <= UCHAR_MAX; i++) skip[i] = len;
        for (i = 0; i < len - 1; i++)
            skip[pattern[i]] = len - 1 - i;
        /* i = len - 1; */          /* いよいよ照合 */
        while ((c = text[i]) != '\0') {
#ifdef DEMO                         /* デモンストレーション用 */
            printf("テ: %s\n", text);
            printf("照: %*s\n", i + 1, pattern);
#endif
            if (c == tail) {
                j = len - 1;  k = i;
                while (pattern[--j] == text[--k])
                    if (j == 0) return k;  /* 見つかった */
            }
            i += skip[c];
        }
    }
    return -1;  /* 見つからなかった */
}

int mygets(int n, unsigned char s[])  /* n 文字まで s[] に読み込む */
{
    int i, c;

    i = 0;
    while ((c = getchar()) != EOF && c != '\n')
        if (i < n) s[i++] = (unsigned char)c;
    if (i != 0) s[i] = '\0';
    return i;
}

int main(void)
{
    int n, m, p;
    static unsigned char
        text[256] = "supercalifragilisticexpialidocious",
        pattern[128];

    for ( ; ; ) {
        printf("テキスト文字列 (リターン: %s)\n  ? ", text);
        if ((n = mygets(127, text)) == 0) n = strlen((char *)text);
        printf("照合文字列 (リターン: 終了)\n  ? ");
        if ((m = mygets(127, pattern)) == 0) break;
        memset(text + n, 0, m);
        p = position(text, pattern);
        if (p >= 0) printf("位置 = %d\n\n", p);
        else        printf("見つかりません.\n\n");
    }
    return 0;
}
