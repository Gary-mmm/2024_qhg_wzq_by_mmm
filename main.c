#define WHITE -1
#define BLACK 1
#define BLANK 0
#define MAX_ROW 15
#define MAX_COL 15

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void draw_chessman(int type, char *tableline);
void draw_chessboard(int row, int col, int chessboard[MAX_ROW][MAX_COL]);
int is_win(int chessboard[MAX_ROW][MAX_COL], int row, int col);
int random_create_point();
int is_full(int chessboard[MAX_ROW][MAX_COL], int row, int col);
void save_chess(int chessboard[][MAX_COL], int row, int col);
void replay_chess(void);
void draw_menu(void);
int PVP(void);
int PVE(void);

char colname[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};


int main() {
	SetConsoleOutputCP(65001);//UTF-8编码
    int choice;
	draw_menu();
	while (1){
		scanf("%d", &choice);
		while (getchar() != '\n');
		switch (choice){
			case 1:
				PVP();
				break;
			case 2:
				PVE();
				break;
			case 3:
				replay_chess();
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("输入错误，请重新选择\n");
				break;
		}
	}
}
//人机对战
int PVE(){
	int x, y;
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	int choice = 1;
	draw_chessboard(MAX_ROW, MAX_COL, chessboard);
	printf("人机对战\n");
	printf("黑棋为1，白棋为2\n请选择先手（黑）或后手（白）：\n");
	scanf("%d", &choice);
	//判断输入是否合法
	while (choice != 1 && choice != 2){
		printf("输入错误，请重新选择：\n");
		scanf("%d", &choice);
	}
	//choice为1时，人先手，为2时，机器先手
	if (choice == 1){
		while (1){
			printf("请黑棋落子：\n");
			scanf("%d %d", &x, &y);
			if (x>=MAX_ROW || y>=MAX_COL || x < 0 || y < 0){
					printf("输入超出棋盘范围，请重新输入：\n");
					continue;
				}
			if (chessboard[x][y] != BLANK){
				printf("此处已有棋子，请重新输入：\n");
				continue;
			}
			chessboard[x][y] = BLACK;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK){
				printf("黑棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
			printf("白棋落子：\n");
			x = random_create_point();
			y = random_create_point();
			while (chessboard[x][y] != BLANK){
				x = random_create_point();
				y = random_create_point();
			}
			chessboard[x][y] = WHITE;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE){
				printf("白棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
			if (is_full(chessboard, MAX_ROW, MAX_COL) == 1){
				printf("平局\n");
				exit(0);
			}
		}
	} else{
		while (1){
			printf("白棋落子：\n");
			x = random_create_point();
			y = random_create_point();
			while (chessboard[x][y] != BLANK){
				x = random_create_point();
				y = random_create_point();
			}
			chessboard[x][y] = WHITE;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE){
				printf("白棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
			printf("请黑棋落子：\n");
			scanf("%d %d", &x, &y);
			if (x>=MAX_ROW || y>=MAX_COL || x < 0 || y < 0){
					printf("输入超出棋盘范围，请重新输入：\n");
					continue;
				}
			if (chessboard[x][y] != BLANK){
				printf("此处已有棋子，请重新输入：");
				continue;
			}
			chessboard[x][y] = BLACK;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK){
				printf("黑棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
			if (is_full(chessboard, MAX_ROW, MAX_COL) == 1){
				printf("平局\n");
				exit(0);
			}
		}
	}
}
//人人对战
int PVP(){
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	int x = 0, y = 0;
	char temp_y;
	int savechess = 0;
	draw_chessboard(MAX_ROW, MAX_COL, chessboard);
	for (int step = 1; step <= MAX_COL*MAX_ROW; step++){
		if (step % 2 == 1){
			printf("请黑棋落子：\n");
			while (1) {
            // 清除输入缓冲区
            while (getchar() != '\n');

            printf("请输入坐标（如 a 10）：");
            if (scanf("%c %d", &temp_y, &x) != 2) {
                printf("输入格式错误，请重新输入：\n");
                // 清除输入缓冲区
                while (getchar() != '\n');
                continue;
            }
            // 清除输入缓冲区
            while (getchar() != '\n');

            // 将字母转换为数字
            if (temp_y >= 'a' && temp_y <= 'o') {
                y = temp_y - 'a';
            } else if (temp_y >= 'A' && temp_y <= 'O') {
                y = temp_y - 'A';
            } else {
                printf("横坐标输入错误，请重新输入：\n");
                continue;
            }

            if (x >= MAX_ROW || y >= MAX_COL || x < 0 || y < 0) {
                printf("输入超出棋盘范围，请重新输入：\n");
                continue;
            }
            if (chessboard[x][y] != BLANK) {
                printf("此处已有棋子，请重新输入：\n");
                continue;
            }
            break;
        }
			chessboard[x][y] = BLACK;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			printf("人人对战\n");
			if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK){
				printf("黑棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
		}else if (step % 2 == 0){
			printf("请白棋落子：");
			while (1){
				while ((getchar()) != '\n');
				scanf("%d %d", &x, &y);
				if (chessboard[x][y] != BLANK){
					printf("此处已有棋子，请重新输入：\n");
					continue;
				}
				if (x>=MAX_ROW || y>=MAX_COL || x < 0 || y < 0){
					printf("输入超出棋盘范围，请重新输入：\n");
					continue;
				}
				break;
			}
			chessboard[x][y] = WHITE;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			printf("人人对战\n");
			if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE){
				printf("白棋获胜\n");
				save_chess(chessboard, MAX_ROW, MAX_COL);
				exit(0);
			}
		}
	}
	if (is_full(chessboard, MAX_ROW, MAX_COL) == 1){
		printf("平局\n");
		exit(0);
	}
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
		printf("%2d", i);
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
int is_win(int chessboard[MAX_ROW][MAX_COL], int row, int col){
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (chessboard[i][j] == BLANK)
				continue;
			//判断横向是否有五子相连
			if (j < col - 4){
				if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4])
					return chessboard[i][j];
			}
			//判断纵向是否有五子相连
			if (i < row - 4){
				if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j])
					return chessboard[i][j];
			}
			//判断左上到右下是否有五子相连
			if (i < row - 4 && j < col - 4){
				if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4])
					return chessboard[i][j];
			}
			//判断右上到左下是否有五子相连
			if (i < row - 4 && j >= 4){
				if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4])
					return chessboard[i][j];
			}
		}
	}
	return BLANK;
}
//随机落子
int random_create_point(){
	int randposition;
    srand((unsigned)time(NULL));
    randposition = rand() % MAX_COL;
	return randposition;
}
//判断棋盘是否已满
int is_full(int chessboard[MAX_ROW][MAX_COL], int row, int col){
	int i, j;
	for (i = 0; i < row; i++){
		for (j = 0; j < col; j++){
			if (chessboard[i][j] == BLANK)
				return BLANK;
		}
	}
	return 1;
}

//保存棋局
void  save_chess(int chessboard[][MAX_COL], int row, int col) {
	int choice ;
	FILE *fp;
	printf("是否选择结束游戏，并保存当前棋局\n");
	printf("*********1.存盘并退出***********\n");
	printf("*********2.重新开始PVP**********\n");
	printf("*********3.重新开始PVE**********\n");
	printf("请选择 :");
	while (1) {
		scanf("%d", &choice);
		if (choice > 3||choice < 1) {
			printf("输入错误，请重新选择\n");
			continue;
		}
		break;
	}
	if (choice == 1) {
		if ( ( fp = fopen( "Save_chess.txt", "w" ) ) == NULL ) {
			printf(" 保存失败\n");
		} else {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					fprintf(fp, "%d", chessboard[i][j]);
				}
			}
			fclose(fp);
			printf("恭喜您，保存成功");
		}
		exit(0);
	}
	if (choice == 2) {
		PVP();
	}
	if (choice == 3) {
		PVE();
	}
}
//复盘游戏
void replay_chess(void) {
	int  chessboard[MAX_ROW][MAX_COL] = {BLANK};
	FILE *fp;
	char ch;
	if ((fp = fopen("Save_chess.txt", "w")) == NULL) {
		printf("复盘失败");
	} else {
		for (int i = 0; i < MAX_ROW; i++) {
			for (int j = 0; j < MAX_COL; j++) {
				fscanf(fp, "%d", chessboard[i][j]);
			}
		}
		fclose(fp);
		draw_chessboard(MAX_ROW, MAX_COL, chessboard);
	}
}
//绘制菜单
void draw_menu(void) {
	printf("******************************\n");
	printf("*********欢迎来到五子棋游戏***\n");
	printf("*********1.人人对战(PVP)******\n");
	printf("*********2.人机对战(PVE)******\n");
	printf("*********3.复盘游戏***********\n");
	printf("*********4.退出游戏***********\n");
	printf("******************************\n");
	printf("请选择：");
}