#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int do_work(int num, int* q) //
{
    int count = 0;
    for (int n = 1; n <= num; n++)
    {
        if (n <= 3 && n > 0)
        {
            count++;
            *q++ = n;
        }

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
                    count++;
                    *q++ = n;
                    break;
                }

            }
        }

    }
    return count;
}

//int goldbach(int add, int n, int* p, int result[100][2])
//{
//    for(int i = 0; i < n; i++)
//
//
//
//}




int main(void)
{
    int result[50][3] = { 0 };//100
    int pnum[50] = { 0 };
    int n = do_work(100, pnum);//个数
    int target = 2 ;

    for (int i = 0; i < 50; i++)
    {
        if (pnum[i] != 0)
            printf("%d\n ", pnum[i]);
        result[i][2] = i * 2 +2;

    }

    for(int i = 0; i < n; i++)
    {
        for(int j = i; j < n; j++)
        {
            int sum = pnum[i] + pnum[j];
            for(int k = 0; k < 50; k++)
            {
                if (sum == result[k][2])
                {
                    result[k][0] = pnum[i];
                    result[k][1] = pnum[j];

                }

            }
        }
    }
    for (int k = 0; k < 50; k++)
    {

        printf("%d + %d = %d\n", result[k][0], result[k][1], result[k][2]);


    }
    return 0;

}