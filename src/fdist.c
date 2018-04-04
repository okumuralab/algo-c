/***********************************************************
    fdist.c -- F分布
***********************************************************/
#include <math.h>
#define PI 3.14159265358979323846264

double q_f(int df1, int df2, double f)  /* 上側累積確率 */
{
    int i;
    double cos2, sin2, prob, temp;

    if (f <= 0) return 1;
    if (df1 % 2 != 0 && df2 % 2 == 0)
        return 1 - q_f(df2, df1, 1 / f);
    cos2 = 1 / (1 + df1 * f / df2);  sin2 = 1 - cos2;
    if (df1 % 2 == 0) {
        prob = pow(cos2, df2 / 2.0);  temp = prob;
        for (i = 2; i < df1; i += 2) {
            temp *= (df2 + i - 2) * sin2 / i;
            prob += temp;
        }
        return prob;
    }
    prob = atan(sqrt(df2 / (df1 * f)));
    temp = sqrt(sin2 * cos2);
    for (i = 3; i <= df1; i += 2) {
        prob += temp;  temp *= (i - 1) * sin2 / i;
    }
    temp *= df1;
    for (i = 3; i <= df2; i += 2) {
        prob -= temp;
        temp *= (df1 + i - 2) * cos2 / i;
    }
    return prob * 2 / PI;
}

double p_f(int df1, int df2, double f)  /* 下側累積確率 */
{
    if (f <= 0) return 0;
    return q_f(df2, df1, 1 / f);
}

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    static seq[4] = {1, 2, 5, 20};
    int i, j, df1;

    for (i = 0; i < 4; i++) {
        df1 = seq[i];
        printf("***** p_f(%d, df2, f) *****\n", df1);
        printf("  F   %-16s %-16s %-16s %-16s\n",
                "df2=1", "df2=2", "df2=5", "df2=20");
        for (j = 0; j <= 10; j++)
            printf("%4d %16.14f %16.14f %16.14f %16.14f\n",
                j, p_f(df1, 1, j), p_f(df1, 2, j),
                   p_f(df1, 5, j), p_f(df1, 20, j));
    }
    return 0;
}
