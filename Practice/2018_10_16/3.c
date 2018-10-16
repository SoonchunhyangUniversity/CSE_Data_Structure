/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 퀵 정렬 프로그램
 * 작성일 : 2018-10-16
 */

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언

/* 배열의 데이터를 교환하는 함수 */
void Swap(int *a, int *b);
/* 배열을 퀵 정렬하는 함수 */
void QuickSort(int arr[], int left, int right);
/* 배열의 데이터를 출력하는 함수 */
void Display(int arr[], int start, int count);
/* 퀵 정렬에서 부분을 나누는 함수 */
int Partition(int arr[], int left, int right);

int main()
{
	int *arr = NULL;
	// 정수형 배열을 동적 할당할 포인터 변수 선언 및 초기화
	int count = 0;
	// 학생의 수를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	/* 파일 포인터 fp선언 및 data3.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일읠 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 퍼일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		// 파일에서 데이터를 읽어와 임시로 저장
		count++;
		// 데이터의 개수를 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 데이터의 개수만큼 배열 동적 할당 */
	arr = (int *)malloc(sizeof(int) * count);

	/* 데이터의 개수 만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &arr[i]);
		// 파일에서 데이터를 읽어와 배열에 저장

	printf("< 정렬되지 않은 리스트 >\n");
	Display(arr, 0, count); // Display 함수로 배열의 데이터 출력
	printf("\n");

	printf("\n< 정렬 과정 >\n");
	QuickSort(arr, 0, count - 1); // QuickSort 함수 호출하여 퀵 정렬

	printf("\n< 정렬된 리스트 >\n");
	Display(arr, 0, count); // Display 함수로 배열의 데이터 출력
	printf("\n");

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.
	free(arr); // 동적 할당한 배열의 메모리 할당 해제

	return 0; // 메인 함수 종료
}

/**
 * [Swap 함수]
 * @param a [배열의 데이터 주소값]
 * @param b [배열의 데이터 주소값]
 */
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * [QuickSort 함수]
 * @param arr   [정수형 배열]
 * @param left  [정렬할 배열의 맨 왼쪽 인덱스]
 * @param right [정렬할 배열의 맨 오른쪽 인덱스]
 */
void QuickSort(int arr[], int left, int right)
{
	/* right가 left보다 크면 실행 */
	if (left <= right)
	{
		int pivot = Partition(arr, left, right);
		// 둘로 나눠서
		QuickSort(arr, left, pivot - 1);
		// 왼쪽 영역을 정렬
		QuickSort(arr, pivot + 1, right);
		// 오른쪽 영역을 정렬
	}
}

/**
 * [Display 함수]
 * @param arr   [정수형 배열]
 * @param start [출력 시작 인덱스]
 * @param count [배열의 데이터 개수]
 */
void Display(int arr[], int start, int count)
{
	int i; // 반복문에서 사용할 변수 선언

	/* 배열의 데이터 개수 만큼 반복하는 반복문 */
	for (i = start; i < count; i++)
	{
		/* 마지막 데이터일 경우 */
		if (i == count - 1)
			printf("%2d", arr[i]);

		/* 그렇지 않을 경우 */
		else
			printf("%2d > ", arr[i]);
	}
}

/**
 * [Partition 함수]
 * @param  arr   [정수형 배열]
 * @param  left  [베열의 맨 왼쪽 인덱스]
 * @param  right [배열의 맨 오른쪽 인덱스]
 * @return       [부분의 맨 오른쪽 인덱스]
 */
int Partition(int arr[], int left, int right)
{
	int pivot;
	// 피봇 변수 선언
	int low = left, high = right + 1;
	// 부분 변수 선언 및 초기화
	int now = 0;
	// 현재의 피봇을 저장할 변수 선언 및 초기화
	pivot = arr[left];
	// 피봇에 현재 배열의 맨 왼쪽 인덱스 지정

	/* high가 low보다 작으면 종료하는 while문 */
	do
	{
		/* low가 right보다 크거나 배열의 low번째
		인덱스 값이 피봇값 보다 크면 탈출하는 반복문 */
		do
			low++; // low 1 증가
		while (low <= right && arr[low] < pivot);

		/* high가 left보다 작거나 배열릐 high번째
		인덱스 값이 피봇보다 작으면 탈출하는 반복문 */
		do
			high--;
		while (high >= left && arr[high] > pivot);

		/* 피봇의 값이 배열의 맨 오른쪽 데이터가 아닐 경우 실행 */
		if (pivot != arr[high])
		{
			/* now가 피봇값이 아닐 경우 실행 */
			if (now != pivot)
			{
				printf("- Pivot : %d -\n", pivot); // 피봇 데이터 출력
				now = pivot; // now에 피봇값 대입
			}

			printf("low : %d high : %d  [", arr[low], arr[high]);
			// low와 high번째 인덱스의 데이터 출력
			Display(arr, left, right + 1);
			// Display 함수 호출하여 배열의 left부터 right번째 까지의 데이터 출력
			printf("]\n\n");
		}

		/* low가 high 보다 클경우 실행 */
		if (low < high)
			Swap(&arr[low], &arr[high]);
			// low번째 인덱스와 high번째 인덱스의 데이터 교환

	} while (low < high);

	Swap(&arr[left], &arr[high]);
	// left번째 데이터와 high번째 데이터 교환

	return high; // 맨 오른쪽 인덱스 반환
}
