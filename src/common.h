#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Size of the board
#define SIZE 8

extern char *piece_types;
extern char turn;
extern char board[SIZE][SIZE];

#endif /* common.h */