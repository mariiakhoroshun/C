#include <stdio.h>

#define MAX_SIZE 50

void count_even_odd(int arr[], int size, int counts[]) {
    counts[0] = 0;
    counts[1] = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 == 0) {
            counts[0]++;
        } else {
            counts[1]++;
        }
    }
}

int main(void) {
    int arr[MAX_SIZE];
    int size = 0;
    int num;

    printf("Enter natural numbers (0 to finish, max %d):\n", MAX_SIZE);
    while (size < MAX_SIZE) {
        if (scanf("%d", &num) != 1 || num == 0) {
            break;
        }
        if (num > 0) {
            arr[size] = num;
            size++;
        }
    }

    int counts[2] = {0, 0};
    count_even_odd(arr, size, counts);

    printf("Total numbers: %d\n", size);
    printf("Even numbers count: %d\n", counts[0]);
    printf("Odd numbers count: %d\n", counts[1]);

    return 0;
}