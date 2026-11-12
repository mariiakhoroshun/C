#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

typedef struct {
    int day;
    int month;
    int year;
} Date;

bool input_date(Date *d);
void print_date(const Date *d);

#endif