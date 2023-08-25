#include "fen.h"
#include "valid_move.h"
#include "common.h"

// ANSI color codes
#define BLACK "\x1B[0;30m"
#define WHITE "\x1B[1;37m"
#define GREY "\x1B[1;30m"
#define RESET "\x1B[0m"

void make_move(char *move);
void print_board(void);

char *piece_types = "rnbqkp";
char board[SIZE][SIZE];
char turn;
char ep_square[3];
char castling_rights[5];
int half_moves, full_moves;

int main(void)
{
    char *fen_startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char *fen_kid = "r1bq1rk1/ppp1npbp/3p1np1/3Pp3/2P1P3/2N2N2/PP2BPPP/R1BQ1RK1 w - - 1 9";
    char *fen = "8/4p3/8/8/8/8/4P3/8";
    char *moves[] = {
        "e2e4", "a7a6", "e4e5", "d7d5", "e5d6", "a6a5",
        "d6e7", "a5a4", "e7d8q", "a4a3", "d8e8", "a3b2",
        "e8d8", "b2a1q"
    };
    char *moves2[] = {
        "e2e4", "e7e5", "g1f3", "b8c6", "f1c4", "f8c5",
        "c2c3", "g8f6"
    };

    load_fen(fen_startpos);
    for (int i = 0; i < (sizeof(moves) / sizeof(moves[0])); i++)
    {
        make_move(moves[i]);
        print_board();
        printf("%c %s %s %d %d\n\n",
            turn, castling_rights, ep_square, half_moves, full_moves);
    }

    return 0;
}

void make_move(char *move)
{
    if (!valid_move(move))
    {
        fprintf(stderr, "Error: Invalid move %s\n", move);
        return;
    }

    // Get the coordinates from the string
    int rank_from, file_from, rank_to, file_to;
    get_coords(move, &rank_from, &file_from, &rank_to, &file_to);

    // en passant
    int rank_ep = ep_square[1] - '0' - 1;
    int file_ep = ep_square[0] - 'a';
    ep_square[0] = '-';
    ep_square[1] = '\0';
    if (tolower(board[rank_from][file_from]) == 'p')
    {
        if (rank_to == rank_ep && file_to == file_ep)
        {
            board[rank_to + (turn == 'w' ? -1 : 1)][file_to] = '\0';
        }

        if (abs(rank_to - rank_from) == 2)
        {
            ep_square[1] = rank_to + (turn == 'w' ? -1 : 1) + '0' + 1;
            ep_square[0] = file_to + 'a';
        }
    }

    // Update counters
    if (turn == 'b')
    {
        full_moves++;
    }
    char target = board[rank_to][file_to];
    // If a pawn is moved or a piece is captured
    if (tolower(board[rank_from][file_from]) == 'p'
        || ((target != '\0') && (turn == 'w' ? islower(target) : isupper(target))))
    {
        half_moves = 0;
    }
    else
    {
        half_moves++;
    }

    // Move the piece and promote if its a pawn on the 8th rank
    board[rank_to][file_to] = move[4] == '\0' ? board[rank_from][file_from] :
        (turn == 'w' ? toupper(move[4]) : move[4]);
    board[rank_from][file_from] = '\0';

    // Switch color
    turn = turn == 'w' ? 'b' : 'w';
}

void print_board(void)
{
    for (int rank = SIZE - 1; rank >= 0; rank--)
    {
        for (int file = 0; file < SIZE; file++)
        {
            char square = board[rank][file];
            if (square != '\0')
            {
                if (islower(square))
                {
                    printf(GREY "%c " RESET, square);
                }
                else
                {
                    printf(WHITE "%c " RESET, square);
                }
            }
            else
            {
                printf(BLACK ". " RESET);
            }
        }
        printf("\n");
    }
}