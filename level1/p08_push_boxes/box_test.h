#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <errno.h>


// �Թ��ߴ���Ϊ����
#define ROWS 10
#define COLS 10
//row�� col��

#define WALL '#'
#define PATH ' '
#define PLAYER 'P'
#define P 'p'
#define B 'b'
#define TARGET 'T'
#define BOX 'B'

// �����
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

// �Թ���ͼ
extern char global_map[ROWS][COLS];

void printmap();

int move_character(int p_row, int p_col, int row, int col, char character);

void game(char name[20]);

//int check_push_boxes(int p_row, int p_col, char key);

char* GetMemory(char** p, int num);

int get_level(char name[20]);
//int generateMaze(char maze[ROWS][COLS]);


























/***
 *                    _ooOoo_
 *                   o8888888o
 *                   88" . "88
 *                   (| -_- |)
 *                    O\ = /O
 *                ____/`---'\____
 *              .   ' \\| |// `.
 *               / \\||| : |||// \
 *             / _||||| -:- |||||- \
 *               | | \\\ - /// | |
 *             | \_| ''\---/'' | |
 *              \ .-\__ `-` ___/-. /
 *           ___`. .' /--.--\ `. . __
 *        ."" '< `.___\_<|>_/___.' >'"".
 *       | | : `- \`.;`\ _ /`;.`/ - ` : | |
 *         \ \ `-. \_ __\ /__ _/ .-` / /
 * ======`-.____`-.___\_____/___.-`____.-'======
 *                    `=---='
 *
 * .............................................
 *          ���汣��             ����BUG
 */