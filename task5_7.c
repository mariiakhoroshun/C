#include <stdio.h>

int main(void) {
    int n;
    printf("Enter a natural number n: ");
    scanf("%d", &n);

    double S = 0.0;
    double a_prev2 = 0.0;
    double a_prev1 = 1.0;
    double b_prev1 = 0.0;
    double pow2 = 1.0;

    for (int k = 1; k <= n; k++) {
        pow2 *= 2.0;
        double a_k, b_k;

        if (k == 1) {
            a_k = 0.0;
            b_k = 1.0;
        } else if (k == 2) {
            a_k = 1.0;
            b_k = 0.0;
        } else {
            b_k = b_prev1 + a_prev1;
            a_k = (a_prev1 / k) + a_prev2 * b_k;

            a_prev2 = a_prev1;
            a_prev1 = a_k;
            b_prev1 = b_k;
        }

        S += pow2 / (a_k + b_k);
    }

    printf("Sum S_%d = %.10f\n", n, S);

    return 0;
}