#ifndef __BUBBLE__SORT__
#define __BUBBLE__SORT__

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include "Swap.h" // 사용자 정의 Swap헤더파일 선언

/**
 * [bubble_sort 함수]
 * @param arr [정렬할 배열]
 * @param n   [데이터의 개수]
 */
void bubble_sort(int arr[], int n)
{
	int i, j;
	// 반복문에서 사용할 변수 선언

	/* 배열의 개수만큼 반복 */
	for (i = n; i > 1; i--)
	{
		/* 정렬되지 않은 배열의 데이터 개수만큼 반복 */
		for (j = 1; j < i; j++)
		{
			/* j - 1번째 데이터가 j번째 데이터보다 크다면*/
			if (arr[j - 1] > arr[j])
				swap(&arr[j - 1], &arr[j]); // 데이터 교환
		}
	}
}

#endif
