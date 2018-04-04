/***********************************************************
    wordcnt.c -- ハッシュ法
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define HASHSIZE   101  /* ハッシュ表の大きさ (素数) */
#define MAXWORDLEN 128  /* 最大単語長 */

int wordlen;                    /* 単語長 */
unsigned long words, newwords;  /* 単語, 新単語カウンタ */
char word[MAXWORDLEN + 1];      /* 現在の単語 */

typedef struct node {           /* 2分木のノード */
    struct node *left, *right;  /* 左右の子 */
    char *key;                  /* キー (文字列) */
} *nodeptr;

struct node nil = {NULL, NULL, word};  /* 番人 */
nodeptr hashtable[HASHSIZE];    /* ハッシュ表 */

int hash(char *s)               /* 簡単なハッシュ関数 */
{
    unsigned v;

    for (v = 0; *s != '\0'; s++)
        v = ((v << CHAR_BIT) + *s) % HASHSIZE;
    return (int)v;
}

void insert(void)  /* 挿入 (登録) */
{
    int cmp;
    nodeptr *p, q;

    words++;
    p = &hashtable[hash(word)];
    while ((cmp = strcmp(word, (*p)->key)) != 0)
        if (cmp < 0) p = &((*p)->left );
        else         p = &((*p)->right);
    if (*p != &nil) return;  /* すでに登録されている */
    newwords++;
    if ((q = malloc(sizeof *q)) == NULL
     || (q->key = malloc(wordlen + 1)) == NULL) {
        printf("メモリ不足.\n");  exit(1);
    }
    strcpy(q->key, word);
    q->left = &nil;  q->right = *p;  *p = q;
}

void getword(void)
{
    int c;

    wordlen = 0;
    do {
        if ((c = getchar()) == EOF) return;
    } while (! isalpha(c));
    do {
        if (wordlen < MAXWORDLEN) word[wordlen++] = tolower(c);
        c = getchar();
    } while (isalpha(c));
    word[wordlen] = '\0';
}

int main(void)
{
    int i;

    words = newwords = 0;
    for (i = 0; i < HASHSIZE; i++) hashtable[i] = &nil;
    while (getword(), wordlen != 0) insert();
    printf("%lu words, %lu different words\n", words, newwords);
    return 0;
}
