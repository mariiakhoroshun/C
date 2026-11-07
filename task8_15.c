#include <stdio.h>
#include <math.h>

#define MAX_N 20

void input_matrix(double mat[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%lf", &mat[i][j]);
        }
    }
}

void print_matrix(double mat[][MAX_N], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%8.2f ", mat[i][j]);
        }
        printf("\n");
    }
}

void find_max_abs_pos(double mat[][MAX_N], int n, int pos[]) {
    int max_r = 0;
    int max_c = 0;
    double max_val = fabs(mat[0][0]);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fabs(mat[i][j]) > max_val) {
                max_val = fabs(mat[i][j]);
                max_r = i;
                max_c = j;
            }
        }
    }

    pos[0] = max_r;
    pos[1] = max_c;
}

void remove_row_and_col(double mat[][MAX_N], int n, int rem_r, int rem_c) {
    double temp[MAX_N][MAX_N];
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (i == rem_r) {
            continue;
        }
        int c = 0;
        for (int j = 0; j < n; j++) {
            if (j == rem_c) {
                continue;
            }
            temp[r][c] = mat[i][j];
            c++;
        }
        r++;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            mat[i][j] = temp[i][j];
        }
    }
}

int main(void) {
    int n;
    double mat[MAX_N][MAX_N];

    printf("Enter matrix size n (1 <= n <= %d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N) {
        printf("Invalid matrix size.\n");
        return 1;
    }

    printf("Enter %d x %d matrix elements:\n", n, n);
    input_matrix(mat, n);

    printf("\nInitial matrix (%d x %d):\n", n, n);
    print_matrix(mat, n);

    int step = 1;
    while (n > 1) {
        int pos[2];
        find_max_abs_pos(mat, n, pos);

        printf("\nStep %d:\n", step);
        printf("Max abs element: %.2f at row %d, col %d\n", mat[pos[0]][pos[1]], pos[0], pos[1]);
        printf("Removing row %d and column %d...\n", pos[0], pos[1]);

        remove_row_and_col(mat, n, pos[0], pos[1]);
        n--;

        printf("New matrix after removal (%d x %d):\n", n, n);
        print_matrix(mat, n);

        step++;
    }

    return 0;
}