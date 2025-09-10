#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "maze_test.h"

// 迷宫尺寸需为奇数
#define ROWS 15
#define COLS 15
//row竖 col横

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define EXIT 'E'

// 方向键
#define KEY_UP 'w'
#define KEY_DOWN 's'
#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'

void printMaze();

void movePlayer(int row, int col);

void game();

int generateMaze(char maze[ROWS][COLS]);