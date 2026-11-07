#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

double task1_a(double a) {
    int k = 1;
    double sum = 0.0;
    while (sum <= a) {
        sum += 1.0 / k;
        k++;
    }
    return sum;
}

int task1_b(double a) {
    int n = 1;
    double sum = 0.0;
    while (sum <= a) {
        sum += 1.0 / n;
        n++;
    }
    return n - 1;
}

int main() {
    double a;
    printf("a = ");
    if (scanf("%lf", &a) != 1) {
        return 1;
    }

    double first_val = task1_a(a);
    int min_n = task1_b(a);

    printf("a) First sum > %lf is %lf\n", a, first_val);
    printf("b) Smallest n > 0 is %d\n", min_n);

    return 0;
}