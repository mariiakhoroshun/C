#include <stdio.h>
#include <stdlib.h>

double **allocate_zero_matrix(int n) {
    if (n <= 0) {
        return NULL;
    }
    double **mat = (double **)malloc((size_t)n * sizeof(double *));
    if (mat == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        mat[i] = (double *)calloc((size_t)n, sizeof(double));
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

void free_matrix(double **mat, int n) {
    if (mat != NULL) {
        for (int i = 0; i < n; i++) {
            free(mat[i]);
        }
        free(mat);
    }
}

int input_matrix(double **mat, int n) {
    if (mat == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &mat[i][j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

double **multiply_matrices(double **a, double **b, int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }
    double **c = allocate_zero_matrix(n);
    if (c == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

void print_matrix(double **mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%10.4f ", mat[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    int n1;
    int n2;

    printf("Enter dimension of the first square matrix: ");
    if (scanf("%d", &n1) != 1 || n1 <= 0) {
        printf("Invalid dimension for the first matrix.\n");
        return 1;
    }

    double **mat1 = allocate_zero_matrix(n1);
    if (mat1 == NULL) {
        printf("Memory allocation failed for the first matrix.\n");
        return 1;
    }

    printf("Enter %d elements for the first matrix (%dx%d):\n", n1 * n1, n1, n1);
    if (!input_matrix(mat1, n1)) {
        printf("Failed to read the first matrix.\n");
        free_matrix(mat1, n1);
        return 1;
    }

    printf("Enter dimension of the second square matrix: ");
    if (scanf("%d", &n2) != 1 || n2 <= 0) {
        printf("Invalid dimension for the second matrix.\n");
        free_matrix(mat1, n1);
        return 1;
    }

    double **mat2 = allocate_zero_matrix(n2);
    if (mat2 == NULL) {
        printf("Memory allocation failed for the second matrix.\n");
        free_matrix(mat1, n1);
        return 1;
    }

    printf("Enter %d elements for the second matrix (%dx%d):\n", n2 * n2, n2, n2);
    if (!input_matrix(mat2, n2)) {
        printf("Failed to read the second matrix.\n");
        free_matrix(mat1, n1);
        free_matrix(mat2, n2);
        return 1;
    }

    if (n1 != n2) {
        printf("Multiplication is impossible: dimensions do not match (%d != %d).\n", n1, n2);
    } else {
        double **prod = multiply_matrices(mat1, mat2, n1);
        if (prod == NULL) {
            printf("Memory allocation failed for product matrix.\n");
        } else {
            printf("Product matrix (%dx%d):\n", n1, n1);
            print_matrix(prod, n1);
            free_matrix(prod, n1);
        }
    }

    free_matrix(mat1, n1);
    free_matrix(mat2, n2);

    return 0;
}