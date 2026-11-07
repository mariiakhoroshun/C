#include <stdio.h>
#include <math.h>

#define N 10

double sum_greater_than_e(double arr[], int size){
    double e = exp(1.0);
    double sum = 0.0;

    for (int i = 0; i < size; i++) {
        if (arr[i] > e) {
            sum += arr[i];
        }
    }

    return sum;
}

int main(void) {
    double arr[N];

    printf("Enter %d real numbers:\n", N);
    for (int i = 0; i < N; i++) {
        printf("arr[%d] = ", i);
        scanf("%lf", &arr[i]);
    }

    double sum = sum_greater_than_e(arr, N);
    printf("Sum of elements greater than e (approx. %.6f): %.6f\n", exp(1.0), sum);

    return 0;
}