#include <stdio.h>
#include <time.h>

double resc_fun(int num);
double loop_fun(int num);

int main()
{
	int num, num_count = 0, temp;
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
		fscanf(fp, "%d", &temp);
		num_count++;
	}

	rewind(fp);

	int i = 0;

	while (i != num_count)
	{
		fscanf(fp, "%d", &num);

		start = clock();
		resc_fun(num);
		finish = clock();

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
