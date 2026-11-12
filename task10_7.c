#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double price;
    int age;
} Car;

int input_car(Car *c) {
    printf("  Price: ");
    if (scanf("%lf", &c->price) != 1 || c->price < 0.0) {
        return 0;
    }
    printf("  Age (years): ");
    if (scanf("%d", &c->age) != 1 || c->age < 0) {
        return 0;
    }
    return 1;
}

int input_cars(Car *arr, int n) {
    for (int i = 0; i < n; i++) {
        printf("Car model #%d:\n", i + 1);
        if (!input_car(&arr[i])) {
            return 0;
        }
    }
    return 1;
}

int calc_avg_price_older_than(const Car *arr, int n, int min_age, double *avg_price) {
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
    } else {
        *avg_price = 0.0;
    }

    return count;
}

int main(void) {
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
        printf("Invalid input.\n");
        free(cars);
        return 1;
    }

    double avg_price = 0.0;
    int count = calc_avg_price_older_than(cars, n, 5, &avg_price);

    if (count > 0) {
        printf("Average price of cars older than 5 years: %.2f\n", avg_price);
    } else {
        printf("No cars older than 5 years found.\n");
    }

    free(cars);
    return 0;
}