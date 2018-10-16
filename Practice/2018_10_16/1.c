#include <stdio.h>
#include <stdlib.h>
#define LEN 30

typedef struct _std
{
	char name[LEN];
	int std_num;
	int record;
} STD;

void selection_sort_by_record(STD *std, int count);
void selection_sort_by_std_num(STD *std, int count);
void display(STD *std, int count);

int main()
{
	STD *std = NULL;
	STD temp;
	int count = 0;
	int i;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d %d", temp.name, &temp.std_num, &temp.record);
		count++;
	}

	rewind(fp);

	std = (STD *)malloc(sizeof(STD) * count);

	for (i = 0; i < count; i++)
		fscanf(fp, "%s %d %d", std[i].name, &std[i].std_num, &std[i].record);

	printf("< 정렬전 데이터 >\n");
	display(std, count);

	selection_sort_by_std_num(std, count);

	printf("< 학번 정렬후 데이터 >\n");
	display(std, count);

	selection_sort_by_record(std, count);

	printf("< 등수 정렬후 데이터 >\n");
	display(std, count);

	fclose(fp);

	return 0;
}

void selection_sort_by_record(STD *std, int count)
{
	int i, j;
	int minIdx;
	STD temp;

	for (i = 0; i < count - 1; i++)
	{
		minIdx = i;

		for (j = i + 1; j < count; j++)
		{
			if (std[j].record < std[minIdx].record)
				minIdx = j;
		}

		temp = std[i];
		std[i] = std[minIdx];
		std[minIdx] = temp;
	}
}

void selection_sort_by_std_num(STD *std, int count)
{
	int i, j;
	int minIdx;
	STD temp;

	for (i = 0; i < count - 1; i++)
	{
		minIdx = i;

		for (j = i + 1; j < count; j++)
		{
			if (std[j].std_num < std[minIdx].std_num)
				minIdx = j;
		}

		temp = std[i];
		std[i] = std[minIdx];
		std[minIdx] = temp;
	}
}

void display(STD *std, int count)
{
	int i;

	printf("---------------------------\n");
	printf("│ 이름   │   학 번  │ 등수│\n");
	printf("---------------------------\n");

	for (i = 0; i < count; i++)
	{
		printf("│ %s │ %8d │ %3d │\n",
			std[i].name, std[i].std_num, std[i].record);
	}

	printf("---------------------------\n\n\n");
}
