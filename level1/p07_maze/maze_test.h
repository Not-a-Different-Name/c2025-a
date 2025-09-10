#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "maze_test.h"

// �Թ��ߴ���Ϊ����
#define ROWS 15
#define COLS 15
//row�� col��

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define EXIT 'E'

// �����
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

void printMaze();

void movePlayer(int row, int col);

void game();

int generateMaze(char maze[ROWS][COLS]);