/***********************************************************
    mergsort.c -- マージソート
***********************************************************/
#define N  90
struct {  int key;  int info;  } a[N], work[N / 2 + 1];

void mergesort(int first, int last)
{
    int middle;
    static int i, j, k, p;

    if (first < last) {
        middle = (first + last) / 2;
        mergesort(first, middle);
        mergesort(middle + 1, last);
        p = 0;
        for (i = first; i <= middle; i++) work[p++] = a[i];
        i = middle + 1;  j = 0;  k = first;
        while (i <= last && j < p)
            if (work[j].key <= a[i].key) a[k++] = work[j++];
            else                         a[k++] = a[i++];
        while (j < p) a[k++] = work[j++];
    }
}

#include <stdio.h>
#include <stdlib.h>

void show(void)
{
    int i, j;

    for (j = 0; j < 10; j++) {
        for (i = j; i < N; i += 10)
            printf("%5d:%2d", a[i].info, a[i].key);
        printf("\n");
    }
}

int main(void)
{
    int i;

    for (i = 0; i < N; i++) {
        a[i].key = rand() / (RAND_MAX / 10 + 1);
        a[i].info = i;
    }
    show();
    mergesort(0, N - 1);
    printf("マージソートは安定です.\n");
    show();
    return 0;
}
