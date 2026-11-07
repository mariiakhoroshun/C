#include <stdio.h>
#include <math.h>

#define MAX_N 100

int find_min(int arr[], int n) {
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

int find_max(int arr[], int n) {
    int max_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int find_closest_to_extrema_avg(int arr[], int n, double *avg_out) {
    int min_val = find_min(arr, n);
    int max_val = find_max(arr, n);
    double avg = (double)(min_val + max_val) / 2.0;

    if (avg_out != NULL) {
        *avg_out = avg;
    }

    int closest_elem = arr[0];
    double min_diff = fabs((double)arr[0] - avg);

    for (int i = 1; i < n; i++) {
        double diff = fabs((double)arr[i] - avg);
        if (diff < min_diff) {
            min_diff = diff;
            closest_elem = arr[i];
        }
    }

    return closest_elem;
}

int main(void) {
    int n;
    int a[MAX_N];

    printf("Enter array size N (1 <= N <= %d): ", MAX_N);
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_N) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) {
        printf("A[%d] = ", i);
        scanf("%d", &a[i]);
    }

    int min_val = find_min(a, n);
    int max_val = find_max(a, n);
    double avg = (double)(min_val + max_val) / 2.0;

    int closest = a[0];
    double min_diff = fabs((double)a[0] - avg);

    for (int i = 1; i < n; i++) {
        double diff = fabs((double)a[i] - avg);
        if (diff < min_diff) {
            min_diff = diff;
            closest = a[i];
        }
    }

    printf("Min element: %d\n", min_val);
    printf("Max element: %d\n", max_val);
    printf("Average of min and max: %.4f\n", avg);
    printf("Closest element in array: %d\n", closest);

    return 0;
}