/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연산자에 따른 시간복잡도 분석
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 12
	*
*/

#include <stdio.h>	// 표준 입출력 헤더파일 선언
#include <time.h>	// clock함수를 사용하기위한 헤더파일 선언

int main()
{
	char oper;
	// 연산자 OPERATOR를 받기위한 char형 변수
	unsigned int input;
	// 연산을 반복할 횟수를 받을 unsigned int형 변수 -> 테스트 횟수를 늘이기 위함
	double result;
	// 연산 결과를 저장하기 위한 변수, 나눗셈을 고려하여 double형 선언
	clock_t start, finish;
	// clock_t형 변수 start와 finish -> 시간 계산을 위함
	double time;
	//  시간을 계산해서 저장할 double형 변수

	FILE *fp = fopen("data.txt", "w");
	// 파일포인터 fp 선언 및 data.txt를 쓰기모드로 오픈

	/* 파일이 존재하지 않을 경우 예외처리 */
	if (fp == NULL)	// 파일이 없으면
	{
		printf("FILE OPEN ERROR!\n");	// 에러메세지 출력
		return 0;	// 함수 종료
	}

	/* 연산자와 반복횟수를 입력 받음 */
	scanf("%c", &oper);
	scanf("%d", &input);

	result = input;
	/*
	연산을 진행하기 위하여 result의 초기값을 input값으로 초기화
	별다른 의미 x
	*/

	start = clock();	// 알고리즘을 시작하기 전에 start에 시작 시간 저장

	/* scanf로 받은 연산자에 따라 계산을 하기 위한 switch문 */
	switch (oper)
	{
	case '+':	// oper == '+'
		for(int i = 0; i < input; i++)	// input번 만큼 반복한다
			result += i;	// result = result + i;
		break;
	case '-':	// oper == '-'
		for(int i = 0; i < input; i++)	// input번 만큼 반복한다
			result -= i;	// result = result - i;
		break;
	case '*':	// oper == '*'
		for (int i = 0; i < input; i++)	// input번 만큼 반복한다
			result *= i;	// result = result * i;
		break;
	case '/':	// oper == '/'
		for (int i = 0; i < input; i++)	// input번 만큼 반복한다
			result /= i;	// result = result / i;
		break;
	default:	// oper != '+' && oper != '-' && oper != '*' && oper != '/'
		printf("OPERATOR INPUT ERROR!\n");	// 에러메세지 출력
		break;
	}

	finish = clock();	// finish에 계산이 끝난 시간을 저장

	time = (double)(finish - start) / CLOCKS_PER_SEC;	// 걸린 시간을 계산

	/* data.txt에 값 저장 */
	fprintf(fp, "연산을 선택하시오 : %c\n", oper);
	fprintf(fp, "반복 횟수를 입력하세요 : %d\n\n", input);
	fprintf(fp, "걸린시간은 %f입니다.\n", time);

	fclose(fp);	// 파일 포인터 fp 닫기

	return 0;	// 메인 함수 종료
}
