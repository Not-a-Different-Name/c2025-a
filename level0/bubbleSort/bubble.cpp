#include <stdio.h>
#include <stdlib.h>

int bubble(int* c, int num)
{
	return 0;
}

int main(void)
{
	int count[10];
	for (int i = 0; i < 10; i++)
	{
		count[i] = rand();
	}

	bubble(count, 10);
	for (int i = 0; i < 10; i++)
	{
		printf("%d ", count[i]);
	}
	return 0;
}