#include <stdio.h>

int main() {
    int a;

    printf("Input integer a: ");
    scanf("%d", &a);

    printf("\n");
    printf("- %d - %d - %d\n", a, a, a);
    printf(" %d | %d | %d\n", a, a, a);
    printf("- %d - %d - %d\n", a, a, a);

    return 0;
}