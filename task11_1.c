#include <stdio.h>
#include <stdlib.h>

double *allocate_array(int n) {
    return (double *)malloc((size_t)n * sizeof(double));
}

int input_array(double *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (scanf("%lf", &arr[i]) != 1) {
            return 0;
        }
    }
    return 1;
}

void free_array(double *arr) {
    free(arr);
}

int write_array_to_file(const char *filename, const double *arr, int n) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        return 0;
    }
    size_t written = fwrite(arr, sizeof(double), (size_t)n, file);
    if (fclose(file) != 0) {
        return 0;
    }
    return written == (size_t)n;
}

int print_file_contents(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0;
    }
    double value;
    int first = 1;
    while (fread(&value, sizeof(double), 1, file) == 1) {
        if (!first) {
            printf(", ");
        }
        printf("%g", value);
        first = 0;
    }
    printf("\n");
    int has_error = ferror(file);
    fclose(file);
    return !has_error;
}

int main(void) {
    int n;
    printf("Enter array length: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid array length.\n");
        return 1;
    }

    double *arr = allocate_array(n);
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter %d real numbers:\n", n);
    if (!input_array(arr, n)) {
        printf("Invalid array input.\n");
        free_array(arr);
        return 1;
    }

    char filename[256];
    printf("Enter binary file name: ");
    if (scanf("%255s", filename) != 1) {
        printf("Invalid file name.\n");
        free_array(arr);
        return 1;
    }

    if (!write_array_to_file(filename, arr, n)) {
        printf("Error writing to file.\n");
        free_array(arr);
        return 1;
    }

    printf("File contents: ");
    if (!print_file_contents(filename)) {
        printf("Error reading from file.\n");
        free_array(arr);
        return 1;
    }

    free_array(arr);
    return 0;
}