#include <stdio.h>
#include <stdbool.h>
#include "Chess.h"

void test_chess(void) {
    ChessSquare s1 = {'a', 1};
    ChessSquare s2 = {'a', 8};
    ChessSquare s3 = {'h', 8};
    ChessSquare s4 = {'c', 2};

    bool t1 = (can_queen_move(s1, s2) == true);
    bool t2 = (can_queen_move(s2, s3) == true);
    bool t3 = (can_queen_move(s1, s3) == true);
    bool t4 = (can_queen_move(s1, s4) == false);
    bool t5 = (can_queen_move(s1, s1) == false);

    printf("--- Automated Tests ---\n");
    printf("Test 1 (vertical a1 -> a8): %s\n", t1 ? "PASSED" : "FAILED");
    printf("Test 2 (horizontal a8 -> h8): %s\n", t2 ? "PASSED" : "FAILED");
    printf("Test 3 (diagonal a1 -> h8): %s\n", t3 ? "PASSED" : "FAILED");
    printf("Test 4 (invalid a1 -> c2): %s\n", t4 ? "PASSED" : "FAILED");
    printf("Test 5 (same square a1 -> a1): %s\n", t5 ? "PASSED" : "FAILED");
    printf("-----------------------\n\n");
}

int main(void) {
    test_chess();

    ChessSquare start, target;

    printf("Enter starting square (letter a-h and digit 1-8, e.g. a5): ");
    if (!input_chess_square(&start)) {
        printf("Invalid starting square.\n");
        return 1;
    }

    printf("Enter target square (letter a-h and digit 1-8, e.g. b8): ");
    if (!input_chess_square(&target)) {
        printf("Invalid target square.\n");
        return 1;
    }

    printf("From ");
    print_chess_square(&start);
    printf(" to ");
    print_chess_square(&target);

    if (can_queen_move(start, target)) {
        printf(": queen CAN move in one step.\n");
    } else {
        printf(": queen CANNOT move in one step.\n");
    }

    return 0;
}