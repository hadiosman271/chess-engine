#ifndef VALID_MOVE_H
#define VALID_MOVE_H

#include "common.h"

int abs(int x);
void get_coords(char *move, int *rank_from, int *file_from, int *rank_to, int *file_to);
bool valid_rook_move(char *move);
bool valid_knight_move(char *move);
bool valid_bishop_move(char *move);
bool valid_queen_move(char *move);
bool valid_king_move(char *move);
bool valid_pawn_move(char *move);
bool valid_move(char *move);

#endif /* valid_move.h */