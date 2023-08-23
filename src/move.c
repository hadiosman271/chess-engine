#include "move.h"

bool valid_rook_move(int rank_from, int file_from, int rank_to, int file_to) {
    if (rank_from == rank_to) {
        int dir = file_from > file_to ? -1 : 1;
        for (int file = file_from + dir; file != file_to; file += dir) {
            if (board[rank_from][file] != '\0') {
                fprintf(stderr, "Path is blocked\n");
                return false;
            }
        }
    }
    else if (file_from == file_to) {
        int dir = rank_from > rank_to ? -1 : 1;
        for (int rank = rank_from + dir; rank != rank_to; rank += dir) {
            if (board[rank][file_from] != '\0') {
                fprintf(stderr, "Path is blocked\n");
                return false;
            }
        }
    }
    else {
        fprintf(stderr, "The tower dosen't move like that\n");
        return false;
    }
    return true;
}

bool valid_knight_move(int rank_from, int file_from, int rank_to, int file_to) {
    return true;
}

bool valid_bishop_move(int rank_from, int file_from, int rank_to, int file_to) {
    return true;
}

bool valid_queen_move(int rank_from, int file_from, int rank_to, int file_to) {
    return true;
}

bool valid_king_move(int rank_from, int file_from, int rank_to, int file_to) {
    return true;
}

bool valid_pawn_move(int rank_from, int file_from, int rank_to, int file_to) {
    return true;
}

// Returns false if the move string is valid
bool valid_move(char *move, char color) {
    if (strlen(move) != 4) {
        return false;
    }

    // Get the coordinates from the string
    int rank_from = move[1] - '0' - 1;
    int file_from = move[0] - 'a';
    int rank_to = move[3] - '0' - 1;
    int file_to = move[2] - 'a';

    // If any coordinate is out of range
    if (rank_from < 0 || rank_from >= SIZE
        || file_from < 0 || file_from >= SIZE
        || rank_to < 0 || rank_to >= SIZE
        || file_to < 0 || file_to >= SIZE) {
        fprintf(stderr, "Coordinate out of range\n");
        return false;
    }

    // If there is no piece on the start square
    if (board[rank_from][file_from] == '\0') {
        fprintf(stderr, "No piece on %c%c\n", move[0], move[1]);
        return false;
    }

    // If the start square has the wrong piece color
    if (islower(board[rank_from][file_from]) && color != 'b'
        || isupper(board[rank_from][file_from]) && color != 'w') {
        fprintf(stderr, "Wrong piece color\n");
        return false;
    }

    // If both squares are occupied by pieces of the same color
    if (islower(board[rank_from][file_from]) == islower(board[rank_to][file_to])
        && isupper(board[rank_from][file_from]) == isupper(board[rank_to][file_to])) {
        fprintf(stderr, "Cannot capture own pieces\n");
        return false;
    }

    // Check if move breaks the rules for its piece type
    char type = tolower(board[rank_from][file_from]);
    switch (type) {
    case 'r':
        return valid_rook_move(rank_from, file_from, rank_to, file_to);
    case 'n':
        return valid_knight_move(rank_from, file_from, rank_to, file_to);
    case 'b':
        return valid_bishop_move(rank_from, file_from, rank_to, file_to);
    case 'q':
        return valid_queen_move(rank_from, file_from, rank_to, file_to);
    case 'k':
        return valid_king_move(rank_from, file_from, rank_to, file_to);
    case 'p':
        return valid_pawn_move(rank_from, file_from, rank_to, file_to);
    default:
        return false;
    }
}