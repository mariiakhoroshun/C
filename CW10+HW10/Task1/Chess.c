#include "Chess.h"
#include <stdio.h>

bool input_chess_square(ChessSquare *sq) {
    if (sq == NULL) {
        return false;
    }
    printf("Enter chess square (letter a-h and digit 1-8, e.g. a5): ");
    if (scanf(" %c%d", &sq->col, &sq->row) != 2) {
        return false;
    }
    if (sq->col >= 'A' && sq->col <= 'H') {
        sq->col = sq->col - 'A' + 'a';
    }
    if (sq->col < 'a' || sq->col > 'h' || sq->row < 1 || sq->row > 8) {
        return false;
    }
    return true;
}

void print_chess_square(const ChessSquare *sq) {
    if (sq == NULL) {
        return;
    }
    printf("%c%d\n", sq->col, sq->row);
}