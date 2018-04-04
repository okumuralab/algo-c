/***********************************************************
    tree.c -- 2分探索木
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char keytype[21];

typedef struct node {
    struct node *left, *right;
    keytype key;
} *nodeptr;

struct node nil;
nodeptr root = &nil;

nodeptr insert(keytype key)  /* 挿入 (登録) */
{
    int cmp;
    nodeptr *p, q;

    strcpy(nil.key, key);  /* 番人 */
    p = &root;
    while ((cmp = strcmp(key, (*p)->key)) != 0)
        if (cmp < 0) p = &((*p)->left );
        else         p = &((*p)->right);
    if (*p != &nil) return NULL;  /* すでに登録されている */
    if ((q = malloc(sizeof *q)) == NULL) {
        printf("メモリ不足.\n");  exit(1);
    }
    strcpy(q->key, key);
    q->left = &nil;  q->right = *p;  *p = q;
    return q;  /* 登録した */
}

int delete(keytype key)  /* 削除できれば 0, 失敗なら 1 を返す */
{
    int cmp;
    nodeptr *p, *q, r, s;

    strcpy(nil.key, key);  /* 番人 */
    p = &root;
    while ((cmp = strcmp(key, (*p)->key)) != 0)
        if (cmp < 0) p = &((*p)->left);
        else         p = &((*p)->right);
    if (*p == &nil) return 1;  /* 見つからず */
    r = *p;
    if      (r->right == &nil) *p = r->left;
    else if (r->left  == &nil) *p = r->right;
    else {
        q = &(r->left);
        while ((*q)->right != &nil) q = &((*q)->right);
        s = *q;  *q = s->left;
        s->left = r->left;  s->right = r->right;
        *p = s;
    }
    free(r);
    return 0;  /* 削除成功 */
}

nodeptr search(keytype key)  /* 検索 (未登録ならNULLを返す) */
{
    int cmp;
    nodeptr p;

    strcpy(nil.key, key);  /* 番人 */
    p = root;
    while ((cmp = strcmp(key, p->key)) != 0)
        if (cmp < 0) p = p->left;
        else         p = p->right;
    if (p != &nil) return p;     /* 見つかった */
    else           return NULL;  /* 見つからない */
}

void printtree(nodeptr p)
{
    static int depth = 0;

    if (p->left != &nil) {
        depth++;  printtree(p->left);  depth--;
    }
    printf("%*c%s\n", 5 * depth, ' ', p->key);
    if (p->right != &nil) {
        depth++;  printtree(p->right);  depth--;
    }
}

int main(void)
{
    char buf[22];

    printf("命令 Iabc:  abcを挿入\n"
           "     Dabc:  abcを削除\n"
           "     Sabc:  abcを検索\n");
    for ( ; ; ) {
        printf("命令? ");
        if (scanf("%21s%*[^\n]", buf) != 1) break;
        switch (buf[0]) {
        case 'I':  case 'i':
            if (insert(&buf[1])) printf("登録しました.\n");
            else                 printf("登録ずみです.\n");
            break;
        case 'D':  case 'd':
            if (delete(&buf[1])) printf("登録されていません.\n");
            else                 printf("削除しました.\n");
            break;
        case 'S':  case 's':
            if (search(&buf[1])) printf("登録されています.\n");
            else                 printf("登録されていません\n");
            break;
        default:
            printf("使えるのは I, D, S です.\n");
            break;
        }
        if (root != &nil) {
            printf("\n");  printtree(root);  printf("\n");
        }
    }
    return 0;
}
