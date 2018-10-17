#ifndef __RADIX__SORT__
#define __RADIX__SORT__

#include <stdio.h> // ǥ�� ����� ������� ����
#include <stdlib.h> // malloc, free �Լ� ����� ���� ������� ����
#define BUCKET_NUM 10 // ��ȣ ��� BUCKET_NUM�� 10���� ����

typedef int Data; // int�� ������ DataŰ����� ���� ����

/* ���� ����Ʈ ��� ť�� ��� ����ü */
typedef struct _node
{
	Data data; // ������ ������ �ʵ�
	struct _node * next; // ���� ��带 ����Ű�� ����ü ������
} Node; // typedef �������� Node Ű����� ���� ����

/* ť ����ü */
typedef struct _lQueue
{
	Node * front; // �� �� ��带 ����Ű�� ������ ����ü
	Node * rear; // �� �� ��带 ����Ű�� ������ ����ü
} Queue; // typedef �������� Queue Ű����� ���� ����

/**
 * [queue_init �Լ�]
 * @param pq [ť ����ü]
 */
void queue_init(Queue *pq)
{
	pq->front = NULL; // ť�� front ������ NULL�� �ʱ�ȭ
	pq->rear = NULL; // ť�� rear ������ NULL�� �ʱ�ȭ
}

/**
 * [enqueue �Լ�]
 * @param pq   [ť ����ü]
 * @param data [���Ե� ������]
 */
void enqueue(Queue *pq, Data data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	// ���Ե� ��� ���� �Ҵ�
	newNode->next = NULL;
	// �� ����� ��ũ�� NULL�� �ʱ�ȭ
	newNode->data = data;
	// �� ����� ������ �ʵ忡 data ����

	/* ť�� ����ִ��� Ȯ�� */
	if (is_empty(pq)) // ����ִ� ���
	{
		pq->front = newNode;
		// ť�� front�� �� ��� ����
		pq->rear = newNode;
		// ť�� rear�� �� ��� ����
	}

	else // ������� ���� ���
	{
		pq->rear->next = newNode;
		// rear�� ���� ��带 newNode ����
		pq->rear = newNode;
		// rear�� newNode�� ����
	}
}

/**
 * [is_empty �Լ�]
 * @param  pq [ť ����ü]
 * @return    [ť ���� ����]
 */
int is_empty(Queue *pq)
{
	return pq->front == NULL;
	// ť�� front�� NULL�� ��� TRUE
	// NULL�� �ƴ� ��� FALSE
}

/**
 * [dequeue �Լ�]
 * @param  pq [ť ����ü]
 * @return    [������ ������]
 */
Data dequeue(Queue *pq)
{
	Node *delNode;
	// ������ ��带 ������ ������ ��� ����ü ����
	Data retData;
	// ��ȯ�� �����͸� ������ ���� ����

	/* ť�� ����ִ��� Ȯ�� */
	if (is_empty(pq)) // ť�� ����ִ� ���
	{
		printf("Queue Memory Error!"); // ���� ���
		exit(-1); // ���� ó�� ����
	}

	delNode = pq->front;
	// ������ ��忡 front ����
	retData = delNode->data;
	// ������ ��忡�� �����͸� retData �����Ϳ� ����
	pq->front = pq->front->next;
	// ���� front�� ���� ���� �̵�

	free(delNode); // �����Ǵ� ��� �޸� �Ҵ� ����

	return retData; // ������ ������ ��ȯ
}

/**
 * [radix_sort �Լ�]
 * @param arr    [������ �迭]
 * @param count  [������ ����]
 * @param maxLen [�������� �ִ� �ڸ���]
 */
void radix_sort(int arr[], int count, int maxLen)
{
	Queue buckets[BUCKET_NUM];
	// 0 ���� 9������ �ڸ����� ������ ť �迭 ����
	int bi, pos, di, i;
	// �ݺ������� ����� ���� ����
	int divfac = 1;
	// ���� �ڸ����� ������ ���� ���� �� �ʱ�ȭ
	int radix;
	// ���� �ڸ����� ������ ���� ����

	/* �� 10���� ��Ŷ �ʱ�ȭ */
	for (bi = 0; bi < BUCKET_NUM; bi++)
		queue_init(&buckets[bi]);

	/* ���� �� �������� ���̹�ŭ �ݺ� */
	for (pos = 0; pos < maxLen; pos++)
	{
		/* ���Ĵ���� ����ŭ �ݺ� */
		for (di = 0; di < count; di++)
		{
			/* N��° �ڸ��� ���� ���� */
			radix = (arr[di] / divfac) % 10;

			/* ������ ���ڸ� �ٰŷ� ��Ŷ�� ������ ���� */
			enqueue(&buckets[radix], arr[di]);
		}

		/* ��Ŷ ����ŭ �ݺ� */
		for (bi = 0, di = 0; bi < count; bi++)
		{

			/* ��Ŷ�� ����� �� ������� �� ������ �ٽ� arr�� ���� */
			while (!is_empty(&buckets[bi]))
				arr[di++] = dequeue(&buckets[bi]);
				// ť�� ������ �����Ͽ� ����
		}
		printf("\n");
		/* N��° �ڸ��� ���� ������ ���� �������� ���� */
		divfac *= 10;
	}
}

#endif