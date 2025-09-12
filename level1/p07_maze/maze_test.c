#include "maze_test.h"

// 迷宫尺寸
//row竖15 col横15
// 游戏状态
int gameOver = 0;
int playerWon = 0;

// 玩家位置
int playerRow = 1;
int playerCol = 1;

// 迷宫地图
char maze[ROWS][COLS];



// 打印迷宫
void printMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}



// 移动玩家
void movePlayer(int row, int col) {
    // 检查是否可以移动
    if (maze[row][col] != WALL) {
        // 如果是出口，游戏结束
        if (maze[row][col] == EXIT) {
            playerWon = 1;
            gameOver = 1;
        }

        // 更新玩家位置
        maze[playerRow][playerCol] = PATH;
        playerRow = row;
        playerCol = col;
        maze[playerRow][playerCol] = PLAYER;
    }else if(maze[row][col] == WALL)
    {
        // 撞墙
		/*Beep(523, 100);*/


	}
}

// 游戏主循环
void game() {
    playerRow = 1;
    playerCol = 1;//初始位置

    while (!gameOver) {
        system("cls");
        printMaze();
        printf("input a w s d to move\n");
        

        // 方向键移动
        char key;
        int check = 1;
		key = getch();
        if (check != 0) 
        {  

            switch (key) {
            case KEY_UP:
                movePlayer(playerRow - 1, playerCol);
                break;
            case KEY_DOWN:
                movePlayer(playerRow + 1, playerCol);
                break;
            case KEY_LEFT:
                movePlayer(playerRow, playerCol - 1);
                break;
            case KEY_RIGHT:
                movePlayer(playerRow, playerCol + 1);
                break;
			default:
                printf("\n");
                break;
            }
        }
        
    }

    system("cls");
    printMaze();
    if (playerWon) 
    {
        printf("\nyou win！\n");
    }
    else 
    {
        printf("\ngame over！\n");
    }
}


//main for play
int main() {
    printf("A_maze\n");
    printf("press any key to start...\n");
	system("pause");
    system("sys -icanon");

	generateMaze(maze);
    game();
    system("pause");
    return 0;
}