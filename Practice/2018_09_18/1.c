<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100
#define TRUE 1
#define FALSE 0

typedef char Data;

typedef struct _bTreenode
{
	Data data;
	struct _bTreenode *left;
	struct _bTreenode *right;
} bTreeNode;

typedef struct _stack
{
	int top;
	Data stack[LEN];
} Stack;

/* 이진 트리에 노드를 삽입하는 함수 */
bTreeNode *insert_node(bTreeNode *node, Data data);
/* 이진 트리의 노드를 생성하는 함수 */
bTreeNode *create_node(Data data);

void stack_init(Stack *s);
void push(Stack *s, Data data);
int is_empty(Stack *s);
int is_full(Stack *s);
Data pop(Stack *s);
Data peek(Stack *s);

int prec(char op);
void infix_to_postfix(char *exp);
void display(char *exp);

int main()
{
	char temp[20];
	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %s", temp);

		display(temp);
	}

	fclose(fp);

	return 0;
}

/**
 * [insert_node 함수]
 * @param  node     [이진 트리에 삽입될 노드]
 * @param  data     [새로운 노드에 삽입될 데이터]
 * @return          [노드가 삽입된 루트 노드]
 */
bTreeNode *insert_node(bTreeNode *node, Data data)
{
	/* 루트 노드가 비어있을 경우 */
	if (node == NULL)
		return create_node(data);
		// create_node 함수로 새 노드를 만들고 데이터 삽입 후 반환

	/* 새로 삽입될 데이터가 현재 노드의 데이터 보다 작을 경우 */
	if (data < node->data)
		node->left = insert_node(node->left, data);
	// 왼쪽 노드에 insert_node 함수로 노드 삽입

	/* 새로 삽입될 데이터가 현재 노드의 데이터 보다 클 경우 */
	else if (data > node->data)
		node->right = insert_node(node->right, data);
		// 오른쪽 노드에 insert_node 함수로 노드 삽입

	return node; // 새 노드가 삽입된 노드 반환
}

/**
 * [create_node 함수]
 * @param  data [노드에 삽입될 데이터]
 * @return      [데이터가 삽입된 노드]
 */
bTreeNode *create_node(Data data)
{
	bTreeNode *temp = (bTreeNode *)malloc(sizeof(bTreeNode));
	// 데이터가 삽입될 노드를 동적 할당

	temp->data = data; // 데이터 삽입
	temp->left = NULL; // 왼쪽 자식 노드를 NULL로 저장
	temp->right = NULL; // 오른쪽 자식 노드를 NULL로 저장

	return temp; // 데이터가 저장된 노드를 반환
}

void stack_init(Stack *s)
{
	s->top = -1;
}

void push(Stack *s, Data data)
{
	if (is_full(s))
	{
		printf("STACK FULL ERROR!\n");
		return;
	}

	else
		s->stack[++(s->top)] = data;
}

int is_empty(Stack *s)
{
	return s->top == -1;
}

int is_full(Stack *s)
{
	return s->top == (LEN - 1);
}

Data pop(Stack *s)
{
	if (is_empty(s))
	{
		printf("STACK EMPTY ERROR!\n");
		return;
	}

	else
		return s->stack[s->top--];
}

Data peek(Stack *s)
{
	if (is_empty(s))
	{
		printf("STACK EMPTY ERROR!\n");
		return;
	}

	else
		return s->stack[s->top];
}

int prec(char op)
{
	switch (op)
	{
	case '(':
	case ')':
		return 0;

	case '+':
	case '-':
		return 1;

	case '*':
	case '/':
		return 2;
	}

	return -1;
}

void infix_to_postfix(char *exp)
{
	int i = 0, idx = 0;
	char ch, top_op;
	char PostfixExp[LEN] = { 0 };
	int len = strlen(exp);

	Stack s;

	stack_init(&s);

	for (i = 0; i < len; i++)
	{
		ch = exp[i];

		switch (ch)
		{
		case '+':
		case '-':
		case '*':
		case '/':
			while (!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				PostfixExp[idx++] = pop(&s);

			push(&s, ch);
			break;

		case '(':
			push(&s, ch);
			break;

		case ')':
			top_op = pop(&s);

			while (top_op != '(')
			{
				PostfixExp[idx++] = top_op;

				top_op = pop(&s);
			}
			break;

		default:
			PostfixExp[idx++] = ch;
			break;
		}
	}

	while (!is_empty(&s))
		PostfixExp[idx++] = pop(&s);

	exp = PostfixExp;

	printf("")
}

void display(char *exp)
{
	printf("읽어낸 수식 < %s >\n", exp);
	printf("전위 표기식 < %s >\n", exp);
	printf("후위 표기식 < %s >\n\n", exp);
}
=======
>>>>>>> 51c0e675193ef29c37f2b3bdfe23b4e573f764a2
