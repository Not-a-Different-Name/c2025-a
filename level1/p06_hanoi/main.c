#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>


//to move the disk from pos1 to pos2
void move(char pos1, char pos2)
{
    printf("%c -> %c\n", pos1, pos2);//打印移动过程
}

//hannuo function
void hannuo(int n, char pos1, char pos2, char pos3)//1借2移动至3
{
    if (n == 1) move(pos1, pos3);//最后一层
    else
    { 
        hannuo(n - 1, pos1, pos3, pos2);//1移动至2
        move(pos1, pos3);//剩下较大数移动至3
        hannuo(n - 1, pos2, pos1, pos3);//2移动至3
    }
}
//自我总结：递归将过程分为 借位移小，直接移大，小位移大三部分，从底到上实现，移动数2^n-1

//driver function
int main()
{
    //int n = 0;
    int n = 64 ;
    printf("We needn't input! The n is %d\n",n);//2^64 - 1 = 18,446,744,073,709,551,615
    printf("The bad news is: you are neeeded to close the .exe by yourself");
    //scanf_s("%d", &n);
    hannuo(n, 'A', 'B', 'C');//start;pos1 = A;pos2 = B;pos3 = C
    return 0;
}