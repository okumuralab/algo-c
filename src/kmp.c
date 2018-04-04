/***********************************************************
    kmp.c -- Knuth--Morris--Pratt法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define DEMO
#define M  9  /* M >= strlen(pattern) */

int position(char text[], char pattern[])
{
    int i, j;
    static int next[M + 1];

    if (pattern[0] == '\0') return 0;
    i = 1;  j = 0;  next[1] = 0;
    while (pattern[i] != '\0') {
        if (i >= M) return -1;  /* エラー: {\tt pattern}が長すぎる */
        if (pattern[i] == pattern[j]) {  i++;  j++;  next[i] = j;  }
        else if (j == 0) {  i++;  next[i] = j;  }
        else j = next[j];
    }
#ifdef DEMO
    for (j = 0; pattern[j] != '\0'; j++)
        printf("pattern[%d] = %c, next[%d] = %d\n",
            j, pattern[j], j + 1, next[j + 1]);
#endif
    i = j = 0;
    while (text[i] != '\0' && pattern[j] != '\0') {
        if (text[i] == pattern[j]) {  i++;  j++;  }
        else if (j == 0) i++;
        else j = next[j];
    }
    if (pattern[j] == '\0') return i - j;
    return -1;  /* 見つからない */
}

int main(void)
{
    char text[] = "ABCABCABABC", pattern[] = "ABCABA";

    printf("position(\"%s\", \"%s\") = %d\n",
        text, pattern, position(text, pattern));
    return 0;
}
