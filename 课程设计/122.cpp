#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"


//菜单实现
void menu()
{
	printf("*************************\n");
	printf("*******  1.play  ********\n");
	printf("*******  0.exit  ********\n");
	printf("*************************\n");
}




//游戏函数-----------------------------------------------------------------
void game()
{

	char board[ROW][COL] = { 0 };
	char chess1 = 0;
	char chess2 = 0;
	char chess3 = 0;
	printf("玩家1请选择棋子: ");
	scanf(" %c", &chess1);
	/*printf("\n玩家2请选择棋子: ");
	scanf(" %c", &chess2);*/
	printf("\n请选择电脑棋子: ");
	scanf(" %c", &chess3);

	Init_board(board, ROW, COL);//棋盘初始化
	Display_board(board, ROW, COL);//棋盘展示
	while (1)
	{
		player_board(board, ROW, COL, chess1, "player1");//玩家1下棋
		if (is_end(board, ROW, COL) != 'c')
		{
			break;
		}

		//player_board(board, ROW, COL, chess2, "player2");//玩家2下棋
		computer_board_ai(board, ROW, COL, chess3, chess1);
		if (is_end(board, ROW, COL) != 'c')
		{
			break;
		}

		/*computer_board_ai(board, ROW, COL, chess1, chess3);
		if (is_end(board, ROW, COL) != 'c')
		{
			break;
		}
		system("pause");*/
	}
	is_win(is_end(board, ROW, COL), chess1, chess3);
}

//棋盘初始化
void Init_board(char board[ROW][COL], int row, int col)
{
	int i = 0; 
	int j = 0;
	char string = 0;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			
				board[i][j] = ' ';
		}
	}
}

//棋盘展示
void Display_board(char board[ROW][COL], int row, int col)
{
	system("cls");
	// 打印列号
	printf("   ");
	for (int j = 1; j <= col; j++)
		printf("%3d ", j);
	printf("\n");

	for (int i = 0; i < row; i++)
	{
		// 打印行号
		printf("%2d ", i + 1);
		for (int j = 0; j < col; j++)
		{
			printf(" %c ", board[i][j]);
			//if (j < col - 1)
			printf("|");
		}
		printf("\n");
		// 打印分隔线
		if (i <= row - 1)
		{
			printf("   ");
			for (int j = 0; j < col; j++)
			{
				printf("---");
				//if (j < col - 1)
				printf("+");
			}
			printf("\n");
		}
	}
}


//玩家下棋
void player_board(char board[ROW][COL], int row, int col, char chess, const char *name)
{
	int i = 0;
	int j = 0;
	while (1)
	{
		int i = 0;
		int j = 0;
		printf("%s请输入下棋位置->", name);
		printf("行：");
		scanf("%d", &i);
		printf("列：");
		scanf("%d", &j);
		if (i <= row && i >= 1 && j <= col && j >= 1)
		{
			if (board[i-1][j-1] == ' ')
			{
				board[i-1][j-1] = chess;
				Display_board(board, ROW, COL);//棋盘展示
				break;
			}
			else
			{
				printf("坐标已有棋，清重新输入！\n");
			}
		}
		else
		{
			printf("坐标非法，清重新输入！\n");
		}
	}
}

/*
//玩家2下棋
void player_board2(char board[ROW][COL], int row, int col)
{
	int i = 0;
	int j = 0;
	while (1)
	{
		int i = 0;
		int j = 0;
		printf("p2请输入下棋位置->");
		scanf("%d %d", &i, &j);
		if (i <= row && i >= 1 && j <= col && j >= 1)
		{
			if (board[i - 1][j - 1] == ' ')
			{
				board[i - 1][j - 1] = '?';
				Display_board(board, ROW, COL);//棋盘展示
				break;
			}
			else
			{
				printf("坐标已有棋，清重新输入！\n");
			}
		}
		else
		{
			printf("坐标非法，清重新输入！\n");
		}
	}
}
*/






// 判断是否结束（横竖）
char is_end(char board[ROW][COL], int row, int col)
{
	int drect[4][2] = { {0,1},{1,0},{1,1},{1,-1} }; // 方向向量：右、下、右下、右上


	// 检查每个点
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			char curr = board[i][j];
			if (curr == ' ')
				continue;

			for(int d = 0; d < 4; d++) {
				int count = 0;
				for(int step = 0; step < 5; step++) {
					int ni = i + step * drect[d][0];
					int nj = j + step * drect[d][1];
					if (board[ni][nj] != curr)break;
					count++;
				}
				if(count >= 5) 
				{
					return curr;
				}
			}
			
		}
	}
	// 检查是否有空位
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (board[i][j] == ' ')
				return 'c'; // 未结束
	return '-'; // 平局
}




//判断谁获胜
void is_win(char flag, char chess1, char chess2)
{
	if (flag == chess1)
	{
		printf("玩家1获胜！\n");
		system("pause");
		system("cls");
	}
	else if (flag == chess2)
	{
		printf("2B获胜！\n");
		system("pause");
		system("cls");
	}
	//else if (flag == '#')
	//{
	//	printf("SB获胜！\n");
	//	system("pause");
	//	system("cls");
	//}
	else if (flag == '-')
	{
		printf("平局!\n");
		system("pause");
		system("cls");
	}
}