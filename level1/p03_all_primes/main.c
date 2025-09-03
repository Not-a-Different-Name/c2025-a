#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <time.h>

int main(void)
{
    clock_t start = clock(); // 计时开始
    Sleep(1);
    for (int n = 2; n <= 1000; n++)
    {

        if (n <= 3 && n > 0)
            printf("%d \n", n);
        if (n > 3) {
            int k = sqrt(n);
            for (int i = 2; i <= k; i++)
            {
                if (n % i == 0)
                {
                    //printf("%d is not prime\n", n);
                    break;
                }
                else if (i >= k)
                {
                    printf("%d \n", n);
                    break;
                }

            }
        }


    }
    clock_t end = clock(); // 计时结束
    double duration = (double)(end - start) / CLOCKS_PER_SEC;
    printf("运行时间: %.100f 秒\n", duration);
    /*system("pause");*/
    return 0;
}