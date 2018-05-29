#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct
{
	element stack[MAX];
	int top;
} StackType;

/* 스택 초기화 함수 */
void init(StackType *s)
{
	s->top = -1;
}

/* 공백 상태 검출 함수 */
int is_empty(StackType *s)
{
	return (s->top == -1);
}

/* 포화 상태 검출 함수 */
int is_full(StackType *s)
{
	return (s->top == (MAX - 1));
}

/* 삽입 함수 */
void push(StackType *s, element item)
{
	if (is_full(s))
	{
		fprintf(stderr, "스택 포화 에러\n");
		return;
	}

	else
		s->stack[++(s->top)] = item;
}

/* 삭제 함수 */
element pop(StackType *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}

	else
		return s->stack[(s->top)--];
}

/* 피크 함수 */
element peek(StackType *s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "스택 공백 에러\n");
		exit(1);
	}

	else
		return s->stack[s->top];
}

/* 괄호 검사 함수 */
int check_matching(char *in)
{
	StackType s;
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

void postfix_to_infix(char exp[])
{
	StackType stack;
	int expLen = strlen(exp);
	int convLen;
	char convExp[MAX] = { 0 };

	int i, j;
	char tok, idx = 0;

	init(&stack);

	convExp[idx++] = exp[0];

	for (i = 0; i < expLen; i++)
	{

		if (exp[i] == '+' || exp[i] == '-' ||
			exp[i] == '*' || exp[i] == '/')
		{
			tok = pop(&stack);

			convExp[idx++] = exp[i];
			convExp[idx++] = tok;
			convExp[idx++] = ')';

			convLen = strlen(convExp);

			for (j = convLen; j >= 0; j--)
				convExp[j] = convExp[j - 1];

			convExp[0] = '(';
			idx++;
		}

		else
		{
			push(&stack, exp[i]);
		}

	}

	convExp[idx] = '\0';

	if (!check_matching(convExp))
	{
		printf("잘못된 수식입니다!\n");
		return;
	}

	printf("중위표기식 : %s\n", convExp);
}

int eval(char exp[])
{
	StackType stack;
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
	printf("후위표기식 : %s\n", exp);

	postfix_to_infix(exp);

	printf("결      과 : %d\n\n", eval(exp));
}

int main()
{
	char postfix[100] = { 0 };
	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		exit(-1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s", postfix);
		display(postfix);
	}

	fclose(fp);

	return 0;
}
