#include "Car.h"
#include <stdio.h>

bool input_car(Car *c) {
    if (c == NULL) {
        return false;
    }
    printf("  Price: ");
    if (scanf("%lf", &c->price) != 1 || c->price < 0.0) {
        return false;
    }
    printf("  Age (years): ");
    if (scanf("%d", &c->age) != 1 || c->age < 0) {
        return false;
    }
    return true;
}

bool input_cars(Car *arr, int n) {
    if (arr == NULL || n <= 0) {
        return false;
    }
    for (int i = 0; i < n; i++) {
        printf("Car model #%d:\n", i + 1);
        if (!input_car(&arr[i])) {
            return false;
        }
    }
    return true;
}

void print_car(const Car *c) {
    if (c == NULL) {
        return;
    }
    printf("Price: %10.2f | Age: %d years\n", c->price, c->age);
}

void print_cars(const Car *arr, int n) {
    if (arr == NULL || n <= 0) {
        return;
    }
    printf("\nList of car models:\n");
    for (int i = 0; i < n; i++) {
        printf("#%d -> ", i + 1);
        print_car(&arr[i]);
    }
}

int calc_avg_price_older_than(const Car *arr, int n, int min_age, double *avg_price) {
    if (avg_price != NULL) {
        *avg_price = 0.0;
    }
    if (arr == NULL || n <= 0 || avg_price == NULL) {
        return 0;
    }

    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i].age > min_age) {
            sum += arr[i].price;
            count++;
        }
    }

    if (count > 0) {
        *avg_price = sum / count;
    }

    return count;
}