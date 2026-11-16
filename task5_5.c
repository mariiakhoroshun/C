#include <stdio.h>

int main(void) {
    int x1 = -99, x2 = -99, x3 = -99;
    int xn = -99;
    int n = 3;

    while (xn <= 0) {
        n++;
        xn = x3 + x1 + 100;
        x1 = x2;
        x2 = x3;
        x3 = xn;
    }

    printf("Smallest positive term: x_%d = %d (index n = %d)\n", n, xn, n);

    return 0;
}