/***********************************************************
    genperm.c -- 順列生成
***********************************************************/

/***** 共通の定義 *****/

#include <stdio.h>
#define N 4
int count, p[N];

void show(void)
{
    int i;

    count++;  printf("%5d: ", count);
    for (i = 0; i < N; i++) printf(" %d", p[i]);
    printf("\n");
}

/***** 方法 1 *****/

#define TRUE  1
#define FALSE 0
char ok[N + 1];

void put(int pos, int k)
{
    int j;

    p[pos] = k;
    if (pos == N - 1) show();
    else {
        ok[k] = FALSE;
        for (j = 1; j <= N; j++)
            if (ok[j]) put(pos + 1, j);
        ok[k] = TRUE;
    }
}

void genperm1(void)
{
    int k;

    count = 0;
    for (k = 1; k <= N; k++) ok[k] = TRUE;
    for (k = 1; k <= N; k++) put(0, k);
}

/***** 方法 2 *****/

void put2(int pos, int k)
{
    int j;

    p[pos] = k;
    if (k == N) show();
    else
        for (j = 0; j < N; j++)
            if (p[j] == 0) put2(j, k + 1);
    p[pos] = 0;
}

void genperm2(void)
{
    int pos;

    count = 0;
    for (pos = 0; pos < N; pos++) p[pos] = 0;
    for (pos = 0; pos < N; pos++) put2(pos, 1);
}

/***** 方法 3 *****/

void perm(int i)
{
    int t, j;

    if (i > 0) {
        perm(i - 1);
        for (j = i - 1; j >= 0; j--) {
            t = p[i];  p[i] = p[j];  p[j] = t;
            perm(i - 1);
            t = p[i];  p[i] = p[j];  p[j] = t;
        }
    } else show();
}

void genperm3(void)
{
    int i;

    count = 0;
    for (i = 0; i < N; i++) p[i] = i + 1;
    perm(N - 1);
}

/***** 方法 4 *****/

void genperm4(void)
{
    int i, k, t, c[N + 1];

    count = 0;
    for (i = 0; i < N; i++) p[i] = i + 1;
    for (i = 1; i <= N; i++) c[i] = i;  /* c[N]≠0 は番人 */
    k = 1;
    while (k < N) {
        if (k & 1) i = c[k];  else i = 0;
        t = p[k];  p[k] = p[i];  p[i] = t;
        show();
        k = 1;
        while (c[k] == 0) {  c[k] = k;  k++;  }
        c[k]--;
    }
}

/***** 各方法のテスト *****/

#include <stdlib.h>

int main(void)
{
    printf("方法 1\n");  genperm1();
    printf("方法 2\n");  genperm2();
    printf("方法 3\n");  genperm3();
    printf("方法 4\n");  genperm4();
    return 0;
}
