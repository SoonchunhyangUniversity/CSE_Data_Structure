/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 숫자 계단 출력
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 13
	*
*/

#include <stdio.h>

int main()
{
	int input;

	printf("줄을 입력 : ");
	scanf("%d", &input);

	for (int i = 1; i <= input; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 1; j <= i; j++)
			{
				if (j % 2 == 0)
				{
					if (j >= 10)
						printf("%d", j % 10);
					else
						printf("%d", j);
				}
				else
					printf(" ");
			}
		}
		else
		{
			for (int j = 1; j <= i; j++)
			{
				if (j % 2 == 0)
					printf(" ");
				else
				{
					if (j >= 10)
						printf("%d", j % 10);
					else
						printf("%d", j);
				}
			}
		}
		printf("\n");
	}

	return 0;
}
