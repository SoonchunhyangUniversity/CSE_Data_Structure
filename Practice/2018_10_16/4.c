/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 셸 정렬 프로그램
 * 작성일 : 2018-10-16
 */

#include <stdio.h>
#include <stdlib.h>
#define LEN 30

typedef struct _std
{
	char name[LEN];
	char phone_num[LEN];
	int std_num;
} STD;

void InsertSort(STD *std, int first, int last, int gap);
void ShellSort(STD *std, int n);
void Display(STD *std, int n);

int main()
{
	STD *std = NULL;
	STD temp;
	int count = 0;
	int i;

	FILE *fp = fopen("data4.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %d %s", temp.name, &temp.std_num, temp.phone_num);
		count++;
	}

	rewind(fp);

	std = (STD *)malloc(sizeof(STD) * count);

	for (i = 0; i < count; i++)
		fscanf(fp, "%s %d %s", std[i].name, &std[i].std_num, std[i].phone_num);

	printf("< 정렬 전 >\n");
	Display(std, count);

	ShellSort(std, count);

	printf("< 정렬 후 >\n");
	Display(std, count);

	fclose(fp);

	return 0;
}

void InsertSort(STD *std, int first, int last, int gap)
{
	int i, j;
	STD temp;
	int key;

	for (i = first + gap; i <= last; i = i + gap)
	{
		temp = std[i];
		key = temp.std_num;

		for (j = i - gap; j >= first&& key > std[j].std_num; j = j - gap)
			std[j + gap] = std[j];

		std[j + gap] = temp;
	}
}

void ShellSort(STD *std, int n)
{
	int i, gap;

	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if (gap % 2 == 0)
			gap++;

		for (i = 0; i < gap; i++)
			InsertSort(std, i, n - 1, gap);
	}
}

void Display(STD *std, int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%s %d %s\n",
			std[i].name, std[i].std_num, std[i].phone_num);
	}

	printf("\n");
}
