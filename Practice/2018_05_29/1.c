#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
#define TRUE 1
#define FALSE 0

typedef int Data;

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

void init(Stack * pstack)
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

void push(Stack * pstack, Data data)
{
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = pstack->head;

	pstack->head = newNode;
}

Data pop(Stack * pstack)
{
	Data rdata;
	Node * rnode;

	if (is_empty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rdata = pstack->head->data;
	rnode = pstack->head;

	pstack->head = pstack->head->next;
	free(rnode);

	return rdata;
}

Data peek(Stack * pstack)
{
	if (is_empty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->head->data;
}

/* 괄호 검사 함수 */
int check_matching(char *in)
{
	Stack s;
	char ch, open_ch;
	int i, n = strlen(in);

	init(&s);

	for (i = 0; i < n; i++)
	{
		ch = in[i]; // 다음 문자

		switch (ch)
		{
		case '(':
		case '[':
		case '{':
			push(&s, ch);
			break;

		case ')':
		case ']':
		case '}':
			if (is_empty(&s))
				return FALSE;

			else
			{
				open_ch = pop(&s);

				if ((open_ch == '(' && ch != ')') ||
					(open_ch == '[' && ch != ']') ||
					(open_ch == '{' && ch != '}'))
					return FALSE;
			}
			break;

		default:
			break;
		}
	}

	/* 스택에 남아있으면 오류 */
	if (!is_empty(&s))
		return FALSE;

	return TRUE;
}

int prec(char op)
{
	switch (op)
	{
	case '*':
	case '/':
		return 2;

	case '+':
	case '-':
		return 1;

	case '(':
		return 0;
	}

	return -1;
}

int prec_check(char op1, char op2)
{
	int op1Prec = prec(op1);
	int op2Prec = prec(op2);

	if (op1Prec > op2Prec)
		return 1;

	else if (op1Prec < op2Prec)
		return -1;

	else
		return 0;
}

void infix_to_postfix(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	char *convExp = (char *)malloc(expLen + 1);

	int i, idx = 0;
	char tok, popOp;

	memset(convExp, 0, sizeof(char) * expLen + 1);
	init(&stack);

	for (i = 0; i < expLen; i++)
	{
		tok = exp[i];

		if (isdigit(tok))
		{
			convExp[idx++] = tok;
		}

		else
		{
			switch (tok)
			{
			case '(':
				push(&stack, tok);
				break;

			case ')':
				while (TRUE)
				{
					popOp = pop(&stack);

					if (popOp == '(')
						break;

					convExp[idx++] = popOp;
				}

				break;

			case '+':
			case '-':
			case '*':
			case '/':
				while (!is_empty(&stack) && prec_check(peek(&stack), tok) >= 0)
					convExp[idx++] = pop(&stack);

				push(&stack, tok);
				break;
			}
		}
	}

	while (!is_empty(&stack))
		convExp[idx++] = pop(&stack);

	strcpy(exp, convExp);
	free(convExp);
}

int eval(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;

	init(&stack);

	for (i = 0; i < expLen; i++)
	{
		tok = exp[i];

		if (isdigit(tok))
		{
			push(&stack, tok - '0');
		}

		else
		{
			op2 = pop(&stack);	// 두 번째 피연산자
			op1 = pop(&stack);	// 첫 번째 피연산자

			switch (tok)
			{
			case '+':
				push(&stack, op1 + op2);
				break;

			case '-':
				push(&stack, op1 - op2);
				break;

			case '*':
				push(&stack, op1 * op2);
				break;

			case '/':
				push(&stack, op1 / op2);
				break;
			}
		}
	}

	return pop(&stack);
}

void display(char exp[])
{
	if (!check_matching(exp))
	{
		printf("잘못된 수식입니다!\n");
		return;
	}

	printf("중위표기식 : %s", exp);

	infix_to_postfix(exp);
	printf("후위표기식 : %s\n", exp);
	printf("결      과 : %d\n\n", eval(exp));
}

int main()
{
	char infix[100] = { 0 };
	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		exit(-1);
	}

	while (!feof(fp))
	{
		fgets(infix, MAX, fp);
		display(infix);
	}

	fclose(fp);

	return 0;
}
