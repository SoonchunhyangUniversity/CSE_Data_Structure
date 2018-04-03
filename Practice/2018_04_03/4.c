/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 재귀함수를 이용한 데이터 처리
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 03
	*
*/

#include <stdio.h>
#include <time.h>

double resc_fun(double num, int degree);
int loop_fun(int num, int degree);

int main()
{
	int num, degree, temp, count = 0;
	clock_t start, finish;
	// clock_t형의 start, finish 변수 걸린 시간을 구하기 위한 변수
	double time_resc, time_loop;
	// 형변환에 의한 데이터 손실을 줄이기위하여 double형으로 변수를 선언

	FILE *fp = fopen("data.txt", "r");
	// 파일 포인터 fp 선언 및 fopen으로 data.txt를 쓰기 모드로 열기

	/* 파일이 존재하지 않을 경우 예외 처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;	// 메인함수 종료
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %d", &temp, &temp);
		count++;
	}

	rewind(fp);

	int i = 0;

	while (i != count)
	{
		fscanf(fp, "%d %d", &num, &degree);

		start = clock();
		resc_fun((double)num, degree);
		finish = clock();

		time_resc = (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		loop_fun(num, degree);
		finish = clock();

		time_loop = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("재귀함수 답[%d, %d] : %.0lf 반복문 답[%d, %d] : %d\n", num, degree, resc_fun((double)num, degree), num, degree, loop_fun(num, degree));
		printf("재귀함수 걸린 시간 : %lf 반복문 걸린 시간 : %lf\n", time_resc, time_loop);
		i++;
	}

	fclose(fp);

	return 0;
}

double resc_fun(double num, int degree)
{
	if (degree == 0)
		return 1;
	else if (degree % 2 == 0)
		return resc_fun(num * num, degree / 2);
	else
		return num * resc_fun(num * num, (degree - 1) / 2);
}

int loop_fun(int num, int degree)
{
	int result = 1;

	for (int i = 0; i < degree; i++)
		result *= num;

	return result;
}
