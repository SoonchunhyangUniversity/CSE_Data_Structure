/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열의 데이터 처리
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int *temp;
	int num;
	
	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	int count = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d", &num);
		count++;
	}

	temp = (int *)malloc(sizeof(int) * count);

	rewind(fp);

	int count2 = 0;

	while (count != count2)
	{
		fscanf(fp, "%d", &temp[count2]);
		count2++;
	}

	printf("변경 전 : \n");
	for (int i = 0; i < count; i++)
	{
		printf("%d ", temp[i]);
	}
	printf("\n");

	int temp_num;

	count2 -= 1;

	for (int i = 0; i < count2 / 2; i++)
	{
		temp_num = temp[i];
		temp[i] = temp[count2];
		temp[count2] = temp_num;
		count2--;
	}

	printf("변경 후 : \n");
	for (int i = 0; i < count; i++)
	{
		printf("%d ", temp[i]);
	}
	printf("\n");

	free(temp);
    fclose(fp);

	return 0;
}
