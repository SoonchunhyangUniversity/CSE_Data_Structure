#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode *link;
} ListNode;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/*
phead : 리스트의 헤드 포인터의 포인터
p : 선행 노트
new_node : 삽입될 노드
*/
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void display(ListNode *head)
{
	ListNode *p = head;

	while (p != NULL)
	{
		printf("< %d >", p->data);
		p = p->link;
	}
	printf("\n");
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));

	if (new_node == NULL)
		error("메모리 할당 에러");

	new_node->data = data;
	new_node->link = link;

	return (new_node);
}

void swap(ListNode *a, ListNode *b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void sort(ListNode *phead)
{
	int check = 1;
	ListNode *node;
	ListNode *next = NULL;

	if (phead == NULL)
		return;

	while(check)
	{
		check = 0;
		node = phead;

		while (node->link != next)
		{
			if (node->data > node->link->data)
			{
				swap(node, node->link);
				check = 1;
			}

			node = node->link;
		}

		next = node;
	}
}

int main()
{
	int num;
	int i;
	ListNode *list = NULL;

	srand((unsigned)time(NULL));

	printf("생성할 노드의 갯수를 입력하세요 : ");
	scanf("%d", &num);
	printf("\n");

	for(i = 0; i < num; i++)
		insert_node(&list, NULL, create_node(rand() % 100 + 1, NULL));

	printf("생성된 리스트\n");
	display(list);
	printf("\n");

	printf("정렬된 리스트\n");
	sort(list);
	display(list);

	return 0;
}
