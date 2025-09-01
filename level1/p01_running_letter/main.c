#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int printboard(int i)
{
    system("cls");
    for (int j = 0; j < 60; j++)
    {


        if (j == i )
            printf("A");

        else
            printf(" ");


    }

    return 0;
}

int main(void)
{
    COORD size = { 60, 50 };
    char c[60];
    for (int i = 0; i < 60; i++)
    {
        printboard( i );
        Sleep(30);
    }
    for (int i = 0; i < 60; i++)
    {
        printboard( 60 - i);
        Sleep(30);
    }
    return 0;
}