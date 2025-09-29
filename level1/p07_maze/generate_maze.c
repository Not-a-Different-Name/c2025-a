#include "maze_test.h"



// DFS
void generateMazeDFS(int x, int y, char maze[ROWS][COLS]) 
{
    maze[y][x] = PATH;  // ���Ϊͨ·

    // ����
    int dirs[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

    // ����
    for (int i = 0; i < 4; i++) {
        // /*srand((unsigned int)time(NULL));
        int r = rand() % 4;

        int tempX = dirs[i][0];
        int tempY = dirs[i][1];

        dirs[i][0] = dirs[r][0];
        dirs[i][1] = dirs[r][1];

        dirs[r][0] = tempX;
        dirs[r][1] = tempY;
    }

    // ����ÿ������
    for (int i = 0; i < 4; i++) {
        int nx = x + 2 * dirs[i][0];
        int ny = y + 2 * dirs[i][1];

        if (nx > 0 && nx < COLS - 1 && ny > 0 && ny < ROWS - 1 && maze[ny][nx] == '#') {
            
            // ��ͨǽ��
            maze[y + dirs[i][1] ][x + dirs[i][0] ] = PATH;
            if(nx == COLS - 2 && ny == ROWS - 2)
            {
                maze[ny][nx] = EXIT;
                maze[y + dirs[i][1]][x + dirs[i][0]] = PATH;
                break;
			}
            generateMazeDFS(nx, ny, maze);
        }
    }
}




//generate maze
int generateMaze(char maze[ROWS][COLS]) {
	// ��ʼ���Թ���ȫ����Ϊǽ
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			maze[i][j] = WALL;
		}
	}

    printMaze();
	system("pause");
    // ���ó���λ��
	//maze[ROWS - 2][COLS - 2] = EXIT;
	
	//
    generateMazeDFS(1, 1, maze);
    maze[1][1] = PLAYER;



	return 0;
}