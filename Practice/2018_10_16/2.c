#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define BUCKET_NUM 10

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _lQueue
{
	Node * front;
	Node * rear;
} Queue;

void QueueInit(Queue * pq);
int QIsEmpty(Queue * pq);
void Enqueue(Queue * pq, Data data);
Data Dequeue(Queue * pq);
Data QPeek(Queue * pq);

void radix_sort(int arr[], int count, int maxLen);
void display(int arr[], int count);

int main()
{
	int *arr = NULL;
	int count = 0;
	int i;

	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		count++;
	}

	rewind(fp);

	arr = (int *)malloc(sizeof(int) * count);

	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &arr[i]);

	printf("< 정렬전 데이터 >\n");
	display(arr, count);

	printf("\n< 정렬 과정 >\n");
	radix_sort(arr, count, 3);

	printf("< 정렬후 데이터 >\n");
	display(arr, count);

	fclose(fp);

	return 0;
}

void radix_sort(int arr[], int count, int maxLen)
{
	/* 매개변수 maxLen에는 정렬대상 중 가장 긴 데이터의 길이 정보가 전달 */
	Queue buckets[BUCKET_NUM];
	int bi, pos, di, i;
	int divfac = 1;
	int radix;

	/* 총 10개의 버킷 초기화 */
	for (bi = 0; bi < BUCKET_NUM; bi++)
		QueueInit(&buckets[bi]);

	/* 가장 긴 데이터의 길이반큼 반복 */
	for (pos = 0; pos < maxLen; pos++)
	{
		printf("- Digit %d -\n", pos + 1);
		/* 정렬대상의 수만큼 반복 */
		for (di = 0; di < count; di++)
		{
			/* N번째 자리의 숫자 추출 */
			radix = (arr[di] / divfac) % 10;

			/* 추출한 숫자를 근거로 버킷에 데이터 저장 */
			Enqueue(&buckets[radix], arr[di]);
		}

		/* 버킷 수만큼 반복 */
		for (bi = 0, di = 0; bi < count; bi++)
		{
			printf("Bucket[%d] : ", bi);

			if (QIsEmpty(&buckets[bi]))
				printf("Empty");

			/* 버킷에 저장된 것 순서대로 다 꺼내서 다시 arr에 저장 */
			while (!QIsEmpty(&buckets[bi]))
			{
				i = Dequeue(&buckets[bi]);
				arr[di++] = i;
				printf(" %d", i);
			}

			printf("\n");
		}
		printf("\n");
		/* N번째 자리의 숫자 추출을 위한 피제수의 증가 */
		divfac *= 10;
	}
}

void display(int arr[], int count)
{
	int i;

	for (i = 0; i < count; i++)
		printf("%d > ", arr[i]);

	printf("\n");
}

void QueueInit(Queue * pq)
{
	pq->front = NULL;
	pq->rear = NULL;
}

int QIsEmpty(Queue * pq)
{
	if (pq->front == NULL)
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue * pq, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = data;

	if (QIsEmpty(pq))
	{
		pq->front = newNode;
		pq->rear = newNode;
	}
	else
	{
		pq->rear->next = newNode;
		pq->rear = newNode;
	}
}

Data Dequeue(Queue * pq)
{
	Node * delNode;
	Data retData;

	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	delNode = pq->front;
	retData = delNode->data;
	pq->front = pq->front->next;

	free(delNode);
	return retData;
}

Data QPeek(Queue * pq)
{
	if (QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}

	return pq->front->data;
}
