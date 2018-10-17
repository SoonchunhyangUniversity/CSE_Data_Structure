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

		/* high가 left보다 작거나 배열