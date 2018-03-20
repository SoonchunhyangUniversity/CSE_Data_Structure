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

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언

/* 피보나치 수열을 계산할 함수 */
int fib(int n) // 매개변수로 int형 정수 n을 받는다.
{
	/* n이 2보다 작을 경우 */
	if (n < 2) // 0, 1 일때
		return n; // 0, 1을 반환
	else // n >= 2
	{
		int tmp, current = 1, last = 0;
		// 값을 임시로 저장할 변수 tmp
		// 하나 전의 값을 저장할 current, 두개 전의 값을 저장할 last
		// fib(6)일 경우 current > fib(5), last > fib(4)

		/* 피보나치 수열을 계산 */
		for (int i = 2; i <= n; i++) // n - 1 번 반복
		{
			tmp = current; // tmp에 current 값을 저장
			current += last; // current에 last값을 더함
			last = tmp; // last에 tmp에 저장해놓은 current 저장
		}
		return current; // current를 반환
	}
}

int main() // 메인함수 시작
{
	int input; // 입력값을 저장할 정수형 변수 input
	int arr[31] = { 0 }; // 피보나치 수열을 30까지 저장할 정수형 변수 arr

	/* 앞에서 선언한 함수를 이용하여 배열에 값을 대입 */
	for (int i = 1; i <= 30; i++) // 30번 반복
		arr[i] = fib(i); // arr의 i번째 idx에 fib(i)의 값을 대입

	printf("검색하고 싶은 피보나치 수열 순번을 입력하시오 : ");
	scanf("%d", &input); // input에 입력값을 받는다.

	/* input번째에 있는 피보나치 수열 데이터를 출력 */
	printf("%d번째 값은 %d입니다.\n\n", input, arr(input));

	/* 저장된 피보나치 수열을 모두 출력 */
	printf("피보나치 수열 : ");
	for (int i = 1; i <= 30; i++) // 30번 반복
		printf("%d ", arr[i]); // 배열에 저장된 값을 모두 출력

	printf("\n");

	return 0; // 메인함수 종료
}
