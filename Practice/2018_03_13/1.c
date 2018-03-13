#include <stdio.h>

int main()
{
	int input;

	printf("첫 줄의 별의 갯수를 입력하시오 : ");
	scanf("%d", &input);


	for (int i = 0; i < input * 2 - 1; i++)
	{
		if (i < input)
		{
			int check = 0;

			while (check < i)
			{
				printf(" ");
				check++;
			}
			for (int j = i; j < input; j++)
				printf("* ");
		}
		else
		{
			int check2 = input * 2 - 2;

			while (check2 > i)
			{
				printf(" ");
				check2--;
			}
			for (int j = i; j >= input - 1; j--)
				printf("* ");
		}
		printf("\n");
	}
}
