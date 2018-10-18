#ifndef __BUBBLE__SORT__
#define __BUBBLE__SORT__

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include "Swap.h" // 사용자 정의 Swap헤더파일 선언

void bubble_sort(int arr[], int n)
{
	int i, j;
	int temp;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < (n - i) - 1; j++)
		{
			if (arr[j] > arr[j + 1])
				swap(&arr[j + 1], &arr[j]);
		}
	}
}

#endif
