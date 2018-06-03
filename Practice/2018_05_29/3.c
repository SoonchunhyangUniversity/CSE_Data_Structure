/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 3
 * 작성일 : 2018 - 05 - 29
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#define MAX 100 // 기호 상수 MAX를 100로 정의
#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0로 정의
#define MAZE_SIZE 6 // 기호 상수 MAZE_SIZE를 6로 정의

/* 미로의 좌표를 저장하는 구조체 */
typedef struct
{
	short r; // row좌표
	short c; // col좌표
} element; // elemnet 키워드로 선언 가능

/* 처음 시작 지점과 입구 데이터 선언 및 초기화 */
element here = { 1, 0 }, entry = { 1, 0 };

/* 6 by 6의 미로 초기화 */
char maze[MAX][MAX] =
{
	{ '1', '1', '1', '1', '1', '1' },
	{ 'e', '0', '1', '0', '0', '1' },
	{ '1', '0', '0', '0', '1', '1' },
	{ '1', '0', '1', '0', '1', '1' },
	{ '1', '0', '1', '0', '0', 'x' },
	{ '1', '1', '1', '1', '1', '1' },
};

/* 배열 기반 스택 구조체 */
typedef struct
{
	element stack[MAX]; // element형 배열
	int top; // 최상위 인덱스 값을 저장할 변수
} StackType; // StackType 키워드로 선언 가능

/* 스택의 초기화 함수 */
void init(StackType *s)
{
	s->top = -1; // 스택의 top변수를 -1로 초기화
}

/* 스택의 공백 상태 검출 함수 */
int is_empty(StackType *s)
{
	return (s->top == -1);
	// 스택의 top이 -1이면 TRUE 반환 그렇지 않으면 FALSE 반환
}

/* 포화 상태 검출 함수 */
int is_full(StackType *s)
{
	return (s->top == (MAX - 1));
	// 스택의 top이 MAX - 1이면 TRUE 반환 그렇지 않으면 FALSE 반환
}

/* 스택의 데이터 삽입 함수 */
void push(StackType *s, element item)
{
	/* 스택이 가득 차 있다면 */
	if (is_full(s))
	{
		printf("스택 포화 에러\n"); // 에러 메세지 출력
		return; // 함수 종료
	}

	/* 그렇지 않으면 */
	else
		s->stack[++(s->top)] = item;
		// 스택의 최상위 인덱스를 1 증가시키고 데이터 삽입
}

/* 스택의 데이터 삭제 함수 */
element pop(StackType *s)
{
	/* 스택이 비어있다면 */
	if (is_empty(s))
	{
		printf("스택 공백 에러\n"); // 에러 메세지 출력
		return; // 함수 종료
	}

	/* 그렇지 않으면 */
	else
		return s->stack[(s->top)--];
		// 스택의 최상위 인덱스의 데이터 반환 후 인덱스 1 감소
}

/* 스택의 피크 함수 */
element peek(StackType *s)
{
	/* 스택이 비어있다면 */
	if (is_empty(s))
	{
		printf("스택 공백 에러\n"); // 에러 메세지 출력
		return; // 함수 종료
	}

	/* 그렇지 앙ㄶ으면 */
	else
		return s->stack[s->top];
		// 스택의 최상위 인덱스의 데이터 반환
}

/* 위치를 스택에 삽입 */
void push_loc(StackType *s, int r, int c)
{
	/* 올바른 위치가 아닐 경우 */
	if (r < 0 || c < 0)
		return; // 함수 종료

	/* 미로의 데이터가 '1'이나 '.'이 아닐 경우 */
	if (maze[r][c] != '1' && maze[r][c] != '.')
	{
		element tmp; // 임시로 데이터를 저장할 변수 선언

		tmp.r = r; // tmp의 r에 r 저장
		tmp.c = c; // tmp의 c에 c 저장

		push(s, tmp); // 스택에 tmp 푸시
	}
}

/* 미로를 출력하는 함수 */
void printMaze()
{
	int r, c; // 반복문에서 사용 할 변수 선언

	printf("\n\n");

	/* MAZE_SIZE번 반복하는 반복문 */
	for (r = 0; r < MAZE_SIZE; r++)
	{
		/* MAZE_SIZE번 반복하는 반복문 */
		for (c = 0; c < MAZE_SIZE; c++)
		{
			/* 현재의 위치와 같을 경우 */
			if (c == here.c && r == here.r)
				printf("m "); // 'm' 출력

			/* 그렇지 않을 경우 */
			else
			{
				/* 미로의 데이터가 '0'일 경우 */
				if (maze[r][c] == '0')
					printf("0 "); // '0' 출력

				/* 그렇지 않을 경우 */
				else
					printf("%c ", maze[r][c]); // 미로의 데이터 출력
			}
		}
		printf("\n");
	}
	printf("\n\n");
}

/* 스택의 데이터를 출력하는 함수 */
void printStack(StackType *s)
{
	int i; // 반복문에서 사용할 변수 선언

	/* 스택의 최상위 인덱스와 같아질 때 까지 반복하는 반복문 */
	for (i = 5; i > s->top; i--)
	{
		printf("|      |\n");

		/* 스택의 최상위 데이터부터 출력 */
		for (i = s->top; i >= 0; i--)
			printf("|(%01d, %01d)|\n", s->stack[i].r, s->stack[i].c);

		printf("--------\n");
	}
}

int main() // 메인 함수 시작
{
	int r, c; // 현재 좌표를 저장할 변수 선언
	StackType s; // 스택 구조체 선언

	init(&s); // 스택의 초기화

	here = entry; // 현재의 좌표를 시작 좌표로 설정

	/* 출구에 도착할 때 까지 반복하는 반복문 */
	while (maze[here.r][here.c] != 'x')
	{
		r = here.r; // r에 here의 r 데이터 저장
		c = here.c; // c에 here의 c 데이터 저장

		maze[r][c] = '.'; // 지나간 곳을 '.'으로 저장

		/* 4방향의 좌표를 push */
		push_loc(&s, r - 1, c);
		push_loc(&s, r + 1, c);
		push_loc(&s, r, c - 1);
		push_loc(&s, r, c + 1);

		printMaze(); // 미로를 출력
		printStack(&s); // 스택의 데이터 출력

		/* 스택에 데이터가 남아있지 않을 경우 */
		if (is_empty(&s))
		{
			printf("실패\n"); // 미로 찾기 실패
			return 0;
		}

		/* 그렇지 않으면 */
		else
			here = pop(&s); // here에 스택에서 pop한 데이터 저장
	}

	printMaze(); // 미로를 출력
	printStack(&s); // 스택의 데이터 출력

	printf("성공\n"); // 미로 찾기 성공

	return 0; // 메인 함수 종료
}
