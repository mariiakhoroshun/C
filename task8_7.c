#include <stdio.h>
#include <math.h>

#define MAX_N 20

double calculate_determinant(double mat[][MAX_N], int n) {
    double a[MAX_N][MAX_N];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = mat[i][j];
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[j][i]) > fabs(a[pivot][i])) {
                pivot = j;
            }
        }

        if (fabs(a[pivot][i]) < 1e-9) {
            return 0.0;
        }

        if (pivot != i) {
            for (int k = 0; k < n; k++) {
                double temp = a[i][k];
                a[i][k] = a[pivot][k];
                a[pivot][k] = temp;
            }
            det = -det;
        }

        det *= a[i][i];

        for (int j = i + 1; j < n; j++) {
            double factor = a[j][i] / a[i][i];
            for (int k = i + 1; k < n; k++) {
                a[j][k] -= factor * a[i][k];
            }
        }
    }

    return det;
}

int main(void) {
    int n;
    double mat[MAX_N][MAX_N];

    printf("Enter matrix dimension n (1 <= n < 20): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_N) {
        printf("Invalid dimension.\n");
        return 1;
    }

    printf("Enter elements of matrix %d x %d:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    double det = calculate_determinant(mat, n);
    printf("Determinant: %.6f\n", det);

    return 0;
}