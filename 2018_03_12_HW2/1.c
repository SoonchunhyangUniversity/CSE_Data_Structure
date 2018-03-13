/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 알고리즘에 따른 시간복잡도 분석
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 12
	*
*/

#include <stdio.h>	// 표준 입출력 헤더파일 선언
#include <time.h>	// clock함수 사용을 위한 헤더파일 선언

int main()
{
	int num, result;
	// num -> 연산 알고리즘(1, 2, 3)중에서 선택, result -> 계산한 값을 저장하기 위한 변수
	unsigned int input;
	// unsigned형으로 input의 양의 범위 증가 -> 더 많은 양의 테스트 진행
	clock_t start, finish;
	// clock_t형의 start, finish 변수 걸린 시간을 구하기 위한 변수
	double time;
	// 형변환에 의한 데이터 손실을 줄이기위하여 double형으로 변수를 선언

	FILE *fp = fopen("data.txt", "w");
	// 파일 포인터 fp 선언 및 fopen으로 data.txt를 쓰기 모드로 열기

	/* 파일이 존재하지 않을 경우 예외 처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;	// 메인함수 종료
	}

	/* 몇 번쨰 알고리즘을 적용할 것인가에 대한 변수와 반복횟수 입력 */
	scanf("%d", &num);
	scanf("%d", &input);

	start = clock();	// 알고리즘을 시작하기 전에 start에 시작 시간 저장

	/* 입력받은 num에 따라 1, 2, 3의 알고리즘을 실행하기 위한 switch문 */
	switch (num)
	{
	case 1:	// num == 1
		result = input * input;	// O(1)
		break;
	case 2:	// num == 2
		result = 0;	// result 값의 초기화
		for (int i = 0; i < input; i++)
			result = result + input;	// O(n)
		break;
	case 3:	// num == 3
		result = 0;	// result 값의 초기화
		for (int i = 0; i < input; i++)
			for (int j = 0; j < input; j++)
				result = result + 1;	//O(n²)
		break;
	default: // num != 1 && num != 2 && num != 3
		printf("NUM INPUT ERROR!\n");	// 에러메세지 출력
		break;
	}

	finish = clock();	// 계산이 끝난후 finish에 종료 시간 저장

	time = (double)(finish - start) / CLOCKS_PER_SEC;
	// 저장된 값을 이용하여 걸린 시간 계산

	/* 파일에 데이터 넣어주기 */
	fprintf(fp, "알고리즘을 선택하세요<1, 2, 3> : %d\n", num);
	fprintf(fp, "숫자를 입력하시오 : %d\n\n", input);
	fprintf(fp, "걸린시간은 %f입니다.\n", time);

	fclose(fp);	// 파일 포인터 fp 닫기

	return 0;	// 메인 함수 종료
}
