/***********************************************************
    merge.c -- マージ
***********************************************************/

typedef int keytype;

void merge(int na, keytype a[], int nb, keytype b[], keytype c[])
{
    int i, j, k;

    i = j = k = 0;
    while (i < na && j < nb)
        if (a[i] <= b[j]) c[k++] = a[i++];
        else              c[k++] = b[j++];
    while (i < na) c[k++] = a[i++];
    while (j < nb) c[k++] = b[j++];
}

#include <stdio.h>
#include <stdlib.h>

#define NA 20
#define NB 30

int a[NA], b[NB], c[NA + NB];

int main(void)
{
    int i;

    a[0] = rand() / (RAND_MAX / 10);
    for (i = 1; i < NA; i++)
        a[i] = a[i - 1] + rand() / (RAND_MAX / 10);
    b[0] = rand() / (RAND_MAX / 10);
    for (i = 1; i < NB; i++)
        b[i] = b[i - 1] + rand() / (RAND_MAX / 10);
    printf("a:");
    for (i = 0; i < NA; i++) printf(" %d", a[i]);
    printf("\n");
    printf("b:");
    for (i = 0; i < NB; i++) printf(" %d", b[i]);
    printf("\n");

    merge(NA, a, NB, b, c);

    printf("c:");
    for (i = 0; i < NA + NB; i++) printf(" %d", c[i]);
    printf("\n");

    return 0;
}
