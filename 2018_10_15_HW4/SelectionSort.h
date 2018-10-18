#ifndef __SELECTION__SORT__
#define __SELECTION__SORT__

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include "Swap.h" // 사용자 정의 Swap헤더파일 선언

/**
 * [selection_sort 함수]
 * @param arr   [정수형 배열]
 * @param count [학생의 수]
 */
void selection_sort(int arr[], int count)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int minIdx;
	// 최솟값을 저장할 변수 선언
	int temp;
	// 데이터를 임시로 저장할 변수 선언

	/* 배열의 크기 - 2번 반복하는 반복문 */
	for (i = 0; i < count - 1; i++)
	{
		minIdx = i; // minIdx에 i값 대입

		/* 배열이 정렬 안된 부분 부터 끝까지 반복하는 반복문 */
		for (j = i + 1; j < count; j++)
		{
			/* 순위 값을 비교하는 조건문 */
			if (arr[j] < arr[minIdx])
				minIdx = j; // j의 순위가 minIdx보다 작으면 값 대입
		}

		/* 구조체 교환 */
		swap(&arr[i], &arr[minIdx]);
	}
}

#endif
