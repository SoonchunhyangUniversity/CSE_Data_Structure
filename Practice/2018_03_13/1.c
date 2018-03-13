/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 별 출력 프로그램
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 13
	*
*/

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

	return 0;
}
