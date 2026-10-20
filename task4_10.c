#include <stdio.h>
#include <float.h>

float find_machine_zero() {
    float a = 1.0f;
    while (1.0f + a != 1.0f) {
        a /= 2.0f;
    }
    return a;
}

int main() {

    float a = find_machine_zero();
    printf("Calculated a (where 1 + a == 1): %e\n", a);
    printf("Standard FLT_EPSILON (<float.h>): %e\n", FLT_EPSILON);

    return 0;
}