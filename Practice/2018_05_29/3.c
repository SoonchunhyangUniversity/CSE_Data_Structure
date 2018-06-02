/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 3
 * 작성일 : 2018 - 05 - 29
 */

#include <stdio.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
#define MAZE_SIZE 6

typedef struct
{
	short r;
	short c;
} element;

element here = { 1, 0 }, entry = { 1, 0 };

char maze[MAX_STACK_SIZE][MAX_STACK_SIZE] =
{
	{ '1', '1', '1', '1', '1', '1' },
	{ 'e', '0', '1', '0', '0', '1' },
	{ '1', '0', '0', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', '1' },
	{ '1', '0', '1', '0', '0', 'x' },
	{ '1', '1', '1', '1', '1', '1' },
};

typedef struct
{
	element stack[MAX_STACK_SIZE];
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
	return (s->top == (MAX_STACK_SIZE - 1));
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

/* 위치를 스택에 삽입 */
void push_loc(StackType *s, int r, int c)
{
	if (r < 0 || c < 0)
		return;

	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp;

		tmp.r = r;
		tmp.c = c;

		push(s, tmp);
	}
}

void printMaze()
{
	int r, c;

	printf("\n\n");

	for (r = 0; r < MAZE_SIZE; r++)
	{
		for (c = 0; c < MAZE_SIZE; c++)
		{
			if (c == here.c && r == here.r)
				printf("m ");

			else
			{
				if (maze[r][c] == '0')
					printf("0 ");

				else
					printf("%c ", maze[r][c]);
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

void printStack(StackType *s)
{
	int i;

	for (i = 5; i > s->top; i--)
	{
		printf("|      |\n");

		for (i = s->top; i >= 0; i--)
			printf("|(%01d, %01d)|\n", s->stack[i].r, s->stack[i].c);

		printf("--------\n");
	}
}

int main()
{
	int r, c;
	StackType s;

	init(&s);

	here = entry;

	while (maze[here.r][here.c] != 'x')
	{
		r = here.r;
		c = here.c;

		maze[r][c] = '.';

		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		printMaze();
		printStack(&s);

		if (is_empty(&s))
		{
			printf("실패\n");
			return;
		}

		else
			here = pop(&s);
	}

	printMaze();
	printStack(&s);

	printf("성공\n");

	return 0;
}
