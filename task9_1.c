#include <stdio.h>
#include <stdlib.h>

double *allocate_array(int n) {
    return (double *)malloc((size_t)n * sizeof(double));
}

void input_array(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        scanf("%lf", &arr[i]);
    }
}

double calculate_sum_of_squares(const double *arr, int n) {
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i] * arr[i];
    }
    return sum;
}

void free_array(double *arr) {
    free(arr);
}

int main(void) {
    int n;

    printf("Enter a natural number n: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Expected a positive integer.\n");
        return 1;
    }

    double *arr = allocate_array(n);
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d real numbers:\n", n);
    input_array(arr, n);

    double sum = calculate_sum_of_squares(arr, n);
    printf("Sum of squares: %.6f\n", sum);

    free_array(arr);

    return 0;
}