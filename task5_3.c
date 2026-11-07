#include <stdio.h>

int collatz_steps(long long a) {
    int steps = 0;
    while (a > 1) {
        if (a % 2 == 0) {
            a = a / 2;
        } else {
            a = 3 * a + 1;
        }
        steps++;
    }
    return steps;
}

int main(void) {
    long long n;
    printf("Enter a natural number n: ");
    scanf("%lld", &n);

    long long a = n;
    int steps_n = 0;
    printf("Sequence: %lld ", a);
    while (a > 1) {
        if (a % 2 == 0) {
            a = a / 2;
        } else {
            a = 3 * a + 1;
        }
        printf("%lld ", a);
        steps_n++;
    }
    printf("\nSteps for n = %lld: %d\n\n", n, steps_n);

    int max_steps = -1;
    int best_n = 1;

    for (int i = 1; i < 1000; i++) {
        int current_steps = collatz_steps(i);
        if (current_steps > max_steps) {
            max_steps = current_steps;
            best_n = i;
        }
    }

    printf("For all n < 1000 the sequence converges to 1.\n");
    printf("Maximum steps for n < 1000: %d (at n = %d)\n", max_steps, best_n);

    return 0;
}