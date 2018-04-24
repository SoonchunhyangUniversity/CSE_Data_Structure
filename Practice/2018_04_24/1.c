#include <stdio.h>

int repeat_count;

int Sol(int num)
{
	if (num % 2 == 0)
	{
		if (num == 0)
			return 0;
		else
		{
			repeat_count++;
			return num + Sol(num - 2);
		}
	}
	else
	{
		if (num == 1)
		{
			repeat_count++;
			return 1;
		}
		else
		{
			repeat_count++;
			return num + Sol(num - 2);
		}
	}
}

int main()
{
	int num, result;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &num);
		repeat_count = 0;
		result = Sol(num);
		printf("입력 받은 수 : %d\n", num);
		printf("계산된 횟수 : %d\n", repeat_count);
		printf("계산 결과 값 : %d\n", result);
	}

	fclose(fp);

	return 0;
}
