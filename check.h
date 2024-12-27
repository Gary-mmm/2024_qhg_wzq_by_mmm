#ifndef CHECK_H
#define CHECK_H

#define WHITE -1
#define BLACK 1
#define BLANK 0
#define MAX_ROW 15
#define MAX_COL 15

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include "board.h"
#include <stdbool.h>

extern int move_count;
extern Move moves[1000]; // 假设最多有1000步

int is_win(int chessboard[MAX_ROW][MAX_COL], int row, int col);
int is_full(int chessboard[MAX_ROW][MAX_COL], int row, int col);
void undo_move(int chessboard[MAX_ROW][MAX_COL], int *step);
void record_move(int step, int x, int y, int color);
void replay_chess(void);
bool is_forbidden(int chessboard[MAX_ROW][MAX_COL], int x, int y, int color);

#endif