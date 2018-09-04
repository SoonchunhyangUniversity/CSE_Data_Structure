#include <stdio.h>
#include <stdlib.h>

#define NAME_LEN 100

typedef struct _data
{
	int std_num;
	char name[NAME_LEN];
	int math;
	int eng;
	int kor;
	int sum;
	double avg;
}Data;

typedef struct _node
{
	Data data;
	struct _node *next;
}Node;

Node *create_node(Data data, Node *next);
void insert(Node **phead, Node *p, Node *new_node);
void display(Node *head);
void swap(Node *a, Node *b);
void sort(Node *head);

int main()
{
	Node *list = NULL;
	Data temp;
	int count = 0;
	char len_check[NAME_LEN] = { NULL };

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s", len_check);
		count++;
	}

	rewind(fp);

	for (int i = 0; i < count / 5; i++)
	{
		fscanf(fp, "%d %s %d %d %d",
					&temp.std_num, temp.name, &temp.math, &temp.eng, &temp.kor);

		temp.sum = temp.kor + temp.eng + temp.math;
		temp.avg = temp.sum / 3.0;

		insert(&list, NULL, create_node(temp, NULL));
	}

	sort(list);
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

	printf("│========================================================│\n");
	printf("│ 학     번 │ 이 름 │ 수학 │ 영어 │ 국어 │ 총 점 │ 평 균 │\n");
	printf("│========================================================│\n");

	while (p != NULL)
	{
		printf("│ %9d │ %s│  %3d │  %3d │  %3d │  %3d  │ %.2f │\n",
			p->data.std_num, p->data.name,
			p->data.math, p->data.eng, p->data.kor,
			p->data.sum, p->data.avg);

		p = p->next;
	}

	printf("│========================================================│\n");
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
	Data temp = a->data;
	a->data = b->data;
	b->data = temp;
}

void sort(Node *head)
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
			if (cur->data.avg < cur->next->data.avg)
			{
				swap(cur, cur->next);
				check = 1;
			}

			cur = cur->next;
		}

		pre = cur;
	}
}
