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

		/* high�� left���� �۰ų� �迭