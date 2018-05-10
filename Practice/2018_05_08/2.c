/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 원형 연결 리스트
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 08
	*
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define DEL_DATA 172

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
	int check = 1;

	while (check)
	{
		check = 0;

		ListNode *curr = header->head;
		ListNode *prev = header->tail;

		do
		{
			if (curr->data == key)
			{
				if (curr == header->head)
				{
					header->tail->link = header->head->link;
					header->head = header->head->link;
					free(curr);
				}

				else if (curr == header->tail)
				{
					prev->link = header->tail->link;
					header->tail = header->tail->link;
					free(curr);
				}

				else
				{
					prev->link = curr->link;
					free(curr);
				}

				check = 1;
				break;
			}

			else
			{
				prev = curr;
				curr = curr->link;
			}

		} while (curr != header->head);
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
	int data;

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
	}

	display(&list);
	printf("\n");

	delete_node(&list, DEL_DATA);
	//reverse(&list);

	printf("< Delete %d >\n", DEL_DATA);
	printf("< Reverse >\n\n");
	display(&list);

	fclose(fp);

	return 0;
}
