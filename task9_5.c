#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int **allocate_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        return NULL;
    }
    int **mat = (int **)malloc((size_t)rows * sizeof(int *));
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        mat[i] = (int *)malloc((size_t)cols * sizeof(int));
        if (mat[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(mat[j]);
            }
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrix(int **mat, int rows) {
    if (mat != NULL) {
        for (int i = 0; i < rows; i++) {
            free(mat[i]);
        }
        free(mat);
    }
}

int **input_matrix(int rows, int cols) {
    int **mat = allocate_matrix(rows, cols);
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (scanf("%d", &mat[i][j]) != 1) {
                free_matrix(mat, rows);
                return NULL;
            }
        }
    }
    return mat;
}

void print_matrix(int **mat, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%5d ", mat[i][j]);
        }
        printf("\n");
    }
}

int calculate_rank(int **mat, int rows, int cols) {
    if (mat == NULL || rows <= 0 || cols <= 0) {
        return 0;
    }

    double **temp = (double **)malloc((size_t)rows * sizeof(double *));
    if (temp == NULL) {
        return -1;
    }
    for (int i = 0; i < rows; i++) {
        temp[i] = (double *)malloc((size_t)cols * sizeof(double));
        if (temp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(temp[j]);
            }
            free(temp);
            return -1;
        }
        for (int j = 0; j < cols; j++) {
            temp[i][j] = (double)mat[i][j];
        }
    }

    int rank = 0;
    int lead = 0;
    for (int r = 0; r < rows && lead < cols; lead++) {
        int pivot = r;
        for (int k = r + 1; k < rows; k++) {
            if (fabs(temp[k][lead]) > fabs(temp[pivot][lead])) {
                pivot = k;
            }
        }

        if (fabs(temp[pivot][lead]) < 1e-9) {
            continue;
        }

        if (pivot != r) {
            double *swap_row = temp[r];
            temp[r] = temp[pivot];
            temp[pivot] = swap_row;
        }

        for (int k = r + 1; k < rows; k++) {
            double factor = temp[k][lead] / temp[r][lead];
            for (int j = lead; j < cols; j++) {
                temp[k][j] -= factor * temp[r][j];
            }
        }
        r++;
        rank++;
    }

    for (int i = 0; i < rows; i++) {
        free(temp[i]);
    }
    free(temp);

    return rank;
}

int calculate_determinant(int **mat, int n, double *det_out) {
    if (mat == NULL || n <= 0 || det_out == NULL) {
        return 0;
    }

    double **temp = (double **)malloc((size_t)n * sizeof(double *));
    if (temp == NULL) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        temp[i] = (double *)malloc((size_t)n * sizeof(double));
        if (temp[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(temp[j]);
            }
            free(temp);
            return 0;
        }
        for (int j = 0; j < n; j++) {
            temp[i][j] = (double)mat[i][j];
        }
    }

    double det = 1.0;
    for (int i = 0; i < n; i++) {
        int pivot = i;
        for (int k = i + 1; k < n; k++) {
            if (fabs(temp[k][i]) > fabs(temp[pivot][i])) {
                pivot = k;
            }
        }

        if (fabs(temp[pivot][i]) < 1e-9) {
            det = 0.0;
            break;
        }

        if (pivot != i) {
            double *swap_row = temp[i];
            temp[i] = temp[pivot];
            temp[pivot] = swap_row;
            det = -det;
        }

        det *= temp[i][i];

        for (int k = i + 1; k < n; k++) {
            double factor = temp[k][i] / temp[i][i];
            for (int j = i; j < n; j++) {
                temp[k][j] -= factor * temp[i][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(temp[i]);
    }
    free(temp);

    if (fabs(det) < 1e-9) {
        *det_out = 0.0;
    } else {
        *det_out = round(det);
    }

    return 1;
}

int compute_determinant_and_rank(int **mat, int rows, int cols, double *det, int *rank) {
    *rank = calculate_rank(mat, rows, cols);
    if (rows == cols) {
        return calculate_determinant(mat, rows, det);
    }
    return 0;
}

int main(void) {
    int rows;
    int cols;

    printf("Enter number of rows: ");
    if (scanf("%d", &rows) != 1 || rows <= 0) {
        printf("Invalid number of rows.\n");
        return 1;
    }

    printf("Enter number of columns: ");
    if (scanf("%d", &cols) != 1 || cols <= 0) {
        printf("Invalid number of columns.\n");
        return 1;
    }

    printf("Enter %d integer elements (%dx%d):\n", rows * cols, rows, cols);
    int **mat = input_matrix(rows, cols);
    if (mat == NULL) {
        printf("Failed to input matrix or allocate memory.\n");
        return 1;
    }

    printf("\nInput matrix:\n");
    print_matrix(mat, rows, cols);

    double det = 0.0;
    int rank = 0;
    int has_det = compute_determinant_and_rank(mat, rows, cols, &det, &rank);

    printf("\nMatrix rank: %d\n", rank);
    if (has_det) {
        printf("Matrix determinant: %.0f\n", det);
    } else {
        printf("Determinant is undefined (matrix is not square: %d != %d).\n", rows, cols);
    }

    free_matrix(mat, rows);

    return 0;
}