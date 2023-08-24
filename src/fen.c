#include "fen.h"

void load_fen(char *fen)
{
    if (!valid_fen(fen))
    {
        fprintf(stderr, "Error: Invalid FEN\n");
        return;
    }

    int rank = SIZE - 1, file = 0;
    for (char *p = fen; *p != '\0'; p++)
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

// Returns false if the FEN string contains any invalid characters
// or if it does not describe every square of the board
bool valid_fen(char *fen)
{
    int rank = 1;
    int file = 0;
    char *p;
    for (p = fen; *p != '\0'; p++)
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
        else if (c == ' ' && rank == SIZE && file == SIZE)
        {
            break;
        }
        else
        {
            return false;
        }
    }

    if (*p != '\0')
    {
        // TODO: check rest of FEN
    }

    return true;
}