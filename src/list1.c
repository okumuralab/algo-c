/***********************************************************
    list1.c -- リスト
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

#define NIL 100  /* 最大の添字 + 1 */
typedef int indextype, infotype;

infotype info[NIL];
indextype next[NIL];

indextype add_list(infotype x, indextype p)
{
    static indextype avail = 0;
    indextype q;

    q = avail++;
    if (q == NIL) {
        printf("満杯です.\n");  exit(1);
    }
    info[q] = x;  next[q] = p;
    return q;
}

void show_list(indextype p)
{
    while (p != NIL) {
        printf(" %d", info[p]);  p = next[p];
    }
    printf("\n");
}

indextype reverse_list(indextype p)
{
    indextype q, t;

    q = NIL;
    while (p != NIL) {
        t = q;  q = p;  p = next[p];  next[q] = t;
    }
    return q;
}

int main(void)
{
    infotype x;
    indextype head;

    head = NIL;                             /* 空のリスト */
    for (x = 1; x <= 9; x++)
        head = add_list(x, head);                 /* 登録 */
    show_list(head);                              /* 表示 */
    head = reverse_list(head);        /* 逆順に並べ替える */
    show_list(head);                              /* 表示 */
    return 0;
}
