#ifndef __HEAP__SORT__
#define __HEAP__SORT__

#include <stdio.h> // ǥ������� ���̺귯�� ������� ����
#define MAX 200 // ��ȣ��� MAX�� 200���� ����

typedef int element;

 /* ���� ����ü */
typedef struct
{
	element heap[MAX]; // MAX�������� element ����ü �迭 �ʵ�
	int heap_size; // ������ ũ�⸦ �����ϴ� ���� �ʼ�
} HeapType; // HeapType Ű���� ���� ����

/**
 * [insert_max_heap �Լ�]
 * @param h    [�� ����ü]
 * @param item [���Ե� ������]
 */
void insert_max_heap(HeapType *h, element item)
{
	int i;
	// �ݺ����� ���� ���� ����
	i = ++(h->heap_size);
	// i ������ h�� heap_size�� 1���Ѱ� ����

	/* i�� 1�̵ǰų� item�� key���� ������� �ݺ��� Ż�� */
	while ((i != 1) && (item > h->heap[i / 2]))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
		// i�� 2�� �����鼭 ���� ������� �̵�
	}

	h->heap[i] = item; // ���� i��° �迭�� item ������ ����
}

/**
 * [init �Լ�]
 * @param h [�� ����ü]
 */
void init(HeapType *h)
{
	h->heap_size = 0; // ���� ����� 0���� �ʱ�ȭ
}

/**
 * [delete_max_heap �Լ�]
 * @param  h [�� ����ü]
 * @return   [���� �ִ�]
 */
element delete_max_heap(HeapType *h)
{
	int parent, child;
	// ���� �θ���� �ڽĳ�� �ε��� ���� ����
	element item, temp;
	// ������ �����͸� ������ ������ �ӽ÷� �����͸� ������ ���� ����

	item = h->heap[1];
	// ������ �����Ϳ� ���� �ִ� item�� ����
	temp = h->heap[(h->heap_size)--];
	// ���� ���� ���� ������ temp�� ����
	parent = 1, child = 2;
	// �θ�, �ڽĳ�� �ε����� �ʱ�ȭ

	/* �ڽĳ�� �ε����� ���� ������� ũ�� Ż���ϴ� �ݺ��� */
	while (child <= h->heap_size)
	{
		/* child�� �ε����� �� ������� �۰�
		   ������ �ڽ� ����� Ű���� Ŭ ���*/
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++; // child �� 1 ����

		/* temp�� key���� �ڽĳ���� Ű������ ũ�ų� ���� ��� */
		if (temp >= h->heap[child])
			break; // �ݺ��� Ż��

		h->heap[parent] = h->heap[child];
		// �θ��忡 �ڽĳ�� ����
		parent = child;
		// �ڽĳ���� �ε����� �θ��忡 ����
		child *= 2;
		// �ڽĳ�带 2 �����ش�.
	}

	h->heap[parent] = temp;
	// �ݺ��� ���� �θ��忡 temp ����

	return item; // ������ ������ ��ȯ
}

void heap_sort(int arr[], int n)
{
	int i;
	HeapType h;

	init(&h);

	for (i = 0; i < n; i++)
		insert_max_heap(&h, arr[i]);

	for (i = (n - 1); i >= 0; i--)
		arr[i] = delete_max_heap(&h);

}

#endif