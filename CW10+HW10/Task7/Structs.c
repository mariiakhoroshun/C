#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Car.h"

void test_car(void) {
    Car sample1[4] = {
        {15000.0, 3},
        {8000.0, 6},
        {6000.0, 8},
        {10000.0, 5}
    };
    double avg1 = 0.0;
    int count1 = calc_avg_price_older_than(sample1, 4, 5, &avg1);
    bool t1 = (count1 == 2 && fabs(avg1 - 7000.0) < 1e-9);

    Car sample2[2] = {
        {20000.0, 2},
        {12000.0, 5}
    };
    double avg2 = 0.0;
    int count2 = calc_avg_price_older_than(sample2, 2, 5, &avg2);
    bool t2 = (count2 == 0 && fabs(avg2 - 0.0) < 1e-9);

    bool t3 = (calc_avg_price_older_than(NULL, 4, 5, &avg1) == 0 && !input_car(NULL));

    printf("--- Automated Tests (Car) ---\n");
    printf("Test 1 (cars older than 5 years -> avg 7000.00): %s\n", t1 ? "PASSED" : "FAILED");
    printf("Test 2 (no cars older than 5 years -> count 0): %s\n", t2 ? "PASSED" : "FAILED");
    printf("Test 3 (NULL safety): %s\n", t3 ? "PASSED" : "FAILED");
    printf("-----------------------------\n\n");
}

int main(void) {
    test_car();

    int n;
    printf("Enter number of car models N: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    Car *cars = (Car *)malloc((size_t)n * sizeof(Car));
    if (cars == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    if (!input_cars(cars, n)) {
        printf("Invalid car input.\n");
        free(cars);
        return 1;
    }

    print_cars(cars, n);

    double avg_price = 0.0;
    int count = calc_avg_price_older_than(cars, n, 5, &avg_price);

    if (count > 0) {
        printf("\nAverage price of cars older than 5 years (%d model(s)): %.2f\n",
               count, avg_price);
    } else {
        printf("\nNo car models older than 5 years found.\n");
    }

    free(cars);
    return 0;
}