#ifndef __QUICK__SORT__
#define __QUICK__SORT__

#include "Swap.h"

/**
 * [partition 함수]
 * @param  arr   [정수형 배열]
 * @param  left  [베열의 맨 왼쪽 인덱스]
 * @param  right [배열의 맨 오른쪽 인덱스]
 * @return       [부분의 맨 오른쪽 인덱스]
 */
int partition(int arr[], int left, int right)
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

		/* low가 high 보다 클경우 실행 */
		if (low < high)
			swap(&arr[low], &arr[high]);
		// low번째 인덱스와 high번째 인덱스의 데이터 교환

	} while (low < high);

	swap(&arr[left], &arr[high]);
	// left번째 데이터와 high번째 데이터 교환

	return high; // 맨 오른쪽 인덱스 반환
}

/**
 * [quick_sort 함수]
 * @param arr   [정수형 배열]
 * @param left  [정렬할 배열의 맨 왼쪽 인덱스]
 * @param right [정렬할 배열의 맨 오른쪽 인덱스]
 */
void quick_sort(int arr[], int left, int right)
{
	/* right가 left보다 크면 실행 */
	if (left <= right)
	{
		int pivot = partition(arr, left, right);
		// 둘로 나눠서
		quick_sort(arr, left, pivot - 1);
		// 왼쪽 영역을 정렬
		quick_sort(arr, pivot + 1, right);
		// 오른쪽 영역을 정렬
	}
}

#endif