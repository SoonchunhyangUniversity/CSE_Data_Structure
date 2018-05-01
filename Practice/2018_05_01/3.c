#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct ListNode
{
	int data_num;
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

/*
	phead : 헤드 포인터의 포인터
	p : 삭제될 노드의 선행 노트
	removed : 삭제될 노드
*/
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = removed->link;

	free(removed);
}

void remove_odd_node(ListNode **phead)
{
	ListNode *ph = *phead;
	ListNode *prev = NULL;
	int count = 0;

	while (ph != NULL)
	{
		if (count % 2 == 0)
		{
			remove_node(phead, prev, ph);

			if (prev != NULL)
				ph = prev->link;

			else
				ph = *phead;
		}

		else
		{
			prev = ph;
			ph = ph->link;
		}
		count++;
	}
}

void display(ListNode *head)
{
	ListNode *p = head;

	while (p != NULL)
	{
		if (p->link == NULL)
			printf("%d\n", p->data);

		else
			printf("%d -> ", p->data);

		p = p->link;
	}
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

int main()
{
	ListNode *list = NULL;
	int data;
	int data_count = 0;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		insert_node(&list, NULL, create_node(data, NULL));
		data_count++;
	}

	display(list);

	remove_odd_node(&list);

	display(list);

	fclose(fp);

	return 0;
}
