#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int element;

typedef struct QueueNode
{
	element item;
	struct QueueNode *link;
} QueueNode;

typedef struct
{
	QueueNode *front;
	QueueNode *rear;
	int count;
} QueueType;

/* 오류를 출력하는 함수 */
void error(char *messgae)
{
	fprintf(stderr, "%s\n", messgae);
	exit(1);
}

/* 큐의 초기화 함수 */
void init(QueueType *q)
{
	q->front = NULL;
	q->rear = NULL;
	q->count = 0;
}

/* 큐가 비어있는지 확인하는 함수 */
int is_empty(QueueType *q)
{
	return (q->front == NULL);
}

/* 큐의 데이터 삽입 함수 */
void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));

	if (temp == NULL)
		error("메모리를 할당할 수 없습니다.\n");

	else
	{
		temp->item = item; // 데이터 저장
		temp->link = NULL; // 노드의 다음 노드를 NULL로 저장

						   /* 큐가 비어있을 경우 */
		if (is_empty(q))
		{
			q->front = temp;
			q->rear = temp;
		}

		/* 큐가 비어있지 않을 경우 */
		else
		{
			q->rear->link = temp;
			q->rear = temp;
		}

		q->count++;
	}
}

/* 큐의 데이터 삭제 함수 */
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;

	/* 큐가 비어있을 경우 */
	if (is_empty(q))
		error("큐가 비어있습니다.\n");

	/* 큐가 비어있지 않을 경우 */
	else
	{
		item = temp->item; // 데이터를 저장
		q->front = q->front->link; // front가 다음 노드를 가리키게 한다.

								   /* 큐가 비어있는 상태가 될 경우 */
		if (q->front == NULL)
			q->rear = NULL;

		free(temp); // 노드의 메모리 할당 해제

		q->count--;

		return item; // 삭제된 데이터 반환
	}
}

/* 큐의 peek 함수 */
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 비어있습니다.\n");

	else
		return q->front->item;
}

void display(QueueType *q, char *oper, element item)
{
	QueueNode *temp = q->front;
	static step = 1;
	int i;

	if (!strcmp(oper, "addq"))
		printf("---Step %d : %s %d ---\n", step++, oper, item);

	else if (!strcmp(oper, "deleteq"))
		printf("---Step %d : %s ---\n", step++, oper);

	printf("┌");

	for (i = 0; i <= (q->count * 3); i++)
		printf("─");

	printf("┐\n");

	while (temp != NULL)
	{
		printf("  %d", temp->item);
		temp = temp->link;
	}

	printf("\n└");

	for (i = 0; i <= (q->count * 3); i++)
		printf("─");

	printf("┘\n");
}

int main()
{
	QueueType q;
	element item;
	char oper[8] = { 0 };

	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	init(&q);

	while (!feof(fp))
	{
		fscanf(fp, "%s", oper);

		if (!strcmp(oper, "addq"))
		{
			fscanf(fp, "%d ", &item);
			enqueue(&q, item);
		}

		else if (!strcmp(oper, "deleteq"))
			item = dequeue(&q);

		else
		{
			fprintf(stderr, "잘못된 연산자 입니다.\n");
			return 0;
		}

		display(&q, oper, item);
	}

	fclose(fp);

	return 0;
}
