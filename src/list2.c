/***********************************************************
    list2.c -- リスト
***********************************************************/
#include <stdio.h>              /********* Pascal *********/
#include <stdlib.h>             /* type infotype = int;   */
typedef int infotype;           /*      pointer = ^item;  */
                                /*      item = record     */
typedef struct item {           /*        info: infotype; */
    infotype info;              /*        next: pointer   */
    struct item *next;          /*      end;              */
} *pointer;                     /**************************/

pointer add_list(infotype x, pointer p)
{
    pointer q;
                                       /***** Pascal ******/
    q = malloc(sizeof *q);             /*  new(q);        */
    if (q == NULL) {
        printf("メモリ不足.\n");  exit(1);
    }
    q->info = x;  q->next = p;         /*  q^.info := x;  */
    return q;                          /*  q^.next := p;  */
}                                      /*******************/

void show_list(pointer p)
{
    while (p != NULL) {
        printf(" %d", p->info);  p = p->next;
    }
    printf("\n");
}

pointer reverse_list(pointer p)
{
    pointer q, t;

    q = NULL;
    while (p != NULL) {
        t = q;  q = p;  p = p->next;  q->next = t;
    }
    return q;
}

int main(void)
{
    infotype x;
    pointer head;

    head = NULL;  /* 空のリスト */
    for (x = 1; x <= 9; x++)
        head = add_list(x, head);
    show_list(head);
    head = reverse_list(head);
    show_list(head);
    return 0;
}
