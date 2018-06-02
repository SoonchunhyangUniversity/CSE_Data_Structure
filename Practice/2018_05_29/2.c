/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 2
 * 작성일 : 2018 - 05 - 29
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0

int step = 1;
int stack1_len;
int stack2_len;

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *next;
} Node;

typedef struct _listStack
{
	Node *head;
} Stack;

void init(Stack *pstack)
{
	pstack->head = NULL;
}

int is_empty(Stack *pstack)
{
	if (pstack->head == NULL)
		return TRUE;

	else
		return FALSE;
}

void push(Stack *stack1, Stack *stack2, int stack_num, Data data)
{
	if (stack_num == 1)
	{
		Node *newNode = (Node *)malloc(sizeof(Node));

		newNode->data = data;
		newNode->next = stack1->head;

		stack1->head = newNode;
		stack1_len++;
	}

	else
	{
		Node *newNode = (Node *)malloc(sizeof(Node));

		newNode->data = data;
		newNode->next = stack2->head;

		stack2->head = newNode;
		stack2_len++;
	}
}

Data pop(Stack *stack1, Stack *stack2, int stack_num)
{
	Data rdata;
	Node *rnode;

	if (stack_num == 1)
	{
		if (is_empty(stack1))
		{
			printf("Stack Memory Error!");
			exit(-1);
		}

		rdata = stack1->head->data;
		rnode = stack1->head;

		stack1->head = stack1->head->next;
		free(rnode);
		stack1_len--;
	}

	else
	{
		if (is_empty(stack2))
		{
			printf("Stack Memory Error!");
			exit(-1);
		}

		rdata = stack2->head->data;
		rnode = stack2->head;

		stack2->head = stack2->head->next;
		stack2_len--;
	}

	return rdata;
}

void display_push(Stack *stack1, Stack *stack2, int stack_num, Data data)
{
	Node *stack1_temp, *stack2_temp;
	int stack1_display_count, stack2_display_count;

	stack1_temp = stack1->head;
	stack2_temp = stack2->head;

	printf("---Step %d : 스택%d %d 입력 ---\n", step++, stack_num, data);

	if (stack1_len > stack2_len)
	{
		stack1_display_count = stack1_len;
		stack2_display_count = stack1_len;
	}

	else
	{
		stack1_display_count = stack2_len;
		stack2_display_count = stack2_len;
	}

	while (stack1_display_count > 0 && stack2_display_count > 0)
	{

		if (stack1_display_count > stack1_len)
			printf("│         │");

		else
		{
			printf("│ < %3d > │", stack1_temp->data);
			stack1_temp = stack1_temp->next;
		}

		if (stack2_display_count > stack2_len)
			printf("│         │\n");

		else
		{
			printf("│ < %3d > │\n", stack2_temp->data);
			stack2_temp = stack2_temp->next;
		}

		stack1_display_count--;
		stack2_display_count--;
	}

	printf("└─────────┘└─────────┘\n\n");
}

void display_pop(Stack *stack1, Stack *stack2, int stack_num, int rdata)
{
	Node *stack1_temp, *stack2_temp;
	int stack1_display_count, stack2_display_count;

	stack1_temp = stack1->head;
	stack2_temp = stack2->head;

	printf("---Step %d : 스택%d %d 삭제 ---\n", step++, stack_num, rdata);

	if (stack1_len > stack2_len)
	{
		stack1_display_count = stack1_len;
		stack2_display_count = stack1_len;
	}

	else
	{
		stack1_display_count = stack2_len;
		stack2_display_count = stack2_len;
	}

	while (stack1_display_count > 0 && stack2_display_count > 0)
	{

		if (stack1_display_count > stack1_len)
			printf("│         │");

		else
		{
			printf("│ < %3d > │", stack1_temp->data);
			stack1_temp = stack1_temp->next;
		}

		if (stack2_display_count > stack2_len)
			printf("│         │\n");

		else
		{
			printf("│ < %3d > │\n", stack2_temp->data);
			stack2_temp = stack2_temp->next;
		}

		stack1_display_count--;
		stack2_display_count--;
	}

	printf("└─────────┘└─────────┘\n\n");
}

int main()
{
	Stack s1, s2;
	Data data;
	int stack_num, rdata;
	char oper[5] = { 0 };

	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		exit(-1);
	}

	init(&s1);
	init(&s2);

	while (!feof(fp))
	{
		fscanf(fp, "%s %d", oper, &stack_num);

		if (!strcmp(oper, "push"))
		{
			fscanf(fp, "%d", &data);

			if(stack_num == 1)
				push(&s1, &s2, stack_num, data);

			else if (stack_num == 2)
				push(&s1, &s2, stack_num, data);

			display_push(&s1, &s2, stack_num, data);
		}

		else if (!strcmp(oper, "pop"))
		{
			if (stack_num == 1)
				rdata = pop(&s1, &s2, stack_num);

			else if (stack_num == 2)
				rdata = pop(&s1, &s2, stack_num);

			display_pop(&s1, &s2, stack_num, rdata);
		}

		else
		{
			printf("Operator Error!\n");
			return 0;
		}
	}

	fclose(fp);

	return 0;
}
