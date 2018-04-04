/***********************************************************
    isomer.c -- 異性体の問題
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#define C    17  /* 炭素原子の数の上限 */
#define L  2558  /* 生成する基の個数の上限 */

int size[L], length[L], count[C + 1];

int main(void)
{
    int i, j, k, h, len, n, si, sj, sk, sh;

    n = size[0] = length[0] = 0;
    for (i = 0; i < L; i++) {
        len = length[i] + 1;  if (len > C / 2) break;
        si = size[i] + 1;  if (si + len > C) continue;
        for (j = 0; j <= i; j++) {
            sj = si + size[j];  if (sj + len > C) continue;
            for (k = 0; k <= j; k++) {
                sk = sj + size[k];  if (sk + len > C) continue;
                if (++n >= L) return 1;
                size[n] = sk;  length[n] = len;
            }
        }
    }
    if (len <= C / 2) return 1;
    for (i = 0; i <= n; i++) {
        si = size[i];
        for (j = 0; j <= i; j++) {
            if (length[i] != length[j]) continue;
            sj = si + size[j];  if (sj > C) continue;
            count[sj]++;  /* 偶数 */
            for (k = 0; k <= j; k++) {
                sk = sj + size[k] + 1;  if (sk > C) continue;
                for (h = 0; h <= k; h++) {
                    sh = sk + size[h];
                    if (sh <= C) count[sh]++;  /* 奇数 */
                }
            }
        }
    }
    for (i = 1; i <= C; i++)
        printf("炭素原子が %2d 個のものは %5d 種類\n", i, count[i]);
    return 0;
}
