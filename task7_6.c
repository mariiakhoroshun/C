#include <stdio.h>

#define MAX_N 20

void input_vector(double v[], int n) {
    for (int i = 0; i < n; i++) {
        printf("v[%d] = ", i);
        scanf("%lf", &v[i]);
    }
}

void print_vector(double v[], int n) {
    printf("(");
    for (int i = 0; i < n; i++) {
        printf("%.4f", v[i]);
        if (i < n - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

void add_vectors(double a[], double b[], double result[], int n) {
    for (int i = 0; i < n; i++) {
        result[i] = a[i] + b[i];
    }
}

double dot_product(double a[], double b[], int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

int main(void) {
    int n;
    double a[MAX_N];
    double b[MAX_N];
    double sum[MAX_N];

    printf("Enter dimension n (1 <= n < 20): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_N) {
        printf("Invalid dimension.\n");
        return 1;
    }

    printf("Enter elements of the first vector:\n");
    input_vector(a, n);

    printf("Enter elements of the second vector:\n");
    input_vector(b, n);

    add_vectors(a, b, sum, n);
    printf("Sum vector:\n");
    print_vector(sum, n);

    double dot = dot_product(a, b, n);
    printf("Dot product: %.4f\n", dot);

    return 0;
}