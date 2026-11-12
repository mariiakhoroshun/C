#include "Date.h"
#include <stdio.h>

static bool is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

static int days_in_month(int month, int year) {
    if (month == 2) {
        return is_leap_year(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

bool input_date(Date *d) {
    if (d == NULL) {
        return false;
    }
    printf("Enter date (day month year, e.g. 12 11 2026): ");
    if (scanf("%d %d %d", &d->day, &d->month, &d->year) != 3) {
        return false;
    }
    if (d->year < 1 || d->month < 1 || d->month > 12 || d->day < 1) {
        return false;
    }
    if (d->day > days_in_month(d->month, d->year)) {
        return false;
    }
    return true;
}

void print_date(const Date *d) {
    if (d == NULL) {
        return;
    }
    printf("%02d.%02d.%04d\n", d->day, d->month, d->year);
}