/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 재귀함수를 이용한 데이터 처리1
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 03
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <time.h> // clock 함수를 사용하기 위한 헤더파일 선언

/* 재귀를 이용한 덧셈 함수 */
int resc_fun(int num);
/* 반복을 이용한 덧셈 함수 */
int loop_fun(int num);

int main() // 메인 함수의 시작
{
	int num, temp, num_count = 0;
    // 몇 번째 숫짜까지 더할지를 저장할 변수, 값을 임시로 담을 변수, 데이터의 개수를 저장할 변수 선언
	clock_t start, finish;
	// clock_t형의 start, finish 변수 걸린 시간을 구하기 위한 변수
	double time_resc, time_loop;
	// 형변환에 의한 데이터 손실을 줄이기위하여 double형으로 변수를 선언

	FILE *fp = fopen("data.txt", "r");
	// 파일 포인터 fp 선언 및 fopen으로 data.txt를 쓰기 모드로 열기

	/* 파일이 존재하지 않을 경우 예외 처리 */
	if (fp == NULL) // 파일을 열 수 없으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0;	// 메인함수 종료
	}

    /* 파일의 끝까지 반복한다 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp); // 임시로 값을 저장한다.
		num_count++; // 파일안의 데이터의 개수를 저장한다.
	}

	rewind(fp); // 파일포인터의 위치를 처음으로 돌린다.

	int i = 0; // while문 안에서 조건을 판단할 변수

    /* num_count번 반복하는 while문 */
	while (i != num_count)
	{
		fscanf(fp, "%d", &num); // num에 파일의 정수 데이터를 저장

		start = clock(); // 재귀 함수 시작 시간 측정
		resc_fun(num); // 재귀 함수 사용
		finish = clock(); // 재귀 함수 종료 시간 측정

        /* 측정한 값으로 걸린 시간을 구한다 */
		time_resc = (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock(); // 반복 함수 시작 시간 측정
		loop_fun(num); // 반복 함수 사용
		finish = clock(); // 반복 함수 종료 시간 측정

        /* 측정한 값으로 걸린 시간을 구한다 */
		time_loop = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("재귀함수 답[%d] : %d 반복문 답[%d] : %d\n", num, resc_fun(num), num, loop_fun(num)); // num을 사용한 값을 출력한다.
		printf("재귀함수 걸린 시간[%d] : %lf 반복문 걸린 시간[%d] : %lf\n", num, time_resc, num, time_loop); // 걸린 시간을 출력한다.
		i++; // i를 1 더해준다 -> 반복 탈출 조건
	}

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
/* 재귀를 이용한 덧셈 함수 */
int resc_fun(int num) // 매개변수로 정수형 변수 num을 받는다
{
	if (num == 1) // num이 1이면
		return 1; // 1을 반환
    else // num != 1
	   return num + resc_fun(num - 1); // 재귀적으로 값을 더한다.
}
/* 반복 이용한 덧셈 함수 */
int loop_fun(int num) // 매개변수로 정수형 변수 num을 받는다.
{
	int sum = 0; // 더한 값을 저장할 변수 선언 및 0으로 초기화

	for (int i = 1; i <= num; i++) // num번 반복한다.
	{
		sum += i; // 1, 2, 3 ... num 까지 sum에 더해준다.
	}

	return sum; // 더한값을 저장한 sum을 반환한다.
}
