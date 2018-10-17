#ifndef __SHELL__SORT__
#define __SHELL__SORT__

#include <stdio.h>

/**
 * [insertion_sort_at_shell_sort 함수]
 * @param std   [학생 구조체 배열]
 * @param first [정렬 시작 인덱스]
 * @param last  [정렬 끝 인덱스]
 * @param gap   [두 요소의 인덱스 차이]
 */
void insertion_sort_at_shell_sort(int arr[], int first, int last, int gap)
{
	int i, j;
	// 반복문에서 사용할 변수 설명
	int key;
	// 배열의 데이터를 임시로 저장할 변수 선언

	for (i = first + gap; i <= last; i = i + gap)
	{
		key = arr[i]; // key에 arr[i] 대입

		/* i - gap부터 역순으로 작아지는 반복문  j 값은 first보다
		   크거나 같고 key 값보다 정렬된 배열에 있는 값이 작으면
		   j번째 데이터를 j+gap번째로 이동 */
		for (j = i - gap; j >= first && key < arr[j]; j = j - gap)
			arr[j + gap] = arr[j]; // gap만큼 오른쪽으로 이동

		arr[j + gap] = key; // j + gap번째 데이터에 temp 저장
	}
}

/**
 * [shell_sort 함수]
 * @param std [학생 배열 구조체]
 * @param n   [데이터의 개수]
 */
void shell_sort(int arr[], int n)
{
	int i, gap;
	// 반복문에서 사용할 변수 선언

	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		/* gap이 짝수인 경우 */
		if (gap % 2 == 0)
			gap++; // gap을 홀수로 만든다.

		/* gap만큼 반복하는 반복문 */
		for (i = 0; i < gap; i++)
			insertion_sort_at_shell_sort(arr, i, n - 1, gap);
			// 부분 리스트에 대한 삽입 정렬 진행
	}
}

#endif
