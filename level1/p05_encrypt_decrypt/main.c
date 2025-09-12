#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS 1

// 加密函数
void encryption(char* data, int key)
{
    for (int i = 0; data[i] != '\0'; i++)
    {
         data[i] = data[i] ^ key ;
        //data[i] = data[i] + key ;
    }
    printf("encrypt string: %s\n", data);
}

// 解密函数
void decrypt(char* data, int key)
{
    for (int i = 0; data[i] != '\0'; i++)
    {
         data[i] = data[i]  ^ key;
        //data[i] = data[i]  - key;
    }
    printf("decrypt string: %s\n", data);
}

int main(void)
{
    char data[1024];
    int key;

    printf("input string: ");
    scanf_s("%1023s", data, (unsigned)_countof(data));

    printf("input key: ");
    scanf_s("%d", &key);

    encryption(data, key);

    decrypt(data, key);

    return 0;
}