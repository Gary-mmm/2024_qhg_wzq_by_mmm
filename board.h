#ifndef BOARD_H
#define BOARD_H

#define WHITE -1
#define BLACK 1
#define BLANK 0
#define MAX_ROW 15
#define MAX_COL 15

#include <stdio.h>
#include <windows.h>
#include <time.h>
typedef struct
{
	int step;
	int x;
	int y;
	int color;
} Move;

extern char colname[15];


void draw_chessman(int type, char *tableline);
void draw_chessboard(int row, int col, int chessboard[MAX_ROW][MAX_COL]);
void draw_menu(void);
int random_create_point();
void save_chess(Move moves[], int move_count, int row, int col);
int get_Input(int *x, int *y, int color, int chessboard[MAX_ROW][MAX_COL]);
int evaluate_position(int chessboard[MAX_ROW][MAX_COL], int x, int y, int color);

#endif