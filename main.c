/*Author：Luo Zheyuan*/
#include "board.h" // 棋盘基本功能实现
#include "check.h" // 判断函数和部分记录函数

int PVP(void);
int PVE(void);

// char colname[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'}; // 棋盘col_name
// Move moves[1000];
// move_count = 0;

int main()
{
	SetConsoleOutputCP(65001); // UTF-8编码
	int choice;
	draw_menu();
	while (1)
	{
		scanf("%d", &choice);
		while (getchar() != '\n')
			;
		switch (choice)
		{
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
	exit(0);
}
// 人机对战
int PVE()
{
	int x, y;
	int last_x = -1, last_y = -1; // 记录上一步的位置
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	int choice = 1;

	draw_chessboard(MAX_ROW, MAX_COL, chessboard);
	printf("人机对战\n");
	printf("黑棋为1，白棋为2\n请选择先手（黑）或后手（白）：\n");
	scanf("%d", &choice);
	// 判断输入是否合法
	while (choice != 1 && choice != 2)
	{
		printf("输入错误，请重新选择：\n");
		while (getchar() != '\n')
			;
		scanf("%d", &choice);
	}
	// choice为1时，人先手，为2时，机器先手
	int step = 0;
	if (choice == 1)
	{
		while (1)
		{
			step++;
			if (step % 2 == 1)
			{
				if (last_x != -1 && last_y != -1)
                {
                    printf("上一步对手下的位置：x=%d y=%c\n", last_x + 1, last_y + 'A');
                }
				get_Input(&x, &y, BLACK, chessboard);
				if (x == -1 && y == -1) // 此时进行悔棋
				{
					undo_move(chessboard, &step);
					undo_move(chessboard, &step);
					step--;
					continue;
				}
				if (is_forbidden(chessboard, x, y, BLACK)) // 禁手判断
				{
					printf("该位置为禁手，请重新选择位置\n");
					step--;
					continue;
				}
				printf("black:x=%d y=%c\n", x + 1, y + 'A');
				record_move(step, x, y, BLACK);
				chessboard[x][y] = BLACK;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("人机对战\n");
				if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK)
				{
					printf("黑棋获胜\n");
					save_chess(moves, step, MAX_ROW, MAX_COL);
					exit(0);
				}
				last_x = x;
                last_y = y;
			}
			else if (step % 2 == 0)
			{
				// x = random_create_point();
				// y = random_create_point();
				// while (chessboard[x][y] != BLANK)
				// {
				// 	x = random_create_point();
				// 	y = random_create_point();
				// }
				int best_score = -1;// 用一层打分搜索替代随机落子
                int best_x = -1, best_y = -1;
                for (int i = 0; i < MAX_ROW; i++)
                {
                    for (int j = 0; j < MAX_COL; j++)
                    {
                        if (chessboard[i][j] == BLANK)
                        {
                            int score = evaluate_position(chessboard, i, j, WHITE);
                            if (score > best_score)
                            {
                                best_score = score;
                                best_x = i;
                                best_y = j;
                            }
                        }
                    }
                }
				x = best_x;
                y = best_y;
				printf("white:x=%d y=%c\n", x + 1, y + 'A');
				record_move(step, x, y, WHITE);
				chessboard[x][y] = WHITE;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("人机对战\n");
				if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE)
				{
					printf("白棋获胜\n");
					save_chess(moves, step, MAX_ROW, MAX_COL);
					exit(0);
				}
				last_x = x;
                last_y = y;
			}
		}
	}
	else
	{
		// 机器先手，第一步落在棋盘中间
        x = MAX_ROW / 2;
        y = MAX_COL / 2;
        step++;
        printf("black:x=%d y=%c\n", x + 1, y + 'A');
        record_move(step, x, y, BLACK);
        chessboard[x][y] = BLACK;
        draw_chessboard(MAX_ROW, MAX_COL, chessboard);
        printf("人机对战\n");
        last_x = x;
        last_y = y;
		while (1)
		{
			step++;
			if (step % 2 == 1)
			{
				int best_score = -1;
                int best_x = -1, best_y = -1;
                for (int i = 0; i < MAX_ROW; i++)
                {
                    for (int j = 0; j < MAX_COL; j++)
                    {
                        if (chessboard[i][j] == BLANK)
                        {
                            int score = evaluate_position(chessboard, i, j, BLACK);
                            if (score > best_score)
                            {
                                best_score = score;
                                best_x = i;
                                best_y = j;
                            }
                        }
                    }
                }
                x = best_x;
                y = best_y;
				printf("black:x=%d y=%c\n", x + 1, y + 'A');
				record_move(step, x, y, BLACK);
				chessboard[x][y] = BLACK;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("人机对战\n");
				if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK)
				{
					printf("黑棋获胜\n");
					save_chess(moves, step, MAX_ROW, MAX_COL);
					exit(0);
				}
				last_x = x;
                last_y = y;
			}
			else if (step % 2 == 0)
			{
				if (last_x != -1 && last_y != -1)
                {
                    printf("上一步对手下的位置：x=%d y=%c\n", last_x + 1, last_y + 'A');
                }
				// while (getchar() != '\n');
				get_Input(&x, &y, WHITE, chessboard);
				if (x == -1 && y == -1) // 此时进行悔棋
				{
					undo_move(chessboard, &step);
					undo_move(chessboard, &step);
					step--;
					continue;
				}
				// if (is_forbidden(chessboard, x, y, WHITE)) // 注意！人执白棋时不应有禁手检测，这个问题直到比赛时才暴露出来。
				// {
				// 	printf("该位置为禁手，请重新选择位置\n");
				// 	step--;
				// 	continue;
				// }
				printf("x=%d y=%c\n", x, y + 'A');
				record_move(step, x, y, WHITE);
				chessboard[x][y] = WHITE;
				draw_chessboard(MAX_ROW, MAX_COL, chessboard);
				printf("人机对战\n");
				if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE)
				{
					printf("白棋获胜\n");
					save_chess(moves, step, MAX_ROW, MAX_COL);
					exit(0);
				}
				last_x = x;
                last_y = y;
			}
		}
	}
	return 0;
}
// 人人对战
int PVP()
{
	int chessboard[MAX_ROW][MAX_COL] = {BLANK};
	int x = 0, y = -1;
	int last_x = -1, last_y = -1; // 记录上一步的位置
	char temp_y;
	int savechess = 0;
	int step = 0;
	// Move moves[MAX_COL * MAX_ROW];
	draw_chessboard(MAX_ROW, MAX_COL, chessboard);
	while (1)
	{
		step++;
		if (step % 2 == 1)
		{
			if (last_x != -1 && last_y != -1)
            {
                printf("上一步对手下的位置：x=%d y=%c\n", last_x + 1, last_y + 'A');
            }
			get_Input(&x, &y, BLACK, chessboard); // 输入坐标
			if (x == -1 && y == -1)				  // 此时进行悔棋
			{
				undo_move(chessboard, &step);
				step--;
				continue;
			}

			if (is_forbidden(chessboard, x, y, BLACK)) // 禁手判断
			{
				printf("该位置为禁手，请重新选择位置\n");
				step--;
				continue;
			}
			printf("x=%d y=%c\n", x, y + 'A');
			record_move(step, x, y, BLACK);
			chessboard[x][y] = BLACK;

			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			printf("人人对战\n");
			if (is_win(chessboard, MAX_ROW, MAX_COL) == BLACK)
			{
				printf("黑棋获胜\n");
				save_chess(moves, step, MAX_ROW, MAX_COL);
				exit(0);
			}
			last_x = x;
            last_y = y;
		}
		else if (step % 2 == 0)
		{
			if (last_x != -1 && last_y != -1)
            {
                printf("上一步对手下的位置：x=%d y=%c\n", last_x + 1, last_y + 'A');
            }
			get_Input(&x, &y, WHITE, chessboard);
			if (x == -1 && y == -1) // 此时进行悔棋
			{
				undo_move(chessboard, &step);
				step--;
				continue;
			}
			if (is_forbidden(chessboard, x, y, WHITE))
			{
				printf("该位置为禁手，请重新选择位置\n");
				step--;
				continue;
			}
			printf("x=%d y=%c\n", x, y + 'A');
			record_move(step, x, y, WHITE);
			chessboard[x][y] = WHITE;
			draw_chessboard(MAX_ROW, MAX_COL, chessboard);
			printf("人人对战\n");
			if (is_win(chessboard, MAX_ROW, MAX_COL) == WHITE)
			{
				printf("白棋获胜\n");
				save_chess(moves, step, MAX_ROW, MAX_COL);
				exit(0);
			}
			last_x = x;
            last_y = y;
		}
	}
	if (is_full(chessboard, MAX_ROW, MAX_COL) == 1)
	{
		printf("平局\n");
		exit(0);
	}
	return 0;
}