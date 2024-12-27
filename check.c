#include "check.h"
int move_count = 0;
Move moves[1000]; // 假设最多有1000步

int is_win(int chessboard[MAX_ROW][MAX_COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (chessboard[i][j] == BLANK)
				continue;
			// 判断横向是否有五子相连
			if (j < col - 4)
			{
				if (chessboard[i][j] == chessboard[i][j + 1] && chessboard[i][j] == chessboard[i][j + 2] && chessboard[i][j] == chessboard[i][j + 3] && chessboard[i][j] == chessboard[i][j + 4])
					return chessboard[i][j];
			}
			// 判断纵向是否有五子相连
			if (i < row - 4)
			{
				if (chessboard[i][j] == chessboard[i + 1][j] && chessboard[i][j] == chessboard[i + 2][j] && chessboard[i][j] == chessboard[i + 3][j] && chessboard[i][j] == chessboard[i + 4][j])
					return chessboard[i][j];
			}
			// 判断左上到右下是否有五子相连
			if (i < row - 4 && j < col - 4)
			{
				if (chessboard[i][j] == chessboard[i + 1][j + 1] && chessboard[i][j] == chessboard[i + 2][j + 2] && chessboard[i][j] == chessboard[i + 3][j + 3] && chessboard[i][j] == chessboard[i + 4][j + 4])
					return chessboard[i][j];
			}
			// 判断右上到左下是否有五子相连
			if (i < row - 4 && j >= 4)
			{
				if (chessboard[i][j] == chessboard[i + 1][j - 1] && chessboard[i][j] == chessboard[i + 2][j - 2] && chessboard[i][j] == chessboard[i + 3][j - 3] && chessboard[i][j] == chessboard[i + 4][j - 4])
					return chessboard[i][j];
			}
		}
	}
	return BLANK;
}

// 判断棋盘是否已满
int is_full(int chessboard[MAX_ROW][MAX_COL], int row, int col)
{
	int i, j;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (chessboard[i][j] == BLANK)
				return BLANK;
		}
	}
	return 1;
}
//悔棋
void undo_move(int chessboard[MAX_ROW][MAX_COL], int *step)
{
	if (move_count > 0)
	{
		move_count--;
		int x = moves[move_count].x;
		int y = moves[move_count].y;
		chessboard[x][y] = BLANK;
		draw_chessboard(MAX_ROW, MAX_COL, chessboard);
		(*step)--;
	}
	else
	{
		printf("没有可以悔棋的步骤\n");
	}
}
//记录
void record_move(int step, int x, int y, int color)
{
	moves[move_count].step = step;
	moves[move_count].x = x;
	moves[move_count].y = y;
	moves[move_count].color = color;
	move_count++;
	printf("move_count=%d, step = %d, x=%d,y=%c,color = %d\n", move_count, step, x+1 , y + 'A', color);
}

// 复盘游戏
void replay_chess(void)
{
	Move moves[225];
	int move_count = 0;
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	FILE *fp;
	char temp;
	if ((fp = fopen("Save_chess.txt", "r")) == NULL)
	{
		printf("复盘失败");
	}
	else
	{
		while (fscanf(fp, "%d %d %d %d", &moves[move_count].step, &moves[move_count].x, &moves[move_count].y, &moves[move_count].color) != EOF)
		{
			move_count++;
		}
		fclose(fp);
		int current_step = 0;

		printf("按 'n' 进行下一步，按 'p' 进行上一步，按 'a' 打印全部\n");

		while (1)
		{
			char ch = getchar(); // 获取用户输入的按键
			if (ch == 'n' && current_step < move_count)
			{
				// 下一步
				chessboard[moves[current_step].x][moves[current_step].y] = moves[current_step].color;
				current_step++;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("step = %d, x = %d, y = %c\n", current_step, moves[current_step-1].x + 1, moves[current_step-1].y + 'A');
			}
			else if (ch == 'p' && current_step > 0)
			{
				// 上一步
				current_step--;
				chessboard[moves[current_step].x][moves[current_step].y] = BLANK;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("step = %d, x = %d, y = %c\n", current_step, moves[current_step].x + 1, moves[current_step].y + 'A');
			}
			else if (ch == 'a')
			{
				// 打印全部
				for (int i = current_step; i < move_count; i++)
				{
					chessboard[moves[i].x][moves[i].y] = moves[i].color;
				}
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				break;
			}
		}
	}
}
// 三三禁手判断
bool is_forbidden(int chessboard[MAX_ROW][MAX_COL], int x, int y, int color) {
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int count = 0;

    for (int d = 0; d < 4; d++) {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int openEnds = 0;
        int stones = 1;

        // Check in the positive direction
        for (int i = 1; i < 5; i++) {
            int nx = x + i * dx;
            int ny = y + i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == color) {
                stones++;
            } else {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK) {
                    openEnds++;
                }
                break;
            }
        }

        // Check in the negative direction
        for (int i = 1; i < 5; i++) {
            int nx = x - i * dx;
            int ny = y - i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == color) {
                stones++;
            } else {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK) {
                    openEnds++;
                }
                break;
            }
        }

        if (stones == 3 && openEnds == 2) {
            count++;
        }
    }

    return count >= 2;
}