#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *allocate_array(int size) {
    return (int *)malloc((size_t)size * sizeof(int));
}

void free_array(int *arr) {
    free(arr);
}

int is_perfect_square(int n) {
    if (n < 0) {
        return 0;
    }
    int r = (int)round(sqrt((double)n));
    return ((long long)r * r == n);
}

int is_perfect_cube(int n) {
    int r = (int)round(cbrt((double)n));
    return ((long long)r * r * r == n);
}

int input_array(int *arr, int max_size) {
    int count = 0;
    int val;
    while (count < max_size) {
        if (scanf("%d", &val) != 1 || val == 0) {
            break;
        }
        arr[count] = val;
        count++;
    }
    return count;
}

void count_squares_and_cubes(const int *arr, int size, int *squares, int *cubes) {
    *squares = 0;
    *cubes = 0;
    for (int i = 0; i < size; i++) {
        if (is_perfect_square(arr[i])) {
            (*squares)++;
        }
        if (is_perfect_cube(arr[i])) {
            (*cubes)++;
        }
    }
}

int main(void) {
    int *arr = allocate_array(100);
    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter integers (0 to terminate, max 100):\n");
    int count = input_array(arr, 100);

    int squares = 0;
    int cubes = 0;
    count_squares_and_cubes(arr, count, &squares, &cubes);

    printf("Total elements read: %d\n", count);
    printf("Count of perfect squares: %d\n", squares);
    printf("Count of perfect cubes: %d\n", cubes);

    free_array(arr);

    return 0;
}