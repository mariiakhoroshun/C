#include <stdio.h>

#define MAX_N 25

void transpose_matrix(double mat[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double temp = mat[i][j];
            mat[i][j] = mat[j][i];
            mat[j][i] = temp;
        }
    }
}

void print_matrix(double mat[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int n;
    double mat[MAX_N][MAX_N];

    printf("Enter matrix size n (0 < n < 25): ");
    if (scanf("%d", &n) != 1 || n <= 0 || n >= MAX_N) {
        printf("Invalid size.\n");
        return 1;
    }

    printf("Enter %d x %d matrix elements:\n", n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }

    printf("Original matrix:\n");
    print_matrix(mat, n);

    transpose_matrix(mat, n);

    printf("Transposed matrix:\n");
    print_matrix(mat, n);

    return 0;
}