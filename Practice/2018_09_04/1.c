/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 파일에서 자료 읽어오기1
 * 작성일 : 2018-09-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언

typedef int Data; // int형 데이터를 typedef선언으로 Data 키워드로 사용 가능

typedef struct _node
{
	Data data;
	struct _node *next;
}Node;

Node *create_node(Data data, Node *next);
void insert(Node **phead, Node *p, Node *new_node);
void display(Node *head);
void swap(Node *a, Node *b);
void down_to_up_sort(Node *head);
void up_to_down_sort(Node *head);

int main()
{
	Node *list = NULL;
	int count = 0;
	int temp;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		count++;
	}

	rewind(fp);

	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d", &temp);
		insert(&list, NULL, create_node(temp, NULL));
	}

	printf("<오름차순 정렬>\n");
	down_to_up_sort(list);
	display(list);

	printf("\n");

	printf("<내림차순 정렬>\n");
	up_to_down_sort(list);
	display(list);

	fclose(fp);

	return 0;
}

Node *create_node(Data data, Node *next)
{
	Node *new_node;
	new_node = (Node *)malloc(sizeof(Node));

	if (new_node == NULL)
	{
		printf("NODE MALLOC ERROR!\n");
		return 0;
	}

	new_node->data = data;
	new_node->next = next;

	return new_node;
}

void display(Node *head)
{
	Node *p = head;

	while (p != NULL)
	{
		if (p->next == NULL)
		{
			printf(" %d", p->data);
			break;
		}

		printf(" %d ->", p->data);
		p = p->next;
	}

	printf("\n");
}

void insert(Node **phead, Node *p, Node *new_node)
{
	if (*phead == NULL)
	{
		new_node->next = NULL;
		*phead = new_node;
	}

	else if (p == NULL)
	{
		new_node->next = *phead;
		*phead = new_node;
	}

	else
	{
		new_node->next = p->next;
		p->next = new_node;
	}
}

void swap(Node *a, Node *b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void down_to_up_sort(Node *head)
{
	int check = 1;
	Node *cur;
	Node *pre = NULL;

	if (head == NULL)
		return;

	while (check)
	{
		check = 0;
		cur = head;

		while (cur->next != pre)
		{
			if (cur->data > cur->next->data)
			{
				swap(cur, cur->next);
				check = 1;
			}

			cur = cur->next;
		}

		pre = cur;
	}
}

void up_to_down_sort(Node *head)
{
	int check = 1;
	Node *cur;
	Node *pre = NULL;

	if (head == NULL)
		return;

	while (check)
	{
		check = 0;
		cur = head;

		while (cur->next != pre)
		{
			if (cur->data < cur->next->data)
			{
				swap(cur, cur->next);
				check = 1;
			}

			cur = cur->next;
		}

		pre = cur;
	}
}
