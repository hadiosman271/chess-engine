#include "fen.h"

void load_fen(char *fen)
{
    if (!valid_fen(fen))
    {
        fprintf(stderr, "Error: Invalid FEN\n");
        return;
    }

    char placements[72];
    sscanf(fen, "%71s %c %4s %2s %d %d",
        placements, &turn, castling_rights, ep_square, &half_moves, &full_moves);

    int rank = SIZE - 1, file = 0;
    for (char *p = placements; *p != '\0'; p++)
    {
        char c = *p;
        if (isalpha(c))
        {
            board[rank][file++] = c;
        }
        else if (isdigit(c))
        {
            file += c - '0';
        }

        if (file == SIZE)
        {
            rank--;
            file = 0;
        }
    }
}

// Returns false if the FEN string is invalid
bool valid_fen(char *fen)
{
    char placements[72], turn, castling_rights[5], ep_square[3];
    int half_moves, full_moves;
    if (sscanf(fen, "%71s %c %4s %2s %d %d",
        placements, &turn, castling_rights, ep_square, &half_moves, &full_moves)
        != 6)
    {
        return false;
    }

    // Check the piece placements
    int rank = 1;
    int file = 0;
    for (char *p = placements; *p != '\0'; p++)
    {
        char c = *p;
        if (isalpha(c) && strchr(piece_types, tolower(c)))
        {
            file++;
        }
        else if (isdigit(c) && c != '0')
        {
            file += c - '0';
        }
        else if (c == '/')
        {
            if (file != SIZE)
            {
                return false;
            }
            file = 0;
            rank++;
        }
        else
        {
            return false;
        }
    }

    // Check the color
    if (turn != 'w' && turn != 'b')
    {
        return false;
    }

    // Check castling rights
    char *all_rights = "KQkq";
    int rights_len = strlen(castling_rights);
    if (rights_len > 0 && castling_rights[0] != '-')
    {
        int i = 0;
        for (int j = 0, len = strlen(all_rights); j < len && i < rights_len; j++)
        {
            if (castling_rights[i] == all_rights[j])
            {
                i++;
            }
        }
        if (i != rights_len)
        {
            return false;
        }
    }
    else if (rights_len != 1)
    {
        return false;
    }

    // Check en passant square
    switch (strlen(ep_square)) {
    case 1:
        if (ep_square[0] != '-')
        {
            return false;
        }
        break;
    case 2:
        if (ep_square[0] - 'a' < 0 || ep_square[0] - 'a' >= 8
            || ep_square[1] - '0' <= 0 || ep_square[1] - '0' > 8)
        {
            return false;
        }
        break;
    default:
        return false;
    }
 
    // Check move counters
    if (half_moves < 0 || full_moves <= 0)
    {
        return false;
    }

    return true;
}