#include <stdio.h>

int main(void) {
    int arr[5] = {14, -3, 8, 0, 25};
    double value;

    printf("Enter a real number: ");
    if (scanf("%lf", &value) != 1) {
        return 1;
    }

    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (arr[i] < value) {
            count++;
        }
    }

    printf("Count of elements less than %f: %d\n", value, count);

    return 0;
}