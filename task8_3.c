#include <stdio.h>

#define MAX_ROWS 20
#define MAX_COLS 20

void input_matrix(double mat[][MAX_COLS], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("mat[%d][%d] = ", i, j);
            scanf("%lf", &mat[i][j]);
        }
    }
}

void print_matrix(double mat[][MAX_COLS], int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%.4f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int m, n;
    double mat[MAX_ROWS][MAX_COLS];

    printf("Enter dimensions m and n (0 < m, n < 20): ");
    if (scanf("%d %d", &m, &n) != 2 || m <= 0 || m >= MAX_ROWS || n <= 0 || n >= MAX_COLS) {
        printf("Invalid dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements:\n");
    input_matrix(mat, m, n);

    printf("Entered matrix:\n");
    print_matrix(mat, m, n);

    return 0;
}