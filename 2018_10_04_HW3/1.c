/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 03 HW
 * 작성일 : 2018-10-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc 함수 사용을 위한 헤더파일 선언

/* 선택 정렬 함수 선언 */
void selection_sort(int arr[], int size);
/* 배열의 데이터를 출력하는 함수 선언 */
void display(int arr[], int size);
/* 배열의 데이터를 교환하는 함수 선언 */
void swap(int *a, int *b);

int main()
{
	int *arr;
	// 데이터의 개수에 따라 동적 할당 할 배열 선언
	int i;
	// 반복문에서 사용할 변수 선언
	int size = 0;
	// 데이터의 개수를 저장할 변수 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d", &i); // 임시로 i에 저장
		size++; // 데이터 개수 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 데이터의 개수에 맞추어 동적 할당 */
	arr = (int *)malloc(sizeof(int) * size);

	/* size만큼 반복하는 반복문 */
	for (i = 0; i < size; i++)
		fscanf(fp, "%d", &arr[i]);
		// fp에서 정수형 데이터를 읽어와 배열의 i번째에 저장

	printf("< Before Selection Sort >\n");
	display(arr, size); // 정렬 전 배열 출력
	printf("\n");

	selection_sort(arr, size); // 배열을 정렬

	printf("< After Selection Sort >\n");
	display(arr, size); // 정렬 후 배열 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	return 0; // 메인 함수 종료
}

/**
 * [selection_sort 함수]
 * @param arr  [정렬할 배열]
 * @param size [배열의 크기]
 */
void selection_sort(int arr[], int size)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int minIdx;
	// 최솟값을 가진 인덱스를 저장할 변수 선언

	/* size - 1번 반복하는 반복문 */
	for (i = 0; i < size - 1; i++)
	{
		minIdx = i; // minIdx에 i 대입

		/* 정렬되지 않은 데이터 개수만큼 반복 */
		for (j = i + 1; j < size; j++)
		{
			/* 배열의 j번째 데이터가 minIdx번째 데이터보다 작다면*/
			if (arr[j] < arr[minIdx])
				minIdx = j; // minIdx에 j 대입
		}

		swap(&arr[i], &arr[minIdx]);
		// i번째 데이터와 minIdx번째 데이터 교환
	}
}

/**
 * [display 함수]
 * @param arr  [배열]
 * @param size [배열 크기]
 */
void display(int arr[], int size)
{
	int i; // 반복문에서 사용할 변수 선언

		   /* 배열의 크기 만큼 반복 */
	for (i = 0; i < size; i++)
	{
		/* 첫번째 데이터일 경우 */
		if (i == 0)
			printf("┌────┬");

		/* 마지막 데이터일 경우 */
		else if (i == size - 1)
			printf("┬────┐\n");

		/* 나머지 경우 */
		else
			printf("┬────┬");
	}

	/* 배열의 크기 만큼 반복 */
	for (i = 0; i < size; i++)
	{
		/* 마지막 데이터일 경우 */
		if (i == size - 1)
			printf("│ %2d │\n", arr[i]);

		/* 나머지 경우 */
		else
			printf("│ %2d │", arr[i]);
	}

	/* 배열의 크기 만큼 반복 */
	for (i = 0; i < size; i++)
	{
		/* 첫번째 데이터일 경우 */
		if (i == 0)
			printf("└────┴");

		/* 마지막 데이터일 경우 */
		else if (i == size - 1)
			printf("┴────┘\n");

		/* 나머지 경우 */
		else
			printf("┴────┴");
	}
}

/**
 * [swap 함수]
 * @param a [배열의 인덱스 주소]
 * @param b [배열의 인덱스 주소]
 */
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
