/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 최댓값,최솟값 찾기
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 12
	*
*/

#include <stdio.h>
#include <time.h>

int main()
{
	int num, input, sum;
	clock_t start, finish;
	double time;

	FILE *fp = fopen("data.txt", "w");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	scanf("%d", &num);
	scanf("%d", &input);

	start = clock();

	switch (num)
	{
	case 1:
		sum = input * input;
		break;
	case 2:
		sum = 0;
		for (int i = 0; i < input; i++)
			sum = sum + input;
		break;
	case 3:
		sum = 0;
		for (int i = 0; i < input; i++)
			for (int j = 0; j < input; j++)
				sum = sum + 1;
		break;
	default:
		printf("NUM INPUT ERROR!\n");
		break;
	}

	finish = clock();

	time = (double)(finish - start) / CLOCKS_PER_SEC;

	fprintf(fp, "알고리즘을 선택하세요<1, 2, 3> : %d\n", num);
	fprintf(fp, "숫자를 입력하시오 : %d\n\n", input);
	fprintf(fp, "걸린시간은 %f입니다.\n", time);

	return 0;
}
