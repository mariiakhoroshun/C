#include <stdio.h>
#include <stdbool.h>
#include "Ratio.h"

void test_rational(void) {
    Rational r_raw = {-6, 8};
    Rational r_red = reduce_rational(r_raw);
    bool t1 = (r_red.numerator == -3 && r_red.denominator == 4);

    Rational a = {1, 2};
    Rational b = {1, 3};
    Rational s1 = add_rational(a, b);
    bool t2 = (s1.numerator == 5 && s1.denominator == 6);

    Rational c = {-1, 4};
    Rational d = {3, 4};
    Rational s2 = add_rational(c, d);
    bool t3 = (s2.numerator == 1 && s2.denominator == 2);

    Rational m = multiply_rational((Rational){2, 3}, (Rational){3, 4});
    bool t4 = (m.numerator == 1 && m.denominator == 2);

    bool t5 = (compare_rational(a, b) == 1 &&
               compare_rational(b, a) == -1 &&
               compare_rational((Rational){2, 4}, a) == 0);

    printf("--- Automated Tests (Rational) ---\n");
    printf("Test 1 (reduce -6/8 -> -3/4): %s\n", t1 ? "PASSED" : "FAILED");
    printf("Test 2 (add 1/2 + 1/3 -> 5/6): %s\n", t2 ? "PASSED" : "FAILED");
    printf("Test 3 (add -1/4 + 3/4 -> 1/2): %s\n", t3 ? "PASSED" : "FAILED");
    printf("Test 4 (multiply 2/3 * 3/4 -> 1/2): %s\n", t4 ? "PASSED" : "FAILED");
    printf("Test 5 (compare fractions): %s\n", t5 ? "PASSED" : "FAILED");
    printf("------------------------------------\n\n");
}

int main(void) {
    test_rational();

    Rational r1, r2;

    printf("Enter first rational number (numerator denominator, e.g. -6 8): ");
    if (!input_rational(&r1)) {
        printf("Invalid rational number.\n");
        return 1;
    }

    printf("Enter second rational number (numerator denominator, e.g. 3 4): ");
    if (!input_rational(&r2)) {
        printf("Invalid rational number.\n");
        return 1;
    }

    printf("First reduced: ");
    print_rational(reduce_rational(r1));
    printf("\nSecond reduced: ");
    print_rational(reduce_rational(r2));
    printf("\n");

    Rational sum = add_rational(r1, r2);
    printf("Sum: ");
    print_rational(sum);
    printf("\n");

    Rational prod = multiply_rational(r1, r2);
    printf("Product: ");
    print_rational(prod);
    printf("\n");

    int cmp = compare_rational(r1, r2);
    printf("Comparison: ");
    print_comparison(r1, r2, cmp);

    return 0;
}