#define WHITE -1
#define BLACK 1
#define BLANK 0
#define MAX_ROW 15
#define MAX_COL 15

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
// #include <windows.h>
char colname[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};
void draw_chessman(int type, char *tableline);
void draw_chessboard(int row, int col, int chessboard[MAX_ROW][MAX_COL]);
struct Chess_info{
	int x[225];
	int y[225];
	int step[225];
	int color[225];
} chess_info;

int main() {
	// SetConsoleOutputCP(65001);//UTF-8编码
    
	for (int i = 0; i < 225; i++){
	chess_info.x[i] = 0;
	chess_info.y[i] = 0;
	chess_info.step[i] = i + 1;
	chess_info.color[i] = BLANK;
    }
	int x, y;
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	char s[10];
	while (1) {
			x = 0;y = 0;//清空x,y
			for (int i = 0; i < 6; i++){
				s[i] = 0;//清空s
			}
			while(getchar() != '\n')
				continue;
            printf("请输入坐标（如 a10）：");
            scanf("%s", s);
			int i = 0;
			if (isdigit(s[i])){
				while (isdigit(s[i])){
					x = x * 10 + s[i] - '0';
					i++;
				}
				x--;
				while(s[i] == ' '){
					i++;
					}
				if (islower(s[i])){
					y = s[i] - 'a';
					i++;
				}else if (isupper(s[i])){
					y = s[i] - 'A';
					i++;
				}
			} else {
				if (islower(s[i])){
					y = s[i] - 'a';
					i++;
				}else if (isupper(s[i])){
					y = s[i] - 'A';
					i++;
				}
				while (isdigit(s[i])){
					x = x * 10 + s[i] - '0';
					i++;
				}
				x--;
			}
			printf("x=%d,y=%c\n", x+1, colname[y]);
			if (x>=MAX_ROW || y>=MAX_COL || x < 0 || y < 0){
				printf("输入超出棋盘范围，请重新输入：\n");
				continue;
			}
			
			if (chessboard[x][y] != BLANK){
				printf("此处已有棋子，请重新输入：\n");
				continue;
			}
			break;
	}
	chessboard[x][y] = BLACK;
	draw_chessboard(MAX_ROW, MAX_COL, chessboard);

}
//绘制棋子
void draw_chessman(int type, char *tableline) {
	if (type == WHITE)
		printf("● ");
	if (type == BLACK)
		printf("○ ");
	if (type == BLANK)
		printf("%s", tableline);//此处传入另一个参数tableline,是为了绘制棋盘更加方便
}
//绘制棋盘
void draw_chessboard(int row, int col, int chessboard[MAX_ROW][MAX_COL]) {
    int i, j;
    for (int i = 0; i < row; i++){
		printf("%2d", i+1);
        if (i == 0) {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "┌ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┐");
				else
					draw_chessman(chessboard[i][j], "┬ ");
			}
			printf("\n");//第一行┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐
		} else if (i == 14) {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "└ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┘ ");
				else
					draw_chessman(chessboard[i][j], "┴ ");
			}
			printf("\n");//最后一行└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘
		} else {
			for (int j = 0; j < col; j++) {
				if (j == 0)
					draw_chessman(chessboard[i][j], "├ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┤");
				else
					draw_chessman(chessboard[i][j], "┼ ");
			}
			printf("\n");//其他行├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
		}
    }
	printf(" ");
	for (int j = 0; j < col; j++) {
		printf("%2c", colname[j]);
	}
	printf("\n");
}