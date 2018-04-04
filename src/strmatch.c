/***********************************************************
    strmatch.c -- 文字列照合
***********************************************************/
int position(char text[], char pattern[])
{
    int i, j, k, c;

    c = pattern[0];  i = 0;
    while (text[i] != 0) {
        if (text[i++] == c) {
            k = i;  j = 1;
            while (text[k] == pattern[j] && pattern[j] != 0) {
                k++;  j++;
            }
            if (pattern[j] == '\0') return k - j;  /* 見つかった */
        }
    }
    return -1;  /* 見つからなかった */
}

#if 0   /***** あるいは同じことであるが... *****/
int position(char text[], char pattern[])
{
    int i, j;

    i = j = 0;
    while (text[i] != '\0' && pattern[j] != '\0')
        if (text[i] == pattern[j]) {  i++;  j++;  }
        else {  i = i - j + 1;  j = 0;  }
    if (pattern[j] == '\0') return i - j;  /* 見つかった */
    return -1;  /* 見つからなかった */
}
#endif

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int i;
    char text[] = "AAAAAABAAAC",
         pattern[4][4] = { "AAA", "AAB", "AAC", "AAD" };

    for (i = 0; i < 4; i++)
        printf("position(\"%s\", \"%s\") = %d\n",
            text, pattern[i], position(text, pattern[i]));
    return 0;
}
