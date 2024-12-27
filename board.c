#include "board.h"
#include "check.h"
char colname[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};


// 绘制棋子
void draw_chessman(int type, char *tableline)
{
	if (type == WHITE)
		printf("● ");
	if (type == BLACK)
		printf("○ ");
	if (type == BLANK)
		printf("%s", tableline); // 此处传入另一个参数tableline,是为了绘制棋盘更加方便
}

// 绘制棋盘
void draw_chessboard(int row, int col, int chessboard[MAX_ROW][MAX_COL])
{
	system("cls");
	int i, j;
	for (int i = 14; i >= 0; i--)
	{
		printf("%2d", i + 1);
		if (i == 14)
		{
			for (int j = 0; j < col; j++)
			{
				if (j == 0)
					draw_chessman(chessboard[i][j], "┌ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┐");
				else
					draw_chessman(chessboard[i][j], "┬ ");
			}
			printf("\n"); // 第一行┌┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┬┐
		}
		else if (i == 0)
		{
			for (int j = 0; j < col; j++)
			{
				if (j == 0)
					draw_chessman(chessboard[i][j], "└ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┘ ");
				else
					draw_chessman(chessboard[i][j], "┴ ");
			}
			printf("\n"); // 最后一行└┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┴┘
		}
		else
		{
			for (int j = 0; j < col; j++)
			{
				if (j == 0)
					draw_chessman(chessboard[i][j], "├ ");
				else if (j == 14)
					draw_chessman(chessboard[i][j], "┤");
				else
					draw_chessman(chessboard[i][j], "┼ ");
			}
			printf("\n"); // 其他行├┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┼┤
		}
	}
	printf(" ");
	for (int j = 0; j < col; j++)
	{
		printf("%2c", colname[j]);
	}
	printf("\n");
}


// 绘制菜单
void draw_menu(void)
{
	printf("******************************\n");
	printf("*********欢迎来到五子棋游戏***\n");
	printf("*********1.人人对战(PVP)******\n");
	printf("*********2.人机对战(PVE)******\n");
	printf("*********3.复盘游戏***********\n");
	printf("*********4.退出游戏***********\n");
	printf("******************************\n");
	printf("请选择：");
}

// 随机落子
int random_create_point()
{
	int randposition;
	srand((unsigned)time(NULL));
	randposition = rand() % MAX_COL;
	return randposition;
}

// 保存棋局
void save_chess(Move moves[], int move_count, int row, int col)
{
	int choice;
	FILE *fp;
	printf("是否选择结束游戏，并保存当前棋局\n");
	printf("*********1.存盘并退出***********\n");
	printf("请选择 :");
	while (1)
	{
		scanf("%d", &choice);
		if (choice > 1 || choice < 1)
		{
			printf("输入错误，请重新选择\n");
			continue;
		}
		break;
	}
	if (choice == 1)
	{
		if ((fp = fopen("Save_chess.txt", "w")) == NULL)
		{
			printf(" 保存失败\n");
		}
		else
		{
			for (int i = 0; i < move_count; i++)
			{
				fprintf(fp, "%d %d %d %d\n", moves[i].step, moves[i].x, moves[i].y, moves[i].color);
			}
			fclose(fp);
			printf("恭喜您，保存成功\n");
		}
		exit(0);
	}
}
int get_Input(int *x, int *y, int color, int chessboard[MAX_ROW][MAX_COL])
{
	while (1)
	{
		*x = 0;
		*y = -1;
		char s[10];
		for (int i = 0; i < 10; i++)
		{
			s[i] = '\0'; // 清空数组
		}
		while (getchar() != '\n'); // 清除输入缓冲区
		if (color == BLACK)
			printf("请黑棋落子：\n");
		else
			printf("请白棋落子：\n");
		printf("请输入坐标（如a10）：");
		scanf("%s", s);
		if (s[0] == 'u' && s[1] == 'n' && s[2] == 'd' && s[3] == 'o')
		{
			*x = -1;
			*y = -1;// 悔棋
			return 0;
		}
		int i = 0;
		if (isdigit(s[i]))
		{
			while (isdigit(s[i]))
			{
				*x = *x * 10 + s[i] - '0';
				i++;
			}
			(*x)--;
			if (islower(s[i]))
			{
				*y = s[i] - 'a';
				i++;
			}
			else if (isupper(s[i]))
			{
				*y = s[i] - 'A';
				i++;
			}
		}
		else
		{
			if (islower(s[i]))
			{
				*y = s[i] - 'a';
				i++;
			}
			else if (isupper(s[i]))
			{
				*y = s[i] - 'A';
				i++;
			}
			while (isdigit(s[i]))
			{
				*x = *x * 10 + s[i] - '0';
				i++;
			}
			(*x)--;
		}

		if (*x >= MAX_ROW || *y >= MAX_COL || *x < 0 || *y < 0)
		{
			printf("Out of the board, please input again\n");
			continue;
		}
		if (chessboard[*x][*y] != BLANK)
		{
			printf("This place has been used. Please try again.\n");
			continue;
		}
		break;
	}
	return 0;
}

// 评分函数
int evaluate_position(int chessboard[MAX_ROW][MAX_COL], int x, int y, int color)
{
    int score = 0;
    int directions[4][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}};
    int opponent_color = (color == BLACK) ? WHITE : BLACK;

    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1;
        int openEnds = 0;

        // Check in the positive direction
        for (int i = 1; i < 5; i++)
        {
            int nx = x + i * dx;
            int ny = y + i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == color)
            {
                count++;
            }
            else
            {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK)
                {
                    openEnds++;
                }
                break;
            }
        }

        // Check in the negative direction
        for (int i = 1; i < 5; i++)
        {
            int nx = x - i * dx;
            int ny = y - i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == color)
            {
                count++;
            }
            else
            {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK)
                {
                    openEnds++;
                }
                break;
            }
        }

        if (count >= 5)
        {
            score += 10000; // 五连珠
        }
        else if (count == 4 && openEnds == 2)
        {
            score += 1000; // 活四
        }
        else if (count == 4 && openEnds == 1)
        {
            score += 100; // 死四
        }
        else if (count == 3 && openEnds == 2)
        {
            score += 100; // 活三
        }
        else if (count == 3 && openEnds == 1)
        {
            score += 10; // 死三
        }
        else if (count == 2 && openEnds == 2)
        {
            score += 10; // 活二
        }
        else if (count == 2 && openEnds == 1)
        {
            score += 1; // 死二
        }
    }

    // 防守评分：对对手的棋子进行评分，并将其纳入总评分中
    for (int d = 0; d < 4; d++)
    {
        int dx = directions[d][0];
        int dy = directions[d][1];
        int count = 1;
        int openEnds = 0;

        // Check in the first direction
        for (int i = 1; i < 5; i++)
        {
            int nx = x + i * dx;
            int ny = y + i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == opponent_color)
            {
                count++;
            }
            else
            {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK)
                {
                    openEnds++;
                }
                break;
            }
        }

        // Check in the second direction
        for (int i = 1; i < 5; i++)
        {
            int nx = x - i * dx;
            int ny = y - i * dy;
            if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == opponent_color)
            {
                count++;
            }
            else
            {
                if (nx >= 0 && nx < MAX_ROW && ny >= 0 && ny < MAX_COL && chessboard[nx][ny] == BLANK)
                {
                    openEnds++;
                }
                break;
            }
        }

        if (count >= 5)
        {
            score += 5000; // 对手五连珠
        }
        else if (count == 4 && openEnds == 2)
        {
            score += 500; // 对手活四
        }
        else if (count == 4 && openEnds == 1)
        {
            score += 50; // 对手死四
        }
        else if (count == 3 && openEnds == 2)
        {
            score += 50; // 对手活三
        }
        else if (count == 3 && openEnds == 1)
        {
            score += 5; // 对手死三
        }
        else if (count == 2 && openEnds == 2)
        {
            score += 5; // 对手活二
        }
        else if (count == 2 && openEnds == 1)
        {
            score += 1; // 对手死二
        }
    }

    // 三三禁手判断
    if (is_forbidden(chessboard, x, y, color))
    {
        score -= 100000; // 如果是禁手位置，极大降低评分
    }

    return score;
}