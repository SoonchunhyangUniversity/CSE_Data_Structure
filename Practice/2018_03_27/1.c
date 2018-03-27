/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 성적 관리 프로그램
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 27
	*
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int **arr2;
	int temp;
	int sum = 0, kor_sum = 0, eng_sum = 0, mat_sum = 0, total_sum = 0;
	double total_avg = 0;
	double avg;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		exit(-1);
	}

	int count = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d %d", &temp, &temp, &temp, &temp);
		count++;
	}

	rewind(fp);

	arr2 = (int**)malloc(sizeof(int *) * count);
	for (int i = 0; i < count; i++)
		arr2[i] = (int *)malloc(sizeof(int) * 4);

	while (!feof(fp))
	{
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < 4; j++)
				fscanf(fp, "%d", &arr2[i][j]);
		}
	}

	printf("===========================================================\n");
	printf("│    학번    │  국어  │  영어  │  수학  │  총점  │  평균  │\n");

	for (int i = 0; i < count; i++)
	{
		int j = 0;

		sum = arr2[i][j + 1] + arr2[i][j + 2] + arr2[i][j + 3];
		avg = (double)sum / 3;
		kor_sum += arr2[i][j + 1];
		eng_sum += arr2[i][j + 2];
		mat_sum += arr2[i][j + 3];
		total_sum += sum;
		total_avg += avg;

		printf("│  %8d  │  %4d  │  %4d  │  %4d  │  %4d  │  %4.2f │\n", arr2[i][j], arr2[i][j + 1], arr2[i][j + 2], arr2[i][j + 3], sum, avg);
	}

	printf("===========================================================\n");
	printf("│   평 균    │  %4.2f │  %4.2f │  %4.2f │  %4.2f │ %4.2f │\n", (double)kor_sum / count, (double)eng_sum / count, (double) mat_sum / count, (double)total_sum / count, (double)total_avg / count);
	printf("===========================================================\n");

	for(int i = 0; i < 4; i++)
		free(arr2[i]);
	free(arr2);

	return 0;
}
