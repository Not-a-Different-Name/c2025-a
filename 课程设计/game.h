#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include <limits.h>

#define ROW 15
#define COL 15
//16=15+1


//菜单函数声明
void menu();
//游戏函数声明
void game();
//棋盘初始化函数声明
void Init_board(char board[ROW][COL], int row, int col);
//棋盘展示函数声明
void Display_board(char board[ROW][COL], int row, int col);
//玩家下棋函数声明
void player_board(char board[ROW][COL], int row, int col, char chess, const char* name);

//玩家2下棋函数声明
//void player_board2(char board[ROW][COL], int row, int col);

//电脑下棋函数声明
void computer_board(char board[ROW][COL], int row, int col, char chess);
//判断是否结束函数声明
char is_end(char board[ROW][COL], int row, int col);
//判断谁获胜函数声明
void is_win(char flag, char chess1, char chess2); //#pragma once


// 评估函数：简单统计连子数（可自行优化）
int evaluate(char board[ROW][COL], int row, int col, char ai_chess, char player_chess);

// AlphaBeta剪枝核心
int alphabeta(char board[ROW][COL], int row, int col, int depth, int alpha, int beta, bool maximizing,
    char ai_chess, char player_chess);
// 电脑下棋（AlphaBeta剪枝）
void computer_board_ai(char board[ROW][COL], int row, int col, char chess3, char chess1);