#include <stdio.h>

int main(void) {
    double mat[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}
    };
    int i, j;
    double a;

    printf("Enter row index i (0-2), column index j (0-2), and real number a: ");
    if (scanf("%d %d %lf", &i, &j, &a) != 3) {
        printf("Invalid input.\n");
        return 1;
    }

    if (i < 0 || i >= 3 || j < 0 || j >= 3) {
        printf("Error: Indices are out of bounds.\n");
        return 1;
    }

    mat[i][j] = a;

    printf("Resulting matrix:\n");
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            printf("%.2f ", mat[r][c]);
        }
        printf("\n");
    }

    return 0;
}