#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


long long fibonacci_by_index(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long prev = 0;
    long long curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}


int max_fibonacci_index_not_exceeding(long long a) {
    if (a < 0) return -1;
    if (a == 0) return 0;

    long long prev = 0;
    long long curr = 1;
    int index = 1;

    while (prev + curr <= a) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
        index++;
    }
    return index;
}


int min_fibonacci_index_greater(long long a) {
    if (a < 0) return 0;

    long long prev = 0;
    long long curr = 1;
    int index = 1;

    while (curr <= a) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
        index++;
    }
    return index;
}

long long sum_fibonacci_up_to_1000(void) {
    long long sum = 0;
    long long prev = 0;
    long long curr = 1;

    sum += prev;

    while (curr <= 1000) {
        sum += curr;
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return sum;
}

int main(void) {
    long long a;
    printf("Input a: ");
    if (scanf("%lld", &a) != 1) {
        printf("Error input.\n");
        return 1;
    }

    int n_test = (int)a;
    if (n_test >= 0) {
        printf("a) F_%d = %lld\n", n_test, fibonacci_by_index(n_test));
    }

    int idx_b = max_fibonacci_index_not_exceeding(a);
    if (idx_b != -1) {
        printf("b) Max index with F_k <= %lld is: %d (value: %lld)\n", 
               a, idx_b, fibonacci_by_index(idx_b));
    } else {
        printf("b) No Fibonacci number <= %lld\n", a);
    }

    int idx_v = min_fibonacci_index_greater(a);
    printf("c) Min index with F_k > %lld is: %d (value: %lld)\n", 
           a, idx_v, fibonacci_by_index(idx_v));

    printf("d) Sum of Fibonacci numbers <= 1000: %lld\n", sum_fibonacci_up_to_1000());

    return 0;
}