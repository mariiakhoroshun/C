#include <stdio.h>
#include <math.h>

void print_fuctorial(unsigned n){
    printf("%u!=", n);
    for (unsigned i = 1; i < n; i++) {
        printf("%u*", i);
    }
    printf("%u\n", n);
}

void print_fuctorial_inverse(unsigned n){
    printf("%u!=", n);
    for (unsigned i = n; i > 1; i--) {
        printf("%u*", i);
    }
    printf("1\n");
}

int main(){
    unsigned n;
    printf("Enter a value for n: ");
    scanf("%u", &n);
    print_fuctorial(n);
    print_fuctorial_inverse(n);
    return 0;
}