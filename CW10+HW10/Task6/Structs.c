#include <stdio.h>
#include <stdbool.h>
#include "Sphere.h"

void test_sphere(void) {
    Sphere s_test = {{1.0, -2.0, 0.0}, 9.0};
    bool t1 = (s_test.center.x == 1.0 && s_test.center.y == -2.0 &&
               s_test.center.z == 0.0 && s_test.radius_sq == 9.0);
    bool t2 = (!input_point3d(NULL) && !input_sphere(NULL));

    printf("--- Automated Tests (Sphere) ---\n");
    printf("Test 1 (struct initialization): %s\n", t1 ? "PASSED" : "FAILED");
    print_sphere(&s_test);
    printf("Test 2 (NULL safety): %s\n", t2 ? "PASSED" : "FAILED");
    printf("--------------------------------\n\n");
}

int main(void) {
    test_sphere();

    Sphere s;
    if (!input_sphere(&s)) {
        printf("Invalid sphere parameters.\n");
        return 1;
    }

    print_sphere(&s);

    return 0;
}