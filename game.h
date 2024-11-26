#ifndef GAME_H
#define GAME_H

#include "cell.h"

// Function declarations
void init_game(struct cell board[15][15]);
void print_board(struct cell board[15][15]);
void calculate_game(struct cell board[15][15]);
void future_board(struct cell board[15][15]);
int count_neighbours(int i, int j, struct cell board[15][15]); 

#endif
