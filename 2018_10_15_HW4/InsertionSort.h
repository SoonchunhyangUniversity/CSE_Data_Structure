#ifndef __INSERTION__SORT__
#define __INSERTION__SORT__

#include <stdio.h>

void insertion_sort(int arr[], int n)
{
	int i, j;
	int insData;

	for (i = 1; i < n; i++)
	{
		insData = arr[i];
		// 정렬대상을 insData에 저장

		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] > insData)
				arr[j + 1] = arr[j]; // 비교대상 한 칸 뒤로 밀기

			else
				break; // 삽입위치를 찾았으니 탈출
		}

		arr[j + 1] = insData; // 찾은 위치에 정렬대상 삽입;
	}
}

#endif