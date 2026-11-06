#include <stdio.h>
#include <math.h>

#define MAX_N 100

int is_cube_and_multiple_of_3(int x) {
    if (x <= 0 || x % 3 != 0) {
        return 0;
    }
    int r = (int)round(cbrt((double)x));
    if ((long long)r * r * r == x) {
        return 1;
    }
    return 0;
}

int count_cubes_mult_3(int arr[], int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (is_cube_and_multiple_of_3(arr[i])) {
            count++;
        }
    }
    return count;
}

int main(void) {
    int n;
    int arr[MAX_N];

    printf("Enter array size N (1 <= N <= %d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d natural numbers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    int result = count_cubes_mult_3(arr, n);
    printf("Count of numbers multiple of 3 and perfect cubes: %d\n", result);

    return 0;
}