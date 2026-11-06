#include <stdio.h>

#define SIZE 5

void input_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("Enter element [%d]: ", i);
        scanf("%d", &arr[i]);
    }
}

int find_max(int arr[], int size) {
    int max_val = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main(void) {
    int arr[SIZE];

    printf("Enter %d integers:\n", SIZE);
    input_array(arr, SIZE);

    int max_val = find_max(arr, SIZE);
    printf("Maximum value: %d\n", max_val);

    return 0;
}