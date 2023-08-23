#include "fen.h"
#include "move.h"
#include "common.h"

// Ansi color codes
#define BLACK   "\x1B[0;30m"
#define WHITE   "\x1B[1;37m"
#define GREY    "\x1B[1;30m"
#define RESET 	"\x1B[0m"

void make_move(char *move, char color);
void print_board(void);

char *piece_types = "rnbqkp";
char turn = 'w';
char board[SIZE][SIZE];

int main(void) {
    char *startpos = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    char *fen1 = "rnbqkbnr/pppppppp/8/7R/8/8/PPPPPPPP/RNBQKBN1 w KQkq - 0 1";
    char *fen2 = "r1bq1rk1/ppp1npbp/3p1np1/3Pp3/2P1P3/2N2N2/PP2BPPP/R1BQ1RK1 w - - 1 9";

    load_fen(fen2);
    make_move("f1e1", turn);
    print_board();

    return 0;
}

void make_move(char *move, char color) {
    if (!valid_move(move, color)) {
        fprintf(stderr, "Error: Invalid move %s\n", move);
        return;
    }

    // Get the coordinates from the string
    int rank_from = move[1] - '0' - 1;
    int file_from = move[0] - 'a';
    int rank_to = move[3] - '0' - 1;
    int file_to = move[2] - 'a';

    // Move the piece
    board[rank_to][file_to] = board[rank_from][file_from];
    board[rank_from][file_from] = '\0';
}

void print_board(void) {
    for (int rank = SIZE - 1; rank >= 0; rank--) {
        for (int file = 0; file < SIZE; file++) {
            char square = board[rank][file];
            if (square != '\0') {
                if (islower(square)) {
                    printf(GREY "%c " RESET, square);
                }
                else {
                    printf(WHITE "%c " RESET, square);
                }
            }
            else {
                printf(BLACK ". " RESET);
            }
        }
        printf("\n");
    }
}