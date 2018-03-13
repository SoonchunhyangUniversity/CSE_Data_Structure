/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 피라미드 만들기
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 13
	*
*/

#include <stdio.h>

int main()
{
	int input;
	int *arr;

	printf("라인을 입력 : ");
	scanf("%d", &input);

	arr = (int*)malloc(sizeof(int) * (input * 2 - 1));

	for (int i = 1; i <= input; i++)
	{
		for (int j = 0; j < input * 2; j++)
		{
			if (j < input)
			{
				arr[j] = input - j;
				if (arr[j] <= i)
					printf("%d", input - j);
				else
					printf(" ");
			}
			else if (j == input)
				continue;
			else
			{
				arr[j] = j - input + 1;
				if (arr[j] <= i)
					printf("%d", j - input + 1);
				else
					printf(" ");
			}
		}
		printf("\n");
	}

	return 0;
}
