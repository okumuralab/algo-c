/***********************************************************
    tbintree.c -- ひも付き2分木
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];  /* 探索のキーの型 */
typedef struct node {      /* struct node は木のノード */
    struct node *left, *right;  /* 左右の子へのポインタ */
    unsigned int count;    /* 参照回数カウンタ */
    keytype key;           /* 探索のキー(登録文字列) */
    char flags;            /* 本文参照 */
} *nodeptr;  /* {\tt nodeptr} はノードへのポインタ */

#define LBIT 1  /* 上の {\tt flags} の説明参照 */
#define RBIT 2

struct node root = {&root, &root, 0, "", 0};  /* 木の根 */

nodeptr newnode(keytype key)  /* 新しいノードを生成 */
{
    nodeptr p;

    if ((p = malloc(sizeof *p)) == NULL) {
        printf("メモリ不足.\n");  exit(1);
    }
    strcpy(p->key, key);  /* キーをコピーする */
    p->count = 1;         /* 参照回数を1にする */
    return p;
}

void insertright(nodeptr p, keytype key)  /* ノード p の右に挿入 */
{
    nodeptr q;

    q = newnode(key);     /* 新しいノードを生成 */
    q->right = p->right;  /* 右の子は親の右の子を受け継ぐ */
    q->left = p;          /* 左の子はじつは親を指すひも */
    q->flags = p->flags & RBIT;  /* 右フラグは親の右フラグを受け継ぐ */
    p->flags |= RBIT;     /* {\tt q} はひもでないので親の右フラグを立てる */
    p->right = q;         /* {\tt q} を親 {\tt p} の右の子にする */
}

void insertleft(nodeptr p, keytype key)  /* ノード p の左に挿入 */
{                                        /* 説明は上と同様なので省く */
    nodeptr q;

    q = newnode(key);
    q->left = p->left;  q->right = p;
    q->flags = p->flags & LBIT;
    p->flags |= LBIT;  p->left = q;
}

void insert(keytype key)  /* 挿入(登録) */
{
    int cmp;    /* 比較結果 */
    nodeptr p;

    p = &root;  cmp = 1;  /* 最初の子は親の右に */
    do {
        if (cmp < 0) {    /* 小さければ左に登録 */
            if (p->flags & LBIT) p = p->left;
            else {  insertleft(p, key);  return;  }
        } else {          /* 大きければ右に登録 */
            if (p->flags & RBIT) p = p->right;
            else {  insertright(p, key);  return;  }
        }
    } while ((cmp = strcmp(key, p->key)) != 0);
    p->count++;           /* 等しければ参照回数を増すだけ */
}

nodeptr successor(nodeptr p)  /* 昇順で {\tt p} の直後のノード */
{  /* ${\tt right} \leftrightarrow {\tt left}$, ${\tt RBIT} \leftrightarrow {\tt LBIT}$ とすれば直前のノードになる */
    nodeptr q;

    q = p->right;
    if (p->flags & RBIT)
        while (q->flags & LBIT) q = q->left;
    return q;
}

void printinorder(void)  /* 昇順で全キーを出力 */
{
    nodeptr p;

    p = &root;
    while ((p = successor(p)) != &root)
        printf("%-20s %5d\n", p->key, p->count);
}

int main(void)
{
    char word[21];

    while (scanf("%20s%*[^ \n\t]", word) == 1)
        insert(word);  /* 標準入力から単語を読み登録 */
    printinorder();    /* 各単語と出現回数を昇順に出力 */
    return 0;
}
