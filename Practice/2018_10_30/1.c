#include <stdio.h>
#include <stdlib.h>

typedef struct _std
{
	int num;
	int kor;
	int eng;
	int mat;
	int sum;
	double avg;
} Student;

typedef struct _node
{
	Student data;
	struct _node *link;
} Node;

Node *create_node(Student data, Node *link);
void insert_node(Node **phead, Node *new_node);
void display(Node *head);
void sorted_insert(Node **phead, Node *new_node);
void insertion_sort(Node **phead);

int main()
{
	Node *list = NULL;
	Student temp;

	int count = 0;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d %d",
			&temp.num, &temp.kor, &temp.eng, &temp.mat);
		temp.sum = (temp.kor + temp.eng + temp.mat);
		temp.avg = (double)temp.sum / 3.0;

		insert_node(&list, create_node(temp, NULL));

		count++;
	}

	puts("<정렬 전>");
	display(list);

	insertion_sort(&list);

	puts("<정렬 후>");
	display(list);

	fclose(fp);

	return 0;
}

Node *create_node(Student data, Node *link)
{
	Node *new_node = (Node *)malloc(sizeof(Node));

	if (new_node == NULL)
	{
		printf("Memory Allocation Error!\n");
		return NULL;
	}

	new_node->data = data;
	new_node->link = link;

	return new_node;
}

void insert_node(Node **phead, Node *new_node)
{
	if (*phead == NULL)
	{
		new_node->link = NULL;
		*phead = new_node;
	}

	else
	{
		Node *p = *phead;

		while (p->link != NULL)
			p = p->link;

		p->link = new_node;
	}
}

void display(Node *head)
{
	Node *p = head;

	puts("|========|=============================|");
	puts("|  학번  | 국어| 영어| 수학|총 점|평 균|");

	while (p != NULL)
	{
		printf("|%8d| %3d | %3d | %3d | %3d |%2.2lf|\n",
				p->data.num, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		p = p->link;
	}

	puts("|========|=============================|\n");
}

void sorted_insert(Node **phead, Node *new_node)
{
	Node *current;

	if ((*phead == NULL) ||
			((*phead)->data.sum < new_node->data.sum))
	{
		new_node->link = *phead;
		*phead = new_node;
	}

	else
	{
		current = *phead;

		while (current->link != NULL &&
					(current->link->data.sum > new_node->data.sum))
		{
			current = current->link;
		}

		new_node->link = current->link;
		current->link = new_node;
	}
}

void insertion_sort(Node **phead)
{
	Node *sorted = NULL;
	Node *current = *phead;

	while (current != NULL)
	{
		Node *next = current->link;

		sorted_insert(&sorted, current);

		current = next;
	}

	*phead = sorted;
}
