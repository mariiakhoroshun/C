#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

bool is_valid_date(const Date *d);
bool input_date(Date *d);
void print_date(const Date *d);
Date get_tomorrow(Date d);
int get_day_of_week(Date d);
void print_day_of_week(int weekday);

#endif