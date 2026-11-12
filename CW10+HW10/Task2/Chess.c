#include "Chess.h"
#include <stdio.h>
#include <stdlib.h>

bool input_chess_square(ChessSquare *sq) {
    if (sq == NULL) {
        return false;
    }
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
    printf("%c%d", sq->col, sq->row);
}

bool can_queen_move(ChessSquare from, ChessSquare to) {
    int d_col = abs(from.col - to.col);
    int d_row = abs(from.row - to.row);

    if (d_col == 0 && d_row == 0) {
        return false;
    }

    return (d_col == 0 || d_row == 0 || d_col == d_row);
}