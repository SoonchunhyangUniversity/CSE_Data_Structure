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
	char oper;
	unsigned int input;
	double result;
	clock_t start, finish;
	double time;

	FILE *fp = fopen("data.txt", "w");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	scanf("%c", &oper);
	scanf("%d", &input);

	result = input;

	start = clock();

	switch (oper)
	{
	case '+':
		for(int i = 0; i < input; i++)
			result += i;
		break;
	case '-':
		for(int i = 0; i < input; i++)
			result -= i;
		break;
	case '*':
		for (int i = 0; i < input; i++)
			result *= i;
		break;
	case '/':
		for (int i = 0; i < input; i++)
			result /= i;
		break;
	default:
		printf("OPERATOR INPUT ERROR!\n");
		break;
	}

	finish = clock();

	time = (double)(finish - start) / CLOCKS_PER_SEC;

	fprintf(fp, "연산을 선택하시오 : %c\n", oper);
	fprintf(fp, "반복 횟수를 입력하세요 : %d\n\n", input);
	fprintf(fp, "걸린시간은 %f입니다.\n", time);

	fclose(fp);	// 파일 포인터 fp 닫기

	return 0;
}
