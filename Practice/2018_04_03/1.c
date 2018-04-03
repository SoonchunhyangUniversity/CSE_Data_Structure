#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <math.h> // sqrt() 함수를 사용하기 위한 헤더파일 선언

/* 산술 평균을 구하기 위한 함수 */
double Get_arit_mean(int arr[], int input_size);
/* 기하 평균을 구하기 위한 함수 */
double Get_geom_mean(int arr[], int input_size);
/* 조화 평균을 구하기 위한 함수 */
double Get_harm_mean(int arr[], int input_size);

int i = 0; // 반복문에서 사용할 변수를 전역 변수 사용

int main() // 메인 함수 시작
{
	int *arr; // 데이터를 저장할 배열
	int temp; // 임시로 값을 저장할 변수
	int input_size = 0; // 데이터의 개수
	double arit_mean = 0; // 산술 평균
	double geom_mean = 0; // 기하 평균
	double harm_mean = 0; // 조화 평균

    /* 파일 포인터 fp 선언및 data.txt를 읽기 모드로 연다 */
	FILE *fp = fopen("data.txt", "r");

    /* 파일이 없을 경우 예외 처리 */
	if (fp == NULL) // 파일을 열 수 없으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

    /* 파일의 끝까지 반복된다 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp); // 데이터의 개수를 파악하기 위함
		input_size++; // 데이터의 개수를 1개씩 더해준다
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다

	arr = (int *)malloc(sizeof(int) * input_size); // 데이터의 개수를 바탕으로 동적할당

    /* input_size 번 반복되는 반복문 배열에 값을 저장 */
	for (i = 0; i < input_size; i++)
	{
		fscanf(fp, "%d", &arr[i]); // arr에 순차적으로 값을 넣는다
	}

    /* 함수를 사용해 산술, 기하, 조화 평균의 값을 출력한다 */
	printf("산술 평균 : %0.2lf\n", Get_arit_mean(arr, input_size));
	printf("기하 평균 : %0.2lf\n", Get_geom_mean(arr, input_size));
	printf("조화 평균 : %0.2lf\n", Get_harm_mean(arr, input_size));

    free(arr); // 동적할당한 메모리를 해제한다.
	fclose(fp); // 열어준 파일포인터 fp를 닫는다.

    return 0; // 메인함수 종료
}
/* 산술 평균을 구하기 위한 함수 */
double Get_arit_mean(int arr[], int input_size)
{
	int sum = 0;

	for (i = 0; i < input_size; i++)
		sum += arr[i];

	return (double)sum / input_size;
}
/* 기하 평균을 구하기 위한 함수 */
double Get_geom_mean(int arr[], int input_size)
{
	int mul_sum = 0;

	for (i = 0; i < input_size; i++)
		mul_sum += (arr[i] * arr[i]);

	return (double)sqrt(mul_sum);
}
/* 조화 평균을 구하기 위한 함수 */
double Get_harm_mean(int arr[], int input_size)
{
	double rev_sum = 0;

	for (i = 0; i < input_size; i++)
		rev_sum += 1 / arr[i];

	return (double)input_size * rev_sum;
}
