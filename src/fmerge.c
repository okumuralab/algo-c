/***********************************************************
    fmerge.c -- マージ
***********************************************************/

#include <stdio.h>

void fmerge(FILE *f1, FILE *f2, FILE *f3)
{
    int x1, x2;  /* キー */
    int r1, r2;  /* fscanf() の結果 */

    r1 = fscanf(f1, "%d", &x1);
    r2 = fscanf(f2, "%d", &x2);
    for ( ; ; ) {
        if (r1 == 1 && (r2 != 1 || x1 <= x2)) {
            fprintf(f3, " %d", x1);  r1 = fscanf(f1, "%d", &x1);
        } else if (r2 == 1) {
            fprintf(f3, " %d", x2);  r2 = fscanf(f2, "%d", &x2);
        } else break;
    }
}

#include <stdlib.h>
#include <time.h>

int main(void)
{
    int i, x, m, n;
    FILE *f1, *f2, *f3;

    srand((unsigned int) time(NULL));
    m = rand() / (RAND_MAX / 20);
    n = rand() / (RAND_MAX / 20);
    f1 = fopen("test1", "w");
    f2 = fopen("test2", "w");
    printf("f1:");  x = 0;
    for (i = 0; i < m; i++) {
        x += rand() / (RAND_MAX / 10);
        printf(" %d", x);  fprintf(f1, " %d", x);
    }
    printf("\n");
    printf("f2:");  x = 0;
    for (i = 0; i < n; i++) {
        x += rand() / (RAND_MAX / 10);
        printf(" %d", x);  fprintf(f2, " %d", x);
    }
    printf("\n");
    fclose(f1);  fclose(f2);

    f1 = fopen("test1", "r");
    f2 = fopen("test2", "r");
    f3 = fopen("test3", "w");
    fmerge(f1, f2, f3);
    fclose(f1);  fclose(f2);  fclose(f3);

    f3 = fopen("test3", "r");
    printf("f3:");
    while (fscanf(f3, "%d", &x) == 1) printf(" %d", x);
    printf("\n");
    return 0;
}
