#ifndef __SELECTION__SORT__
#define __SELECTION__SORT__

#include <stdio.h>
#include "Swap.h"

/**
 * [selection_sort �Լ�]
 * @param arr   [������ �迭]
 * @param count [�л��� ��]
 */
void selection_sort(int arr[], int count)
{
	int i, j;
	// �ݺ������� ����� ���� ����
	int minIdx;
	// �ּڰ��� ������ ���� ����
	int temp;
	// �����͸� �ӽ÷� ������ ���� ����

	/* �迭�� ũ�� - 2�� �ݺ��ϴ� �ݺ��� */
	for (i = 0; i < count - 1; i++)
	{
		minIdx = i; // minIdx�� i�� ����

		/* �迭�� ���� �ȵ� �κ� ���� ������ �ݺ��ϴ� �ݺ��� */
		for (j = i + 1; j < count; j++)
		{
			/* ���� ���� ���ϴ� ���ǹ� */
			if (arr[j] < arr[minIdx])
				minIdx = j; // j�� ������ minIdx���� ������ �� ����
		}

		/* ����ü ��ȯ */
		swap(&arr[i], &arr[minIdx]);
	}
}

#endif