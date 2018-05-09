#include <stdio.h>
#include <stdlib.h>

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

	printf("< ");
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->link;
	}
	printf(">");
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

ListNode *get_mid_node(ListNode *head, int count)
{
	int i;
	ListNode *mid = head;

	if (count % 2 != 0)
	{
		for (i = 0; i < count / 2; i++)
			mid = mid->link;
	}

	else
	{
		for (i = 0; i < count / 2 - 1; i++)
			mid = mid->link;
	}

	return mid;
}

int main()
{
	ListNode *list = NULL;
	ListNode *mid = NULL;
	int data, input;
	int data_count = 0, i = 0;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		insert_node(&list, NULL, create_node(data, NULL));
		data_count++;
	}

	do
	{
		mid = list;
		mid = get_mid_node(list, data_count);

		display(list);
		printf("삽입 할 값을 입력하세요( 0 : 종료) : ");
		scanf("%d", &input);

		if (input == 0)
			break;

		else
		{
			insert_node(&list, mid, create_node(input, NULL));
			data_count++;
		}

	} while (input != 0);

	fclose(fp);

	return 0;
}
