/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 피보나치 수열 검색
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h>

int fib(int n)
{
	if (n < 2)
		return n;
	else
	{
		int tmp, current = 1, last = 0;

		for (int i = 2; i <= n; i++)
		{
			tmp = current;
			current += last;
			last = tmp;
		}
		return current;
	}
}

int main()
{
	int input;
	int arr[31] = { 0 };

	for (int i = 1; i <= 30; i++)
		arr[i] = fib(i);

	printf("검색하고 싶은 피보나치 수열 순번을 입력하시오 : ");
	scanf("%d", &input);

	printf("%d번째 값은 %d입니다.\n\n", input, fib(input));

	printf("피보나치 수열 : ");
	for (int i = 1; i <= 30; i++)
		printf("%d ", arr[i]);

	printf("\n");

	return 0;
}
