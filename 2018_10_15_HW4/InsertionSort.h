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
		// ���Ĵ���� insData�� ����

		for (j = i - 1; j >= 0; j--)
		{
			if (arr[j] > insData)
				arr[j + 1] = arr[j]; // �񱳴�� �� ĭ �ڷ� �б�

			else
				break; // ������ġ�� ã������ Ż��
		}

		arr[j + 1] = insData; // ã�� ��ġ�� ���Ĵ�� ����;
	}
}

#endif