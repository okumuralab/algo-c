/***********************************************************
    solst.c -- 自己組織化探索
***********************************************************/
/* 先頭移動法 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEYSIZE     15  /* 名前欄の大きさ */
#define INFOSIZE   127  /* 住所欄の大きさ */
typedef char keytype[KEYSIZE + 1], infotype[INFOSIZE + 1];
typedef struct item {
    struct item *next;
    keytype key;
    infotype info;
} *pointer;

static struct item head = { &head, "", "" };  /* リストの頭 */

void insert(keytype key, infotype info)
{
    pointer p;

    if ((p = malloc(sizeof *p)) == NULL) {
        printf("メモリ不足.\n");  exit(1);
    }
    strcpy(p->key, key);  strcpy(p->info, info);
    p->next = head.next;  head.next = p;
}

pointer search(keytype x)
{
    pointer p, q;

    strcpy(head.key, x);  p = &head;  /* 番人 */
    do {
        q = p;  p = p->next;
    } while (strcmp(p->key, x) != 0);
    if (p == &head) return NULL;
    q->next = p->next;  p->next = head.next;  head.next = p;
    return p;
}

#define ReadString(len, x) (scanf("%" #len "s%*[^\n]", x) == 1)

int main(void)
{
    keytype key;
    infotype info;
    pointer p;

    for ( ; ; ) {
        printf("名前? ");
        if (! ReadString(KEYSIZE, key)) break;
        if ((p = search(key)) != NULL)
            printf("住所: %s\n", p->info);
        else {
            printf("住所? ");
            if (ReadString(INFOSIZE, info)) insert(key, info);
        }
    }
    return 0;
}
