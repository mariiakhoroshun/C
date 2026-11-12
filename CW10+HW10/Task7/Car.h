#ifndef CAR_H
#define CAR_H

#include <stdbool.h>

typedef struct {
    double price;
    int age;
} Car;

bool input_car(Car *c);
bool input_cars(Car *arr, int n);
void print_car(const Car *c);
void print_cars(const Car *arr, int n);
int calc_avg_price_older_than(const Car *arr, int n, int min_age, double *avg_price);

#endif