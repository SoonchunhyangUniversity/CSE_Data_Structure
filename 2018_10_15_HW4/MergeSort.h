﻿#ifndef __MERGE__SORT__
#define __MERGE__SORT__

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언

/**
 * [merge 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 인덱스]
 * @param mid   [배열의 가운데 인덱스]
 * @param right [배열의 가장 오른쪽 인덱스]
 */
void merge(int arr[], int left, int mid, int right)
{
	int fIdx = left;
	// 왼쪽 배열의 시작 인덱스를 저장할 변수 선언 및 초기화
	int rIdx = mid + 1;
	// 오른쪽 배열의 시작 인덱스를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	int *sortArr = (int *)malloc(sizeof(int) * (right + 1));
	// 정렬된 배열을 저장할 배열 동작 할당
	int sIdx = left;

	/* left부터 mid까지의 블록과 mid + 1부터
	   right까지의 블록을 비교하는 부분 */
	while (fIdx <= mid && rIdx <= right)
	{
		/* left의 데이터가 right값보다 작을 경우 */
		if (arr[fIdx] <= arr[rIdx])
			sortArr[sIdx] = arr[fIdx++];
			// left의 데이터를 결과 배열에 복사

		/* 그렇지 않을 경우 */
		else
			sortArr[sIdx] = arr[rIdx++];
			// right의 데이터를 결과 배열에 복사

		sIdx++; // 결과 배열의 인덱스 증가
	}

	/* 오른쪽 배열의 데이터가 남아있는 경우 */
	if (fIdx > mid)
	{
		/* 오른쪽 배열의 남은 데이터 만큼 반복 */
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
			// 오른쪽 배열의 데이터를 결과 배열에 복사
	}

	/* 왼쪽 배열의 데이터가 남아있는 경우 */
	else
	{
		/* 왼쪽 배열의 남은 데이터 만큼 반복 */
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
			// 왼쪽 배열의 데이터를 결과 배열에 복사
	}

	/* 배열의 데이터 개수만큼 반복 */
	for (i = left; i <= right; i++)
		arr[i] = sortArr[i]; // 원본 배열에 복사

	free(sortArr); // 배열 메모리 할당 해제
}

/**
 * [merge_sort 함수]
 * @param arr   [정렬할 배열]
 * @param left  [배열의 가장 왼쪽 인덱스]
 * @param right [배열의 가장 오른쪽 인덱스]
 */
void merge_sort(int arr[], int left, int right)
{
	int mid;
	// 중간 지점 인덱스를 저장할 변수 선언

	/* left가 right보다 작으면 실행 */
	if (left < right)
	{
		/* 중간 지점을 계산한다 */
		mid = (left + right) / 2;

		/* 둘로 나눠서 각각을 정렬한다 */
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		/* 정렬된 두 배열을 병합한다 */
		merge(arr, left, mid, right);
	}
}

#endif
