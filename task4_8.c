#include <stdio.h>

int max_4(unsigned m){
    unsigned a = 1;
    int k=0;
    while (a <= m) {
        a = a*4;
        k++;
    }
    return k-1;
}

int main() {
    unsigned m;
    printf("Enter a value for m: ");
    scanf("%u", &m);

    int max_k = max_4(m);
    printf("Result = %d\n", max_k);
    return 0;
}