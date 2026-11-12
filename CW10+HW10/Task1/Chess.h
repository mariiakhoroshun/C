#ifndef CHESS_H
#define CHESS_H

#include <stdbool.h>

typedef struct {
    char col;
    int row;
} ChessSquare;

bool input_chess_square(ChessSquare *sq);
void print_chess_square(const ChessSquare *sq);

#endif