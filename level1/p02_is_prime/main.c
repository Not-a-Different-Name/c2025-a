#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    int n;
    printf("\n Enter a number: ");
    scanf("%d", &n);
    if(n <= 3 && n > 0)
        printf("%d is  prime\n", n);
    if(n > 3)
    {
        int k = sqrt(n);
        for(int i = 2; i <= k; i++)
        {
            if(n % i == 0)
            {
                printf("%d is not prime\n", n);
                break;
            }else if (i >= k)
            {
                printf("%d is  prime\n", n);
                break;
            }

        }
    system("pause");
        return 0;



    }




}