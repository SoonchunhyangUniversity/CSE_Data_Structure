#include <stdio.h>

int main()
{
	int input;
	int *arr;

	printf("라인을 입력 : ");
	scanf("%d", &input);

	arr = (int*)malloc(sizeof(int) * input * 2 - 1);

	for (int i = 1; i <= input; i++)
	{
		for (int j = 0; j < input * 2; j++)
		{
			if (j < input)
			{
				arr[j] = input - j;
				if (arr[j] <= i)
					printf("%d", input - j);
				else
					printf(" ");
			}
			else if (j == input)
				continue;
			else
			{
				arr[j] = j - input + 1;
				if (arr[j] <= i)
					printf("%d", j - input + 1);
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}
