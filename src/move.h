#ifndef MOVE_H
#define MOVE_H

#include "common.h"

bool valid_move(char *move, char color);
bool valid_rook_move(int rank_from, int file_from, int rank_to, int file_to);
bool valid_knight_move(int rank_from, int file_from, int rank_to, int file_to);
bool valid_bishop_move(int rank_from, int file_from, int rank_to, int file_to);
bool valid_queen_move(int rank_from, int file_from, int rank_to, int file_to);
bool valid_king_move(int rank_from, int file_from, int rank_to, int file_to);
bool valid_pawn_move(int rank_from, int file_from, int rank_to, int file_to);

#endif /* move.h */