#include <stdio.h>

int main()
{
	int input;

	printf("줄을 입력 : ");
	scanf("%d", &input);

	for (int i = 1; i <= input; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 1; j <= i; j++)
			{
				if (j % 2 == 0)
				{
					if (j >= 10)
						printf("%d", j % 10);
					else
						printf("%d", j);
				}
				else
					printf(" ");
			}
		}
		else
		{
			for (int j = 1; j <= i; j++)
			{
				if (j % 2 == 0)
					printf(" ");
				else
				{
					if (j >= 10)
						printf("%d", j % 10);
					else
						printf("%d", j);
				}
			}
		}
		printf("\n");
	}

	return 0;
}
