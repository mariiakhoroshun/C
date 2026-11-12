#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char col;
    int row;
} ChessSquare;

bool input_chess_square(ChessSquare *sq) {
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

bool can_queen_move(ChessSquare from, ChessSquare to) {
    int d_col = abs(from.col - to.col);
    int d_row = abs(from.row - to.row);

    if (d_col == 0 && d_row == 0) {
        return false;
    }

    return (d_col == 0 || d_row == 0 || d_col == d_row);
}

int main(void) {
    ChessSquare start, target;

    printf("Enter starting square (e.g. a5): ");
    if (!input_chess_square(&start)) {
        printf("Invalid starting square.\n");
        return 1;
    }

    printf("Enter target square (e.g. b8): ");
    if (!input_chess_square(&target)) {
        printf("Invalid target square.\n");
        return 1;
    }

    if (can_queen_move(start, target)) {
        printf("Yes, the queen can move from %c%d to %c%d in one move.\n",
               start.col, start.row, target.col, target.row);
    } else {
        printf("No, the queen cannot move from %c%d to %c%d in one move.\n",
               start.col, start.row, target.col, target.row);
    }

    return 0;
}