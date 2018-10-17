#ifndef __SHELL__SORT__
#define __SHELL__SORT__

#include <stdio.h>

/**
 * [insertion_sort_at_shell_sort �Լ�]
 * @param std   [�л� ����ü �迭]
 * @param first [���� ���� �ε���]
 * @param last  [���� �� �ε���]
 * @param gap   [�� ����� �ε��� ����]
 */
void insertion_sort_at_shell_sort(int arr[], int first, int last, int gap)
{
	int i, j;
	// �ݺ������� ����� ���� ����
	int key;
	// �迭�� �����͸� �ӽ÷� ������ ���� ����

	for (i = first + gap; i <= last; i = i + gap)
	{
		key = arr[i]; // key�� arr[i] ����

		/* i - gap���� �������� �۾����� �ݺ���  j ���� first����
		   ũ�ų� ���� key ������ ���ĵ� �迭�� �ִ� ���� ������
		   j��°�� j+gap������ �̵� */
		for (j = i - gap; j >= first && key < arr[j]; j = j - gap)
			arr[j + gap] = arr[j]; // gap��ŭ ���������� �̵�

		arr[j + gap] = key; // j + gap��° �迭�� temp ����
	}
}

/**
 * [shell_sort �Լ�]
 * @param std [�л� �迭 ����ü]
 * @param n   [�������� ����]
 */
void shell_sort(int arr[], int n)
{
	int i, gap;
	// �ݺ������� ����� ���� ����

	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		/* gap�� ¦���� ��� */
		if (gap % 2 == 0)
			gap++; // gap�� Ȧ���� �����.

		/* gap��ŭ �ݺ��ϴ� �ݺ��� */
		for (i = 0; i < gap; i++)
			insertion_sort_at_shell_sort(arr, i, n - 1, gap);
			// �κ� ����Ʈ�� ���� ���� ���� ����
	}
}

#endif