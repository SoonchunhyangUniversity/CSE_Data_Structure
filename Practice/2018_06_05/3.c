#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct DlistNode
{
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

typedef struct DequeType
{
	DlistNode *head;
	DlistNode *tail;
	int count;
} DequeType;

/* 오류 처리 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/* 덱의 초기화 함수 */
void init(DequeType *dq)
{
	dq->head = NULL;
	dq->tail = NULL;
	dq->count = 0;
}

/* 노드를 생성하는 함수 */
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
	DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));

	if (node == NULL)
		error("메모리 할당 오류\n");

	node->llink = llink;
	node->rlink = rlink;
	node->data = item;

	return node;
}

/* 덱이 비어있는지 확인하는 함수 */
int is_empty(DequeType *dq)
{
	if (dq->head == NULL)
		return TRUE;

	else
		return FALSE;
}

/* 덱의 뒷부분에서 삽입하는 함수 */
void add_rear(DequeType *dq, element item)
{
	DlistNode *new_node = create_node(dq->tail, item, NULL);

	if (is_empty(dq))
		dq->head = new_node;

	else
		dq->tail->rlink = new_node;

	dq->tail = new_node;
	dq->count++;
}

/* 덱의 앞부분에서 삽입하는 함수 */
void add_front(DequeType *dq, element item)
{
	DlistNode *new_node = create_node(NULL, item, dq->head);

	if (is_empty(dq))
		dq->tail = new_node;

	else
		dq->head->llink = new_node;

	dq->head = new_node;
	dq->count++;
}

/* 덱의 앞부분에서 삭제하는 함수 */
element delete_front(DequeType *dq)
{
	element item;
	DlistNode *removed_node;

	if (is_empty(dq))
		error("덱이 비어있습니다.\n");

	else
	{
		removed_node = dq->head; // 삭제할 노드 저장
		item = removed_node->data; // 삭제될 데이터 저장
		dq->head = dq->head->rlink; // 덱의 헤드포인터 변경

		free(removed_node); // 노드의 메모리 할당 해제

		if (dq->head == NULL)
			dq->tail = NULL;

		else
			dq->head->llink = NULL;

		dq->count--;
	}

	return item;
}

/* 덱의 뒷부분에서 삭제하는 함수 */
element delete_rear(DequeType *dq)
{
	element item;
	DlistNode *removed_node;

	if (is_empty(dq))
		error("덱이 비어있습니다.\n");

	else
	{
		removed_node = dq->tail; // 삭제할 노드 저장
		item = removed_node->data; // 삭제될 데이터 저장
		dq->tail = dq->tail->llink; // 덱의 헤드포인터 변경

		free(removed_node); // 노드의 메모리 할당 해제

		if (dq->tail == NULL)
			dq->head = NULL;

		else
			dq->tail->rlink = NULL;

		dq->count--;
	}

	return item;
}

void display(DequeType *dq, char *oper, char *position, element item)
{
	DlistNode *temp = dq->head;
	static int step = 1;
	int i;

	if (!strcmp(oper, "add"))
		printf("---Step %d : %s %s %d ---\n", step++, oper, position, item);

	else if(!strcmp(oper, "delete"))
		printf("---Step %d : %s %s ---\n", step++, oper, position);

	printf("┌");

	for (i = 0; i <= (dq->count * 3); i++)
		printf("─");

	printf("┐\n");

	while (temp != NULL)
	{
		printf("  %d", temp->data);
		temp = temp->rlink;
	}

	printf("\n└");

	for (i = 0; i <= (dq->count * 3); i++)
		printf("─");

	printf("┘\n");
}

int main()
{
	DequeType deque;
	element item;
	char oper[8] = { 0 };
	char position[6] = { 0 };

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	init(&deque);

	while (!feof(fp))
	{
		fscanf(fp, "%s %s", oper, position);

		if (!strcmp(oper, "add"))
		{
			fscanf(fp, "%d", &item);

			if (!strcmp(position, "front"))
				add_front(&deque, item);

			else if (!strcmp(position, "rear"))
				add_rear(&deque, item);
		}

		else if (!strcmp(oper, "delete"))
		{
			if (!strcmp(position, "front"))
				item = delete_front(&deque);

			else if (!strcmp(position, "rear"))
				item = delete_rear(&deque);
		}

		else
		{
			fprintf(stderr, "잘못된 연산자입니다.\n");
			return 0;
		}

		display(&deque, oper, position, item);
	}

	return 0;
}
