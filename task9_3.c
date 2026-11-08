#include <stdio.h>
#include <stdlib.h>

double *input_vector(int n) {
    if (n <= 0) {
        return NULL;
    }
    double *vec = (double *)malloc((size_t)n * sizeof(double));
    if (vec == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &vec[i]) != 1) {
            free(vec);
            return NULL;
        }
    }
    return vec;
}

void free_vector(double *vec) {
    free(vec);
}

double *subtract_vectors(const double *a, const double *b, int n) {
    if (a == NULL || b == NULL || n <= 0) {
        return NULL;
    }
    double *diff = (double *)malloc((size_t)n * sizeof(double));
    if (diff == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        diff[i] = a[i] - b[i];
    }
    return diff;
}

void print_vector(const double *vec, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.4f ", vec[i]);
    }
    printf("\n");
}

int main(void) {
    int n1;
    int n2;

    printf("Enter dimension of the first vector: ");
    if (scanf("%d", &n1) != 1 || n1 <= 0) {
        printf("Invalid dimension for the first vector.\n");
        return 1;
    }

    printf("Enter %d real numbers for the first vector:\n", n1);
    double *v1 = input_vector(n1);
    if (v1 == NULL) {
        printf("Failed to read the first vector.\n");
        return 1;
    }

    printf("Enter dimension of the second vector: ");
    if (scanf("%d", &n2) != 1 || n2 <= 0) {
        printf("Invalid dimension for the second vector.\n");
        free_vector(v1);
        return 1;
    }

    printf("Enter %d real numbers for the second vector:\n", n2);
    double *v2 = input_vector(n2);
    if (v2 == NULL) {
        printf("Failed to read the second vector.\n");
        free_vector(v1);
        return 1;
    }

    if (n1 != n2) {
        printf("Subtraction is impossible: dimensions do not match (%d != %d).\n", n1, n2);
    } else {
        double *diff = subtract_vectors(v1, v2, n1);
        if (diff == NULL) {
            printf("Memory allocation failed for the difference vector.\n");
        } else {
            printf("Difference vector (v1 - v2):\n");
            print_vector(diff, n1);
            free_vector(diff);
        }
    }

    free_vector(v1);
    free_vector(v2);

    return 0;
}