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

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언

int main()
{
	int input; // 출력할 줄을 받을 정수형 변수 선언
	int *arr; // 정수들을 담을 정수형 포인터 변수 선언 -> 배열의 역할(동적할당)

	printf("라인을 입력 : ");
	scanf("%d", &input); // scanf를 이용해여 input에 몇 줄을 출력할지 저장

	 /*
		 포인터 변수 arr 동적할당
		 예를들어 input이 5일 경우 5번째 줄은 543212345로 9개의 정수를 출력해야함
		 sizeof(int) * (input * 2 - 1) -> 4 * (5 * 2 - 1) = 36, 36바이트의 공간을 할당
	 */
	arr = (int*)malloc(sizeof(int) * (input * 2 - 1));

	/* i가 input과 같아질때 까지 반복 */
	for (int i = 1; i <= input; i++) // input번 반복
	{
		/* j가 input * 2와 같아질때 까지 반복 */
		for (int j = 0; j < input * 2; j++)	// input * 2번 반복
		{
			if (j < input) // 543212345 에서 54321까지의 범위
			{
				arr[j] = input - j;
				// 동적할당한 배열 arr에 input - j 저장, j = 0 일떄 arr[0] = 5 - 0
				if (arr[j] <= i) // arr[j]가 i보다 작거나 같다면
					printf("%d", arr[j]); // arr[j]의 값을 출력
				else // arr[j] > i
					printf(" "); // 공백 출력
			}
			else if (j == input) // j와 input이 같을때
				continue; // 반복문 진행
			else // 543212345에서 2345까지의 범위
			{
				arr[j] = j - input + 1;
				// 동적할당한 배열 arr에 j - input + 1 저장, j = 6 일때 arr[6] = 6 - 5 + 1
				if (arr[j] <= i) // arr[j]가 i보다 작거나 같다면
					printf("%d", arr[j]); // arr[j]의 값을 출력
				else // arr[j] > i
					printf(" "); // 공백 출력
			}
		}
		printf("\n"); // 안쪽 반복문이 종료되면(한 줄이 출력되면) 개행
	}

	return 0; // 메인함수 종료
}
