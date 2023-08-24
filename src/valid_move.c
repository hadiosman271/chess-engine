#include "valid_move.h"

// Absolute value of an integer
int abs(int x)
{
    return x >= 0 ? x : -x;
}

bool valid_rook_move(int rank_from, int file_from, int rank_to, int file_to)
{
    if (rank_from == rank_to)
    {
        int dir = file_to > file_from ? 1 : -1;
        for (int file = file_from + dir; file != file_to; file += dir)
        {
            if (board[rank_from][file] != '\0')
            {
                return false;
            }
        }
    }
    else if (file_from == file_to)
    {
        int dir = rank_to > rank_from ? 1 : -1;
        for (int rank = rank_from + dir; rank != rank_to; rank += dir)
        {
            if (board[rank][file_from] != '\0')
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

bool valid_knight_move(int rank_from, int file_from, int rank_to, int file_to)
{
    return (abs(rank_to - rank_from) == 2 && abs(file_to - file_from) == 1)
        || (abs(rank_to - rank_from) == 1 && abs(file_to - file_from) == 2);
}

bool valid_bishop_move(int rank_from, int file_from, int rank_to, int file_to)
{
    if (abs(rank_to - rank_from) != abs(file_to - file_from))
    {
        return false;
    }
    int rank_dir = rank_to > rank_from ? 1 : -1;
    int file_dir = file_to > file_from ? 1 : -1;
    for (int rank = rank_from + rank_dir, file = file_from + file_dir;
         rank != rank_to && file != file_to;
         rank += rank_dir, file += file_dir)
    {
        if (board[rank][file] != '\0')
        {
            return false;
        }
    }

    return true;
}

bool valid_queen_move(int rank_from, int file_from, int rank_to, int file_to)
{
    return valid_rook_move(rank_from, file_from, rank_to, file_to)
        || valid_bishop_move(rank_from, file_from, rank_to, file_to);
}

bool valid_king_move(int rank_from, int file_from, int rank_to, int file_to)
{
    return abs(rank_to - rank_from) <= 1 && abs(file_to - file_from) <= 1;
}

bool valid_pawn_move(int rank_from, int file_from, int rank_to, int file_to)
{
    switch (abs(rank_to - rank_from))
    {
    case 1:
        switch (abs(file_to - file_from))
        {
        case 0:
            // Can't capture forwards
            if (board[rank_to][file_to] != '\0')
            {
                return false;
            }
            // TODO: Promotion
            break;
        case 1:
            // Can capture diagonally forwards
            if (board[rank_to][file_to] == '\0')
            {
                return false;
            }
            // TODO: en passant
            break;
        default:
            return false;
        }
        break;
    case 2:
        // Can only move 2 squares when on the 2nd rank
        if (abs(file_to - file_from) == 0 && board[rank_to][file_to] == '\0')
        {
            if (turn == 'w')
            {
                if (rank_from != 1 || rank_to < rank_from)
                {
                    return false;
                }
            }
            else if (turn == 'b')
            {
                if (rank_from != 6 || rank_to > rank_from)
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        break;
    default:
        return false;
    }

    return true;
}

// Returns false if the move string is invalid
bool valid_move(char *move)
{
    if (strlen(move) != 4)
    {
        return false;
    }

    if (turn != 'w' && turn != 'b')
    {
        fprintf(stderr, "Wrong color %c\n", turn);
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
        || file_to < 0 || file_to >= SIZE)
    {
        fprintf(stderr, "Coordinate out of range\n");
        return false;
    }

    // If there is no piece on the start square
    if (board[rank_from][file_from] == '\0')
    {
        fprintf(stderr, "No piece on %c%c\n", move[0], move[1]);
        return false;
    }

    // If the start square has the wrong piece color
    if (islower(board[rank_from][file_from]) && turn != 'b'
        || isupper(board[rank_from][file_from]) && turn != 'w')
    {
        fprintf(stderr, "Wrong piece color\n");
        return false;
    }

    // If both squares are occupied by pieces of the same color
    if (islower(board[rank_from][file_from]) == islower(board[rank_to][file_to])
        && isupper(board[rank_from][file_from]) == isupper(board[rank_to][file_to]))
    {
        fprintf(stderr, "Cannot capture own pieces\n");
        return false;
    }

    // Check if move breaks the rules for its piece type
    bool (*valid_piece_move[])(int, int, int, int) = {
        valid_rook_move, valid_knight_move, valid_bishop_move,
        valid_queen_move, valid_king_move, valid_pawn_move
    };
    char type = tolower(board[rank_from][file_from]);
    return valid_piece_move[strchr(piece_types, type) - piece_types](rank_from, file_from, rank_to, file_to);

    // TODO: Check if move leaves king in check
}