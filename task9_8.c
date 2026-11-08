#include <stdio.h>
#include <stdlib.h>

double *allocate_vector(int n) {
    if (n <= 0) {
        return NULL;
    }
    return (double *)malloc((size_t)n * sizeof(double));
}

void free_vector(double *vec) {
    free(vec);
}

int input_vector(double *vec, int n) {
    if (vec == NULL || n <= 0) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &vec[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

double *append_elements(double *arr, int current_size, const double *new_batch, int batch_size) {
    int new_size = current_size + batch_size;
    double *new_arr = (double *)malloc((size_t)new_size * sizeof(double));
    if (new_arr == NULL) {
        return NULL;
    }
    for (int i = 0; i < current_size; i++) {
        new_arr[i] = arr[i];
    }
    for (int i = 0; i < batch_size; i++) {
        new_arr[current_size + i] = new_batch[i];
    }
    free(arr);
    return new_arr;
}

double calculate_mean(const double *arr, int n) {
    if (arr == NULL || n <= 0) {
        return 0.0;
    }
    double sum = 0.0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum / (double)n;
}

double calculate_variance(const double *arr, int n, double mean) {
    if (arr == NULL || n <= 0) {
        return 0.0;
    }
    double sum_sq_diff = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = arr[i] - mean;
        sum_sq_diff += diff * diff;
    }
    return sum_sq_diff / (double)n;
}

int main(void) {
    double *all_values = NULL;
    int total_count = 0;

    while (1) {
        int n;
        printf("Enter vector dimension (0 to exit): ");
        if (scanf("%d", &n) != 1 || n <= 0) {
            break;
        }

        double *batch = allocate_vector(n);
        if (batch == NULL) {
            printf("Memory allocation failed for current vector.\n");
            free_vector(all_values);
            return 1;
        }

        printf("Enter %d real numbers:\n", n);
        if (!input_vector(batch, n)) {
            printf("Failed to read vector elements.\n");
            free_vector(batch);
            free_vector(all_values);
            return 1;
        }

        double *updated_all = append_elements(all_values, total_count, batch, n);
        if (updated_all == NULL) {
            printf("Memory allocation failed while expanding dataset.\n");
            free_vector(batch);
            free_vector(all_values);
            return 1;
        }

        all_values = updated_all;
        total_count += n;

        double total_mean = calculate_mean(all_values, total_count);
        double total_var = calculate_variance(all_values, total_count, total_mean);

        printf("Mean of all values: %.6f\n", total_mean);
        printf("Variance of all values: %.6f\n\n", total_var);

        free_vector(batch);
    }

    free_vector(all_values);

    return 0;
}