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

bool is_valid_date(const Date *d) {
    if (d == NULL) {
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

bool input_date(Date *d) {
    if (d == NULL) {
        return false;
    }
    printf("Enter date (day month year, e.g. 12 11 2026): ");
    if (scanf("%d %d %d", &d->day, &d->month, &d->year) != 3) {
        return false;
    }
    return is_valid_date(d);
}

void print_date(const Date *d) {
    if (d == NULL) {
        return;
    }
    printf("%02d.%02d.%04d\n", d->day, d->month, d->year);
}

Date get_tomorrow(Date d) {
    if (!is_valid_date(&d)) {
        return d;
    }
    d.day++;
    if (d.day > days_in_month(d.month, d.year)) {
        d.day = 1;
        d.month++;
        if (d.month > 12) {
            d.month = 1;
            d.year++;
        }
    }
    return d;
}

int get_day_of_week(Date d) {
    int t[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    int y = d.year;
    if (d.month < 3) {
        y -= 1;
    }
    return (y + y / 4 - y / 100 + y / 400 + t[d.month - 1] + d.day) % 7;
}

void print_day_of_week(int weekday) {
    const char *names[7] = {
        "Sunday", "Monday", "Tuesday", "Wednesday",
        "Thursday", "Friday", "Saturday"
    };
    if (weekday >= 0 && weekday < 7) {
        printf("%s\n", names[weekday]);
    }
}