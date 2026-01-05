#define _CRT_SECURE_NO_WARNINGS 1
#include"game.h"


int main()
{
	srand((unsigned int)time(NULL));
	int input = 0;
	do
	{
		menu();
		printf("请选择:->");
		scanf("%d", &input);
		system("cls");
		switch (input)
		{
		case 1:
			game();
			break;
		case 0:
			break;
		default:
			printf("已退出！\n");
			break;
		}
	} while (input);
	return 0;
}