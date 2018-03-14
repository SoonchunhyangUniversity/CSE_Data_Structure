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

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언

int main()
{
	int input; // 첫 번째 줄의 별의 개수를 담을 변수 선언

	printf("첫 줄의 별의 갯수를 입력하시오 : ");
	scanf("%d", &input); // scanf로 별의 개수를 입력 받음

	/* 별을 출력하는 반복문 input이 6이면 11줄 출력 */
	for (int i = 0; i < input * 2 - 1; i++)	// input * 2 - 1 번 반복한다
	{
		/* 1번째 줄부터 input번째 줄을 출력하기위한 if 조건문 */
		if (i < input) // i = 0, 1, 2, 3... input - 1까지 0부터 시작 -> input개 출력
		{
			int check = 0;
			// 공백을 출력할때 사용할 변수 check 선언, 다음 반복문으로 넘어가면 재 초기화

			/* 공백을 출력하기 위한 반복문 */
			while (check < i) // check변수가 i와 같아지면 탈출
			{
				printf(" "); // 공백 출력
				check++; // check = check + 1;
			}
			/* 별을 출력하기 위한 반복문 */
			for (int j = i; j < input; j++)	// input - i번 만큼 반복
				printf("* "); // 별 출력
		}
		/* 나머지 줄을 출력하기 위한 else 조건문 */
		else
		{
			int check2 = input * 2 - 2;
			// input번쨰 줄 이후를 출력할때 공백을 출력할때 사용할 변수 check2선언 및 input * 2 - 2로 초기화

			/* 공백을 출력하기 위한 반복문 */
			while (check2 > i) // i 가 check2 변수와 같아지면 탈출
			{
				printf(" "); // 공백 출력
				check2--; // check2 = check2 - 1;
			}
			for (int j = i; j >= input - 1; j--) // j가 input - 1과 같아질 때 까지 반복
				printf("* "); // 별 출력
		}
		printf("\n"); // 안쪽 반복문이 종료되면(한 줄이 출력되면) 개행
	}

	return 0; // 메인함수 종료
}
