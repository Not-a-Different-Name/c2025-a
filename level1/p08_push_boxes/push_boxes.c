#include "box_test.h"



char global_map[ROWS][COLS];

// GetMemory to store file content
char* GetMemory(char** p, int num)
{
    *p = (char*)malloc(num);
    if (NULL == *p)  // 修正：检查*p而不是p
    {
        perror("malloc");
        exit(3);
    }
    return *p;
}

////////---------------------------




//
int get_level(char name[20])// get level file name
{

    FILE* fp = NULL;
    int num = ROWS;

    errno_t err;

    /*printf("file name: ");*/
    /*scanf_s("%19s", name, (unsigned)_countof(name)); */ // 添加长度限制

    if ((err = fopen_s(&fp, name, "r")) != 0)
    {
        printf("无法打开此文件\n");
        exit(1);
    }

    //printf("num(<100): ");
    //scanf_s("%d", &num);

    if (num <= 0 || num > 100)  // 添加上限检查
    {
        printf("wrong num=%d \n", num);
        fclose(fp);
        exit(2);
    }



    // 读取并检查文件内容
    for (int i = 0; i < ROWS; i++)
    {
        /*for (int j = 0; j < COLS; j++)
        {

            global_map[i][j] = fgetc(fp);

        }

        global_map[i][COLS] = '\0';*/ // 确保字符串以null结尾
        if (fgets(global_map[i], 1024, fp) != NULL)//这里读取1024过大量
        {


            global_map[i][COLS] = '\0'; // 确保字符串以null结尾

        }
        else {
            printf("Error reading line %d from file\n", i + 1);

            fclose(fp);
            exit(1);
        }
    }





    fclose(fp);
    return 0;
}


//main for play
int main() {
    printf("pb\n\n");
    printf("press any key to start...\n");
    system("pause");
    system(" -icanon");
    system("cls");

    while (1)
    {

		printf("choose level:\n1.easy\n2.normal\n3.hard\nor 4 for quit");
		char choice = getch();
        switch (choice)
        {
        case '1':
			get_level("1.txt");
			game("1.txt");
            break;
        case '2':
            get_level("2.txt");
			game("2.txt");
            break;
        case '3':
            get_level("3.txt");
			game("3.txt");
            break;
        case '4':
			printf("bye\n");
            return 0;
        default:
            printf("wrong level\n");
            exit(1);
        }

        
        system("pause");
        
    }
    
        
    return 0;
}






