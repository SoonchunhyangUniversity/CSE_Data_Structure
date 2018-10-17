#ifndef __MERGE__SORT__
#define __MERGE__SORT__

#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	int *sortArr = (int *)malloc(sizeof(int) * (right + 1));
	int sIdx = left;

	while (fIdx <= mid && rIdx <= right)
	{
		if (arr[fIdx] <= arr[rIdx])
			sortArr[sIdx] = arr[fIdx++];

		else
			sortArr[sIdx] = arr[rIdx++];

		sIdx++;
	}

	if (fIdx > mid)
	{
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	else
	{
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	for (i = left; i <= right; i++)
		arr[i] = sortArr[i];

	free(sortArr);
}

void merge_sort(int arr[], int left, int right)
{
	int mid;

	if (left < right)
	{
		/* �߰� ������ ����Ѵ� */
		mid = (left + right) / 2;

		/* �ѷ� ������ ������ �����Ѵ� */
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		/* ���ĵ� �� �迭�� �����Ѵ� */
		merge(arr, left, mid, right);
	}
}

#endif
