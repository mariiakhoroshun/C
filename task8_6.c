#include <stdio.h>

#define MAX_ROWS 100
#define MAX_COLS 100

double sum_diagonal_elements(double a[][MAX_COLS], int n, int m, int k) {
    double sum = 0.0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i - j == k) {
                sum += a[i][j];
                count++;
            }
        }
    }

    if (count == 0) {
        return 0.0;
    }

    return sum;
}

int main(void) {
    int n, m, k;
    double a[MAX_ROWS][MAX_COLS];

    printf("Enter N (rows) and M (columns) (0 < N, M < 100): ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 0 || n >= MAX_ROWS || m <= 0 || m >= MAX_COLS) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    printf("Enter elements of matrix %d x %d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%lf", &a[i][j]);
        }
    }

    printf("Enter integer k: ");
    if (scanf("%d", &k) != 1) {
        printf("Invalid k.\n");
        return 1;
    }

    double result = sum_diagonal_elements(a, n, m, k);
    printf("Result sum: %.4f\n", result);

    return 0;
}