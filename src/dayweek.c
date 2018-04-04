/***********************************************************
    dayweek.c -- 曜日
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int year, month, day, dayofweek;
    static char name[7][10] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday" };

    printf("Year ? ");  scanf("%d", &year);
    printf("Month? ");  scanf("%d", &month);
    printf("Day  ? ");  scanf("%d", &day);
    if (month < 3) {  year--;  month += 12;  }
    dayofweek = (year + year / 4 - year / 100 + year / 400
        + (13 * month + 8) / 5 + day) % 7;
    printf("It's %s.\n", name[dayofweek]);
    return 0;
}
