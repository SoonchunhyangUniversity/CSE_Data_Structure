#include <stdio.h>
#include <string.h>
#define MAX 1000

typedef struct _std
{
	char std_num[MAX];
	char name[MAX];
	int kor;
	int eng;
	int mat;
	int sum;
	double avg;
	int rank;
} STUDENT;

int main()
{
	int i, j, line_count = 0, idx = -1, rank_temp;
	char temp[MAX], input[MAX];

	STUDENT *std;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fgets(temp, MAX, fp);
		line_count++;
	}

	rewind(fp);

	std = (STUDENT *)malloc(sizeof(STUDENT) * line_count);

	for (i = 0; i < line_count; i++)
	{
		fscanf(fp, "%s %s %d %d %d", std[i].std_num, std[i].name, &std[i].kor, &std[i].eng, &std[i].mat);
		std[i].sum = std[i].kor + std[i].eng + std[i].mat;
		std[i].avg = (double)std[i].sum / 3;
		std[i].rank = 1;
	}

	for (i = 0; i < line_count; i++)
	{
		for (j = 0; j < line_count; j++)
		{
			if (std[i].avg < std[j].avg)
				std[i].rank++;
		}
	}

	printf("학생의 이름 또는 학번을 입력하세요 : ");
	scanf("%s", &input);

	for (i = 0; i < line_count; i++)
	{
		if (!strcmp(input, std[i].name) || !strcmp(input, std[i].std_num))
			idx = i;
	}

	if (idx == -1)
	{
		printf("찾으려는 학생은 존재하지 않습니다.\n");
	}
	else
	{
		printf("입력하신 학생 \"%s\"학생의 정보는 아래와 같습니다.\n", std[idx].name);
		printf("│ 학   번 │ 국어 │ 영어 │ 수학 │ 총 점 │ 평 균 │ 석 차 │\n");
		printf("│======================================================│\n");
		printf("│ %s│ %4d │ %4d │ %4d │ %4d │  %4.2lf │  %d/%d  │\n", std[idx].std_num, std[idx].kor, std[idx].eng, std[idx].mat, std[idx].sum, std[idx].avg, std[idx].rank, line_count);
	}

	fclose(fp);
	free(std);

	return 0;
}
