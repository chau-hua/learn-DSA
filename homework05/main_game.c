#include "stack_game.h"
#include <time.h>

#define BOARD_SIZE 3
#define VALID   0
#define INVALID 1

// main logic
int play_game(int board[][BOARD_SIZE], move** moves);

// player & computer move
position player_move(int board[][BOARD_SIZE]);
position computer_move_random(int board[][BOARD_SIZE]);
position computer_move_minimax(int board[][BOARD_SIZE]);

// undo
int is_undo(position p);
void undo(move** moves);

// game checking utilities
int is_over(int board[][BOARD_SIZE]);
int invalid_move(int x, int y, int board[][BOARD_SIZE]);
int three_consecutive(int board[][BOARD_SIZE], char c);
int is_full(int board[][BOARD_SIZE]);

// minimax algorithm
int minimax(int board[][BOARD_SIZE], int depth, int is_max);
int try_all(int board[][BOARD_SIZE], int depth, int is_max);

// draw board
void print_hline(int length);
void draw_board(int board[][BOARD_SIZE], move* moves);

// redo
move *redo_moves = NULL;
int is_redo(position p);
void redo(move **moves, move **redo_moves);

int main(int argc, const char * argv[])
{
    int board[BOARD_SIZE][BOARD_SIZE];
    move* moves = NULL;
    draw_board(board, moves);
    time_t t;
    srand((unsigned) time(&t));
    
    int game_over = 0;
    while (!game_over)
    {
        game_over = play_game(board, &moves);
    }
    clear_stack(&moves);
    return 0;
}
int play_game(int board[][BOARD_SIZE], move** moves)
{
    int game_over = 0;
    position pos;
    move *move;
    
    pos = player_move(board);
    if (is_undo(pos))
    {
        undo(moves);
        draw_board(board, *moves);
        return game_over;
    }
    else if (is_redo(pos))
    {
        redo(moves, &redo_moves);
        draw_board(board, *moves);
        return game_over;
    }

    // not undo, redo
    push(moves, pos);
    draw_board(board, *moves);
    game_over = is_over(board);
    if (!game_over)
    {
        pos = computer_move_minimax(board);
        push(moves, pos);
        draw_board(board, *moves);
        game_over = is_over(board);
    }

    return game_over;
}
void undo(move** moves)
{
    if (!is_empty(*moves))
    {
        push(&redo_moves, (*moves)->pos);
        pop(moves);
        push(&redo_moves, (*moves)->pos);
        pop(moves);
    }
    else printf("Nothing to undo\n");
}

void redo(move **moves, move **redo_moves)
{
    if (!is_empty(*redo_moves))
    {
        push(moves, (*redo_moves)->pos);
        pop(redo_moves);
        push(moves, (*redo_moves)->pos);
        pop(redo_moves);
    }
    else printf("Nothing to redo\n");
}

position player_move(int board[][BOARD_SIZE])
{
    int x = -2, y = -2;
    int invalid = INVALID;
    while (invalid)
    {
        printf("Player move (ex: 0 0), to undo (-1 -1), to redo (-2 -2): ");
        fflush(stdin);
        scanf("%d", &x);
        scanf("%d", &y);
        invalid = invalid_move(x, y, board);
        if (invalid) printf("Invalid move!\n");
    }
    position pos = {x, y, 'X'};
    return pos;
}
position computer_move_random(int board[][BOARD_SIZE])
{
    int x = -2, y = -2;
    printf("Computer move: ");
    
    while (invalid_move(x, y, board))
    {
        x = rand() % BOARD_SIZE;
        y = rand() % BOARD_SIZE;
    }
    printf("%d %d\n", x, y);
    position pos = {x, y, 'O'};
    return pos;
}
position computer_move_minimax(int board[][BOARD_SIZE])
{
    int best_score = -1000;
    position best_move;
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = 'O';
                int score = minimax(board, 0, 0);
                board[i][j] = ' ';
                if (score > best_score)
                {
                    best_score = score;
                    best_move = (position) {i, j, 'O'};
                }
            }
        }
    }
    printf("%d %d\n", best_move.x, best_move.y);
    return best_move;
}

int minimax(int board[][BOARD_SIZE], int depth, int is_max)
{
    // check if game depth is reached
    if (depth == 9) return 0;
    
    if (three_consecutive(board, 'O')) return 10;
    if (three_consecutive(board, 'X')) return -10;
    if (is_full(board)) return 0;
    int best_score = try_all(board, depth, is_max);
    return best_score;
}

int try_all(int board[][BOARD_SIZE], int depth, int is_max)
{
    int best_score = 0;
    if (is_max) best_score = -1000;
    else best_score = 1000;
    
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = is_max ? 'O' : 'X';
                int score = minimax(board, depth + 1, !is_max);
                board[i][j] = ' ';
                if (is_max && score > best_score) best_score = score;
                else if (!is_max && score < best_score) best_score = score;
            }
        }
    }
    return best_score;
}

int is_over(int board[][BOARD_SIZE])
{
    if (three_consecutive(board, 'O'))
    {
        printf("Computer win.\n");
        return 1;
    }
    else if (three_consecutive(board, 'X'))
    {
        printf("You win.\n");
        return 1;
    }
    else if (is_full(board))
    {
        printf("Full map.\n");
        return 1;
    }

    return 0;
}

int invalid_move(int x, int y, int board[][BOARD_SIZE])
{
    if ((x == -1 && y == -1) || (x == -2 && y == -2)) return VALID; // undo/redo move
    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) return INVALID;
    if (board[x][y] != ' ') return INVALID; // already taken
    return VALID;
}

int is_undo(position p)
{
    return p.x == -1 && p.y == -1;
}

int is_redo(position p)
{
    return p.x == -2 && p.y == -2;
}

int three_consecutive(int board[][BOARD_SIZE], char c)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c) return 1;
    }
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[0][i] == c && board[1][i] == c && board[2][i] == c) return 1;
    }
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c) return 1;
    if (board[0][2] == c && board[1][1] == c && board[2][0] == c) return 1;
    return 0;
}

int is_full(int board[][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (board[i][j] == ' ') return 0;
    return 1;
}


void print_hline(int length)
{
    printf("+");
    for (int i = 0; i < length; i++)
    {
        printf("-+");
    }
    printf("\n");
}

void draw_board(int board[][BOARD_SIZE], move* moves)
{
    position* pos = to_array(moves);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board[i][j] = ' ';
    
    for (int i = 0; i < get_size(moves); i++)
        board[pos[i].x][pos[i].y] = pos[i].c;
    
    printf("Board:\n");
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        print_hline(BOARD_SIZE);
        for (int j = 0; j < BOARD_SIZE; j++)
            printf("|%c", board[i][j]);
        printf("|\n");
    }
    print_hline(BOARD_SIZE);
    
    free(pos);
}