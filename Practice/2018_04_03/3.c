#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <time.h> // clock 함수를 사용하기 위한 헤더파일 선언

/* 재귀를 이용한 역수의 덧셈 함수 */
double resc_fun(int num);
/* 반복을 이용한 역수의 덧셈 함수 */
double loop_fun(int num);

int main() // 메인 함수의 시작
{
	int num, num_count = 0, temp;
	// 몇 번째 숫자까지 더할지를 저장할 변수, 데이터의 개수를 담을 변수, 임시로 값을 저장할 변수 선언
	clock_t start, finish;
	// clock_t형의 start, finish 변수 걸린 시간을 구하기 위한 변수
	double time_resc, time_loop;
	// 형변환에 의한 데이터 손실을 줄이기위하여 double형으로 변수를 선언

	FILE *fp = fopen("data.txt", "r");
	// 파일 포인터 fp 선언 및 fopen으로 data.txt를 쓰기 모드로 열기

	/* 파일이 존재하지 않을 경우 예외 처리 */
	if (fp == NULL)
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

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌란다.

	int i = 0; // while문 안에서 조건을 판단할 변수

	/* num_count번 반복하는 while문 */
	while (i != num_count)
	{
		fscanf(fp, "%d", &num); // num에 fp의 정수형 데이터를 저장

		start = clock(); // 재귀 함수 시작 시간 측정
		resc_fun(num); // 재귀 함수 사용
		finish = clock(); // 재귀 함수 종료 시간 측정

		/* 측정한 값으로 걸린 시간을 구한다 */
		time_resc = (double)(finish - start) / CLOCKS_PER_SEC;

		start = clock();
		loop_fun(num);
		finish = clock();

		time_loop = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("재귀함수 답[%d] : %lf 반복문 답[%d] : %lf\n", num, resc_fun(num), num, loop_fun(num));
		printf("재귀함수 걸린 시간[%d] : %lf 반복문 걸린 시간[%d] : %lf\n", num, time_resc, num, time_loop);
		i++;
	}

	fclose(fp);

	return 0;
}

double resc_fun(int num)
{
	if (num == 1)
		return 1.0 / num;
	else
		return 1.0 / num + resc_fun(num - 1);
}

double loop_fun(int num)
{
	double sum = 0;

	for (int i = 1; i <= num; i++)
	{
		sum += (double)1 / i;
	}

	return sum;
}
