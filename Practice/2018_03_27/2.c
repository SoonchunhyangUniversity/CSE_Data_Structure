/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 난수의 생성 및 검색
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	int **matrix;
	int COLS, ROWS;
	int input;
	int COLS_temp = -1, ROWS_temp = -1;
	int i, j;

	printf("행과 열의 크기를 입력하시오 : ");
	scanf("%d %d", &COLS, &ROWS);

	matrix = (int **)malloc(sizeof(int *) * ROWS);
	for (i = 0; i < ROWS; i++)
		matrix[i] = (int *)malloc(sizeof(int) * COLS);

	srand((unsigned)time(NULL));

	for (i = 0; i < COLS; i++)
	{
		for (j = 0; j < ROWS; j++)
		{
			matrix[i][j] = (rand() % 100) + 1;
		}

	}

	printf("난수 생성 완료!\n");

	printf("검색할 숫자를 입력하시오 : ");
	scanf("%d", &input);

	for (i = 0; i < COLS; i++)
	{
		for (j = 0; j < ROWS; j++)
		{
			if (matrix[i][j] == input)
			{
				COLS_temp = i;
				ROWS_temp = j;
				break;
			}
		}
	}

	if (COLS_temp == -1 && ROWS_temp == -1)
		printf("검색하신 숫자는 존재하지 않습니다.\n");
	else
		printf("검색하신 숫자 %d는 %d행 %d열에 있습니다.\n", input, COLS_temp + 1, ROWS_temp + 1);

	printf("저장된 행렬-----\n");
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
			printf("%d ", matrix[i][j]);

		printf("\n");
	}

	for (i = 0; i < ROWS; i++)
		free(matrix[i]);
	free(matrix);


	return 0;
}
