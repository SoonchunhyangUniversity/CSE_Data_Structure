#ifndef __QUICK__SORT__
#define __QUICK__SORT__

#include "Swap.h"

/**
 * [partition �Լ�]
 * @param  arr   [������ �迭]
 * @param  left  [������ �� ���� �ε���]
 * @param  right [�迭�� �� ������ �ε���]
 * @return       [�κ��� �� ������ �ε���]
 */
int partition(int arr[], int left, int right)
{
	int pivot;
	// �Ǻ� ���� ����
	int low = left, high = right + 1;
	// �κ� ���� ���� �� �ʱ�ȭ
	int now = 0;
	// ������ �Ǻ��� ������ ���� ���� �� �ʱ�ȭ
	pivot = arr[left];
	// �Ǻ��� ���� �迭�� �� ���� �ε��� ����

	/* high�� low���� ������ �����ϴ� while�� */
	do
	{
		/* low�� right���� ũ�ų� �迭�� low��°
		�ε��� ���� �Ǻ��� ���� ũ�� Ż���ϴ� �ݺ��� */
		do
			low++; // low 1 ����
		while (low <= right && arr[low] < pivot);

		/* high�� left���� �۰ų� �迭�l high��°
		�ε��� ���� �Ǻ����� ������ Ż���ϴ� �ݺ��� */
		do
			high--;
		while (high >= left && arr[high] > pivot);

		/* low�� high ���� Ŭ��� ���� */
		if (low < high)
			swap(&arr[low], &arr[high]);
		// low��° �ε����� high��° �ε����� ������ ��ȯ

	} while (low < high);

	swap(&arr[left], &arr[high]);
	// left��° �����Ϳ� high��° ������ ��ȯ

	return high; // �� ������ �ε��� ��ȯ
}

/**
 * [quick_sort �Լ�]
 * @param arr   [������ �迭]
 * @param left  [������ �迭�� �� ���� �ε���]
 * @param right [������ �迭�� �� ������ �ε���]
 */
void quick_sort(int arr[], int left, int right)
{
	/* right�� left���� ũ�� ���� */
	if (left <= right)
	{
		int pivot = partition(arr, left, right);
		// �ѷ� ������
		quick_sort(arr, left, pivot - 1);
		// ���� ������ ����
		quick_sort(arr, pivot + 1, right);
		// ������ ������ ����
	}
}

#endif