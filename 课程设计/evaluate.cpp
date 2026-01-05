#include"game.h"

// 评估函数
		// 检查每个点
		//2025.8.30 井字棋 minimax 实现， 五子棋alphabeta开始尝试
//暂时信AI的
//•	只有当当前点是该方向的起点（前一个格子不属于本方棋子），才开始统计该方向的连续五子。8.30晚
//8.31-明天改这个和AI算法
int evaluate(char board[ROW][COL], int row, int col, char chess, char opponent_chess)
{
	static const int drect[4][2] = { {0,1},{1,0},{1,1},{1,-1} }; // 方向向量：右、下、右下、右上
	int score = 0;
	
	/*Display_board(board, ROW, COL);*/
	// 检查每个点   评分，启动！！！！！！！！！！！！！
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] != chess) continue;

            for (int d = 0; d < 4; d++) {
                // 只从线段起点统计
                int pi = i - drect[d][0], pj = j - drect[d][1];
                if (pi >= 0 && pi < row && pj >= 0 && pj < col &&
                    board[pi][pj] == chess) {
                    continue;
                }

                int count = 0;
                for (int step = 0; step < 6; step++) {
                    int ni = i + step * drect[d][0];
                    int nj = j + step * drect[d][1];
                    if (ni < 0 || ni >= row || nj < 0 || nj >= col) break;
                    if (board[ni][nj] != chess) break;
                    count++;
                }

                // 统计两端开口
                int openends = 0;
                if (pi >= 0 && pi < row && pj >= 0 && pj < col &&
                    board[pi][pj] == ' ') {
                    openends++;
                }
                int ei = i + count * drect[d][0];
                int ej = j + count * drect[d][1];
                if (ei >= 0 && ei < row && ej >= 0 && ej < col &&
                    board[ei][ej] == ' ') {
                    openends++;
                }

                switch (count) {
                case 0: break;
                case 1:
                    score += (openends == 2) ? 10 : (openends == 1 ? 2 : 0);
                    break;
                case 2:
                    score += (openends == 2) ? 500 : (openends == 1 ? 50 : 0);
                    break;
                case 3:
                    score += (openends == 2) ? 5000 : (openends == 1 ? 500 : 0);
                    break;
                case 4:
                    score += (openends == 2) ? 100000 : (openends == 1 ? 10000 : 0);
                    break;
                default: // >=5
                    score = INT_MAX;
                    break;
                }
            }
        }
    }
    return score;
}

