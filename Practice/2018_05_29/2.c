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
#define MAX 100
#define TRUE 1
#define FALSE 0

typedef int Data;

int step = 1;
int stack1_len;
int stack2_len;
int stack_temp1[MAX];
int stack_temp2[MAX];

typedef struct _node
{
	Data data;
	struct _node *next;
} Node;

typedef struct _listStack
{
	Node *head;
} ListStack;

typedef ListStack Stack;

void init(Stack *pstack)
{
	pstack->head = NULL;
}

int is_empty(Stack * pstack)
{
	if (pstack->head == NULL)
		return TRUE;

	else
		return FALSE;
}

void push(Stack *pstack, int stack_num, Data data)
{
	Stack temp;
	int i, j;

	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;

	printf("---Step %d : 스택%d %d 입력 ---\n", step++, stack_num, data);

	if (stack_num == 1)
		stack_temp1[++stack1_len] = data;

	if (stack_num == 2)
		stack_temp2[++stack2_len] = data;

	if (stack1_len > stack2_len)
	{
		i = stack1_len;
		j = stack1_len;
	}

	else
	{
		i = stack2_len;
		j = stack2_len;
	}

	while(TRUE)
	{

		if (i <= 0 && j <= 0)
			break;

		if (i > stack1_len)
			printf("│         │");

		else
			printf("│ < %3d > │", stack_temp1[i]);

		if(j > stack2_len)
			printf("│         │\n");

		else
			printf("│ < %3d > │\n", stack_temp2[j]);

		i--;
		j--;
	}

	printf("└─────────┘└─────────┘\n\n");

}

Data pop(Stack *pstack, int stack_num)
{
	Data rdata;
	Node *rnode;
	int i, j;

	if (is_empty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);


	printf("---Step %d : 스택%d %d 삭제 ---\n", step++, stack_num, rdata);

	if (stack_num == 1)
		stack1_len -= 1;

	if (stack_num == 2)
		stack2_len -= 1;

	if (stack1_len > stack2_len)
	{
		i = stack1_len;
		j = stack1_len;
	}

	else
	{
		i = stack2_len;
		j = stack2_len;
	}

	while(TRUE)
	{
		if (i <= 0 && j <= 0)
			break;

		if (i > stack1_len)
			printf("│         │");

		else
			printf("│ < %3d > │", stack_temp1[i]);

		if (j > stack2_len)
			printf("│         │\n");

		else
			printf("│ < %3d > │\n", stack_temp2[j]);

		i--;
		j--;
	}

	printf("└─────────┘└─────────┘\n\n");

	return rdata;
}


int main()
{
	Stack s1, s2;
	int temp, stack_num;
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
			fscanf(fp, "%d", &temp);

			if(stack_num == 1)
				push(&s1, stack_num, temp);

			if (stack_num == 2)
				push(&s2, stack_num, temp);
		}

		else if (!strcmp(oper, "pop"))
		{
			if (stack_num == 1)
				pop(&s1, stack_num);

			if (stack_num == 2)
				pop(&s2, stack_num);
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
