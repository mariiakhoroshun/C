#include <stdio.h>
#include <math.h>

double compute_v(int n) {
    if (n == 0 || n == 1) {
        return 1.0;
    }

    double u_prev2 = 0.0;
    double u_prev1 = 0.0;
    double v_prev2 = 1.0;
    double v_prev1 = 1.0;
    double v_curr = 1.0;

    for (int i = 2; i <= n; i++) {
        v_curr = (u_prev1 - v_prev1) / (fabs(u_prev2 + v_prev1) + 2.0);
        double u_curr = (u_prev1 - u_prev2 * v_prev1 - v_prev2) / (1.0 + u_prev1 * u_prev1 + v_prev1 * v_prev1);

        u_prev2 = u_prev1;
        u_prev1 = u_curr;
        v_prev2 = v_prev1;
        v_prev1 = v_curr;
    }

    return v_curr;
}

int main(void) {
    int n;

    printf("Enter n (n >= 0): ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    double result = compute_v(n);
    printf("v_%d = %.10f\n", n, result);

    return 0;
}