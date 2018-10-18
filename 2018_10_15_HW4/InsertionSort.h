#ifndef __INSERTION__SORT__
#define __INSERTION__SORT__

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언

/**
 * [insertion_sort 함수]
 * @param arr [정렬할 배열]
 * @param n   [데이터의 개수]
 */
void insertion_sort(int arr[], int n)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int insData;
	// 삽입할 데이터를 저장할 변수 선언

	/* 배열의 두번째 데이터부터 끝까지 반복 */
	for (i = 1; i < n; i++)
	{
		insData = arr[i];
		// 정렬대상을 insData에 저장

		/* 정렬되지 않은 배열을 반복 */
		for (j = i - 1; j >= 0; j--)
		{
			/* 현재 탐색중인 데이터가 insData보다 클 경우 */
			if (arr[j] > insData)
				arr[j + 1] = arr[j]; // 비교대상 한 칸 뒤로 밀기

			/* 그렇지 않을 경우 */
			else
				break; // 삽입위치를 찾았으니 탈출
		}

		arr[j + 1] = insData; // 찾은 위치에 정렬대상 삽입;
	}
}

#endif
