#include "main.h"

int main(void)
{
	if (BONUS == 0)
		printf("Mandatory\n");
	else
	{
		test();
		printf("bonus\n");
	}
	printf("%d\n", BONUS);
	return (0);
}