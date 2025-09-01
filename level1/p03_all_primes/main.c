#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    for (int n=2; n<=1000; n++)
    {
    if(n <= 3 && n > 0)
        printf("%d \n", n);
    if(n > 3) {
        int k = sqrt(n);
        for(int i = 2; i <= k; i++)
        {
            if(n % i == 0)
            {
                //printf("%d is not prime\n", n);
                break;
            }else if (i >= k)
            {
                printf("%d \n", n);
                break;
            }

        }
    }




    }



    system("pause");
    return 0;
}