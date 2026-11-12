#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Date.h"
#include "Chess.h"
#include "Geometry.h"
#include "Polynome.h"

void test_task1(void) {
    printf("--- Automated Tests (Task 1) ---\n");

    Date d_test = {29, 2, 2024};
    bool date_ok = (d_test.day == 29 && d_test.month == 2 && d_test.year == 2024);
    printf("Test 1a (Date): %s -> ", date_ok ? "PASSED" : "FAILED");
    print_date(&d_test);

    ChessSquare sq_test = {'e', 4};
    bool sq_ok = (sq_test.col == 'e' && sq_test.row == 4);
    printf("Test 1b (ChessSquare): %s -> ", sq_ok ? "PASSED" : "FAILED");
    print_chess_square(&sq_test);

    Rectangle rect_test = {{0.0, 0.0}, {4.0, 3.0}};
    bool rect_ok = (rect_test.v1.x == 0.0 && rect_test.v1.y == 0.0 &&
                    rect_test.v2.x == 4.0 && rect_test.v2.y == 3.0);
    printf("Test 1c (Rectangle): %s -> ", rect_ok ? "PASSED" : "FAILED");
    print_rectangle(&rect_test);

    Polynome poly_test;
    poly_test.degree = 2;
    poly_test.coeffs = (double *)malloc(3 * sizeof(double));
    bool poly_ok = false;
    if (poly_test.coeffs != NULL) {
        poly_test.coeffs[0] = 1.0;
        poly_test.coeffs[1] = -3.0;
        poly_test.coeffs[2] = 2.0;
        poly_ok = (poly_test.degree == 2 && poly_test.coeffs[0] == 1.0 &&
                   poly_test.coeffs[1] == -3.0 && poly_test.coeffs[2] == 2.0);
    }
    printf("Test 1d (Polynome): %s -> ", poly_ok ? "PASSED" : "FAILED");
    print_polynome(&poly_test);

    free_polynome(&poly_test);
    bool free_ok = (poly_test.coeffs == NULL && poly_test.degree == 0);
    printf("Test 1d (Polynome free): %s\n", free_ok ? "PASSED" : "FAILED");

    bool null_ok = (!input_date(NULL) && !input_chess_square(NULL) &&
                    !input_rectangle(NULL) && !input_polynome(NULL));
    printf("Test 1e (NULL safety): %s\n", null_ok ? "PASSED" : "FAILED");

    printf("--------------------------------\n\n");
}

int main(void) {
    test_task1();

    Date d;
    printf("--- Task 1a: Date ---\n");
    if (!input_date(&d)) {
        printf("Invalid date.\n");
        return 1;
    }
    printf("Entered date: ");
    print_date(&d);

    ChessSquare sq;
    printf("\n--- Task 1b: Chess Square ---\n");
    if (!input_chess_square(&sq)) {
        printf("Invalid chess square.\n");
        return 1;
    }
    printf("Entered square: ");
    print_chess_square(&sq);

    Rectangle rect;
    printf("\n--- Task 1c: Rectangle ---\n");
    if (!input_rectangle(&rect)) {
        printf("Invalid rectangle.\n");
        return 1;
    }
    print_rectangle(&rect);

    Polynome poly;
    printf("\n--- Task 1d: Polynomial ---\n");
    if (!input_polynome(&poly)) {
        printf("Invalid polynomial.\n");
        return 1;
    }
    print_polynome(&poly);
    free_polynome(&poly);

    return 0;
}