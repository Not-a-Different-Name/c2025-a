#include"game.h"
#include "GomokuBoard.h" // 引入头文件，声明棋盘控件类

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<windows.h>
#include <limits.h>


//电脑下棋函数声明
void computer_board(char board[ROW][COL], int row, int col, char chess);
// AlphaBeta剪枝核心
int alphabeta(const int board[][], int row, int col, int depth, int alpha, int beta, bool maximizing,
    char ai_chess, char player_chess);
// 电脑下棋（AlphaBeta剪枝）
void computer_board_ai(char board[ROW][COL], int row, int col, char chess3, char chess1);

// 生成所有可能的走法（修复：正确外扩与边界夹限）
static int possible_moves(char board[ROW][COL], int moves[ROW * COL][2])
{
    int minrow = ROW, maxrow = -1, mincol = COL, maxcol = -1;

    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (board[i][j] != ' ') {
                if (i < minrow) minrow = i;
                if (i > maxrow) maxrow = i;
                if (j < mincol) mincol = j;
                if (j > maxcol) maxcol = j;
            }
        }
    }

    // 空棋盘：仅中心点
    if (maxrow == -1) {
        int ci = ROW / 2, cj = COL / 2;
        moves[0][0] = ci;
        moves[0][1] = cj;
        return 1;
    }

    // 正确外扩并夹限
    int r0 = minrow - 2; if (r0 < 0) r0 = 0;
    int c0 = mincol - 2; if (c0 < 0) c0 = 0;
    int r1 = maxrow + 2; if (r1 >= ROW) r1 = ROW - 1;
    int c1 = maxcol + 2; if (c1 >= COL) c1 = COL - 1;

    int count = 0;
    for (int i = r0; i <= r1; ++i) {
        for (int j = c0; j <= c1; ++j) {
            if (board[i][j] != ' ')
                continue;

            // 只保留切比雪夫距离<=2的空位
            int near_ = 0;
            for (int di = -2; di <= 2 && !near_; ++di) {
                for (int dj = -2; dj <= 2 && !near_; ++dj) {
                    int ni = i + di, nj = j + dj;
                    if (ni >= 0 && ni < ROW && nj >= 0 && nj < COL &&
                        board[ni][nj] != ' ') {
                        near_ = 1;
                    }
                }
            }
            if (!near_) continue;

            moves[count][0] = i;
            moves[count][1] = j;
            ++count;
        }
    }
    return count;
}




// AlphaBeta剪枝核心
int alphabeta(char board[ROW][COL], int row, int col, int depth, int alpha, int beta, bool maximizing, char ai_chess, char player_chess)
{
    char result = is_end(board, row, col);
    if (result == ai_chess) return 100000;
    if (result == player_chess) return -100000;
    if (result == '-') return 0;


    if (depth == 0) return (evaluate(board, row, col, ai_chess, player_chess)- 1.3 * evaluate(board, row, col, player_chess, ai_chess));//最终评估值------------------
    //优先堵对方1倍权重

    int moves[ROW * COL][2];//表
    int mcount = possible_moves(board, moves);

    // 无可下位置（理应已被终局判断覆盖）
    if (mcount == 0) 
    {
        return (evaluate(board, row, col, ai_chess, player_chess) - 1.2 * evaluate(board, row, col, player_chess, ai_chess));
    }

    if (maximizing)//敌最优, maximazing初始为false
    {
        int best = INT_MIN;//下界表最优
        for (int t = 0; t < mcount; ++t) {
            int i = moves[t][0], j = moves[t][1];
            board[i][j] = ai_chess;
            int val = alphabeta(board, row, col, depth - 1, alpha, beta, false, ai_chess, player_chess);
            board[i][j] = ' ';

            if (val > best) best = val;
            if (best > alpha) alpha = best;
            if (beta <= alpha) break; // 剪枝
        }
        return best;
    }
    else//我（机）最优，敌人大则剪枝
    {
        int best = INT_MAX;
        for (int t = 0; t < mcount; ++t) {
            int i = moves[t][0], j = moves[t][1];
            board[i][j] = player_chess;
            int val = alphabeta(board, row, col, depth - 1, alpha, beta, true, ai_chess, player_chess);
            board[i][j] = ' ';

            if (val < best) best = val;
            if (best < beta) beta = best;
            if (beta <= alpha) break; // 剪枝
        }
        return best;
    }
    
}// ← 这里补上，结束alphabeta函数





// 电脑下棋（AlphaBeta剪枝）
void computer_board_ai(char board[ROW][COL], char ai_chess, char player_chess)
{
    int bestScore = INT_MIN;
    int best_i = -1, best_j = -1;

    int depth = 3; // 搜索深度，可根据性能调整

    int moves[ROW * COL][2];//表
    int mcount = possible_moves(board, moves);

    for (int t = 0; t < mcount; t++) {
        int i = moves[t][0], j = moves[t][1];
        board[i][j] = ai_chess;
        int score = alphabeta(board, row, col, 1 * depth, INT_MIN, INT_MAX, false, ai_chess, player_chess);
        /*Display_board(board, ROW, COL);*/
        board[i][j] = ' ';
        if (score > bestScore) {
            bestScore = score;
            best_i = i; best_j = j;
        }
    }

    
    if (best_i != -1 && best_j != -1)
    {
        board[best_i][best_j] = ai_chess;
        Display_board(board, ROW, COL);
        printf("\nscore == %d\n", bestScore);
    }
    else printf("FUCK\n");
}