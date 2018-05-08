#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct ListNode
{
	int data;
	struct ListNode *link;
} ListNode;

typedef struct List
{
	ListNode *head; // 처음 노드
	ListNode *tail; // 마지막 노드
} List;

void list_init(List *header)
{
	header->head = NULL;
	header->tail = NULL;
}

void insert_node(List *header, int data)
{
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));

	if (header->head == NULL)
	{
		header->head = new_node;
		header->tail = new_node;
		new_node->data = data;
		new_node->link = header->tail;

		return;
	}

	if (header->head != NULL)
	{
		new_node->link = header->head;
		new_node->data = data;
		header->head = new_node;
		header->tail->link = header->head;

		return;
	}
}

void delete_node(List *header, int key)
{
	if (header->head == NULL)
		return;

	ListNode *curr = header->head;
	ListNode *prev;

	while (curr->data != key)
	{
		if (curr->link == header->head)
			break;

		prev = curr;
		curr = curr->link;
	}

	if (curr->link == header->head)
	{
		header->head = NULL;
		free(curr);
		return;
	}

	if (curr == header->head)
	{
		prev = header->head;

		while (prev->link != header->head)
			prev = prev->link;

		header->head = curr->link;
		prev->link = header->head;
		free(curr);
		return;
	}

	else if (curr->link == header->head)
	{
		prev->link = header->head;
		free(curr);
		return;
	}

	else
	{
		prev->link = curr->link;
		free(curr);
		return;
	}
}

List *reverse(List *header)
{
	ListNode *p, *q, *r;

	/* 공백이거나 노드가 하나일 경우 즉, 바꿀필요가 없는 경우 */
	if (header->head->link == header->head || header->head == NULL)
		return header;

	p = header->head->link; // 시작노드 주소 저장
	q = header->head; // q는 역순으로 만들 노드

	while (p != header->head)
	{
		/* r은 역순으로 된 리스트 r은 q, q는 p를 차례로 따라감 */
		r = q;
		q = p;
		p = p->link;
		q->link = r; // q의 링크 방향을 변경
	}

	header->head = q;
	header->tail = p;
	p->link = q;

	return header;
}

/* 리스트의 항목 출력 */
void display(List *header)
{
	ListNode *cur = header->head;

	printf("< ");

	do
	{
		printf("%d ", cur->data);
		cur = cur->link;
	} while (cur != header->head);

	printf(">\n");

	printf("Head : %d\n", header->head->data);
	printf("Tail : %d\n", header->tail->data);
	printf("Tail Next : %d\n", header->tail->link->data);
}


int main()
{
	List list;
	int data, delete_data = 172;
	int num_of_data = 0, i;

	list_init(&list);

	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		insert_node(&list, data);
		num_of_data++;
	}

	display(&list);
	printf("\n");

	reverse(&list);
	delete_node(&list, delete_data);

	printf("< Delete %d >\n", delete_data);
	printf("< Reverse >\n\n");
	display(&list);

	return 0;
}
