#include "box_test.h"

// 迷宫尺寸
//row竖15 col横15
// 游戏状态
int gameOver = 0;
int playerWon = 0;

// 玩家位置
int playerRow = 0;
int playerCol = 0;


int save_steps(char name[20], int steps)
{
    FILE* fp = NULL;
    errno_t err;
    if ((err = fopen_s(&fp, name, "a")) != 0)
    {
        printf("无法打开此文件\n");
        exit(1);
    }
    fprintf(fp, "steps: %d\n", steps);
    fclose(fp);
    return 0;
}



// 打印迷宫
void printmap()
{
	int count = 0;
    playerWon = 1;
    gameOver = 1;
    for (int i = 0; i < ROWS; i++)
    {
        /*printf("%c", WALL);*/
        for (int j = 0; j < COLS; j++)
        {
            /*if (global_map[i][j] != '\n')*/
                printf("%c ", global_map[i][j]);

                if (global_map[i][j] == TARGET || global_map[i][j] == P)
                {
                    playerWon = 0;
                    gameOver = 0;
                }
        }
        printf("\n");
        /*printf("%c\n",WALL);*/

    }



}



// 移动目标:角色移至(y,x)
int move_character(int p_row, int p_col, int row, int col, char character) {
    // 检查是否可以移动
    if ((global_map[row][col] == PATH || global_map[row][col] == B || global_map[row][col] == P || global_map[row][col] == TARGET)
        && 0 <= row && row < ROWS && 0 <= col && col < ROWS && global_map[row][col] != WALL)
    {

        // 更新玩家位置
        switch (character)
        {
        case PLAYER:
            global_map[row][col] = (global_map[row][col] == TARGET) ? P : character;
            break;

        case BOX:
            global_map[row][col] = (global_map[row][col] == TARGET) ? B : character;
            break;

        default:
            global_map[row][col] = character;
            break;
        }

        switch (character)
        {
        case PLAYER:
            global_map[p_row][p_col] = (global_map[p_row][p_col] == P) ? TARGET : PATH;
            break;

        case BOX:
            global_map[p_row][p_col] = (global_map[p_row][p_col] == B) ? TARGET : PATH;
            break;

        default:
            global_map[p_row][p_col] = PATH;
            break;
        }

        if (character == PLAYER)
        {
            playerRow = row;
            playerCol = col;
        }
		return 0;
    }
    else
        return 1;
}

// 游戏主循环
void game(char name[20])
{
    int step = 0;
    gameOver = 0;
    playerWon = 0;
    playerRow = 0;
    playerCol = 0;
    get_level(name);

    while (!gameOver)
    {


        system("cls");
        printmap();
        printf("Press direction key to move or \"r\" to reset\n");
        printf("%d  %d\nstep: %d", playerCol, playerRow, (step)/2);

        // 方向键移动

        char key;
        int check = 1;
		int judge = 0;
        key = _getch();
        if (check != 0)
        {

            step++;
            switch (key)
            {
            case KEY_UP:
                if ((global_map[playerRow - 1][playerCol] == BOX || global_map[playerRow - 1][playerCol] == B)
                    /*&& (global_map[playerRow - 2][playerCol] != B || global_map[playerRow - 2][playerCol] != BOX)*/)
                    judge = move_character(playerRow - 1, playerCol, playerRow - 2, playerCol, BOX);
				if (judge == 0)
                    move_character(playerRow, playerCol, playerRow - 1, playerCol, PLAYER);
                break;

            case KEY_DOWN:
                if ((global_map[playerRow + 1][playerCol] == BOX || global_map[playerRow + 1][playerCol] == B)
                    /*&& (global_map[playerRow + 2][playerCol] != B || global_map[playerRow + 2][playerCol] != BOX)*/)
                    judge = move_character(playerRow + 1, playerCol, playerRow + 2, playerCol, BOX);
                if (judge == 0)
                    move_character(playerRow, playerCol, playerRow + 1, playerCol, PLAYER);
                break;

            case KEY_LEFT:
                if ((global_map[playerRow][playerCol - 1] == BOX || global_map[playerRow][playerCol - 1] == B)
                    /*&& (global_map[playerRow][playerCol - 2] != B || global_map[playerRow][playerCol - 2] != BOX)*/)
                    judge = move_character(playerRow, playerCol - 1, playerRow, playerCol - 2, BOX);
                if (judge == 0)
                    move_character(playerRow, playerCol, playerRow, playerCol - 1, PLAYER);
                break;

            case KEY_RIGHT:

                if ((global_map[playerRow][playerCol + 1] == BOX || global_map[playerRow][playerCol + 1] == B)
                    /*&& (global_map[playerRow][playerCol + 2] != BOX || global_map[playerRow][playerCol + 2] != B)*/)
                    judge = move_character(playerRow, playerCol + 1, playerRow, playerCol + 2, BOX);
                if (judge == 0)
                    move_character(playerRow, playerCol, playerRow, playerCol + 1, PLAYER);
                break;

            case 'r':
				judge = 2;
				break;
            default:
                printf("\n");
                break;
            }
        }
        system("cls");

        printmap();
        if (judge == 2)
        {
            get_level(name);
            playerRow = 0;
            playerCol = 0;
        }


    }
    save_steps(name, step / 2);
    if (playerWon)
    {
        printf("\nyou win！within %d \n", step/2);

    }
    else
    {
        printf("\ngame over！\n");
    }

}


