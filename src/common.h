#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Size of the board
#define SIZE 8

extern char *piece_types;
extern char board[SIZE][SIZE];
extern char turn;
extern char ep_square[3];
extern char castling_rights[5];
extern int half_moves, full_moves;

#endif /* common.h */