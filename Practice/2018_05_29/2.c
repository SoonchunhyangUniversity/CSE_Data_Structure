/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 2
 * 작성일 : 2018 - 05 - 29
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp 함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TRUE를 1로 정의
#define FALSE 0 // 기호상수 FALSE를 0로 정의

int step = 1; // 단계를 저장할 전역변수 선언 및 초기화
int stack1_len; // 스택1의 길이를 저장할 전역 변수 선언
int stack2_len; // 스택2의 길이를 저장할 전역 변수 선언

typedef int Data; // typedef로 Data키워드로 int형 데이터 선언 가능

/* 스택의 노드 구조체 */
typedef struct _node
{
	Data data; // Data형 데이터를 저장할 변수
	struct _node *next; // 다음 노드를 가리킬 포인터
} Node; // Node키워드로 선언 가능

/* 스택의 헤드 구조체 */
typedef struct _listStack
{
	Node *head; // 첫 노드를 가리킬 헤드 포인터
} Stack; // Stack키워드로 선언 가능

/* 스택을 초기화하는 함수 */
void init(Stack *pstack)
{
	pstack->head = NULL; // 스택의 헤드 포인터를 NULL로 초기화
}

/* 스택이 비어있는지 확인하는 함수 */
int is_empty(Stack *pstack)
{
	/* 스택의 헤드 포인터가 NULL인 경우 */
	if (pstack->head == NULL)
		return TRUE; // TRUE 반환

	/* 그렇지 않은 경우*/
	else
		return FALSE; // FALSE 반환
}

/* 스택에 데이터를 삽입하는 함수 */
void push(Stack *stack1, Stack *stack2, int stack_num, Data data)
{
	/* 매개변수로 받은 스택의 번호가 1일 경우 */
	if (stack_num == 1)
	{
		Node *newNode = (Node *)malloc(sizeof(Node)); // 새 노드 동적 할당

		newNode->data = data; // 새 노드에 data 저장
		newNode->next = stack1->head; // 새 노드의 다음 노드에 헤드 노드 저장
		stack1->head = newNode; // 스택의 헤드를 새 노드로 저장
		stack1_len++; // 스택의 길이를 1 더해줌
	}

	/* 스택의 번호가 1이 아닐 경우 */
	else
	{
		Node *newNode = (Node *)malloc(sizeof(Node)); // 새 노드 동적 할당

		newNode->data = data; // 새 노드에 data 저장
		newNode->next = stack2->head; // 새 노드의 다음 노드에 헤드 노드 저장
		stack2->head = newNode; // 스택의 헤드를 새 노드로 저장
		stack2_len++; // 스택의 길이를 1 더해줌
	}
}

/* 스택의 POP 함수 */
Data pop(Stack *stack1, Stack *stack2, int stack_num)
{
	Data rdata; // 지워지는 데이터를 저장할 변수 선언
	Node *rnode; // 지워지는 노드를 저장할 포인터 선언

	/* 매개변수로 받은 스택의 번호가 1일 경우 */
	if (stack_num == 1)
	{
		/* 스택이 비어있을 경우 */
		if (is_empty(stack1))
		{
			printf("Stack Memory Error!"); // 에러 메세지 출력
			exit(-1); // 프로그램 종료
		}

		rdata = stack1->head->data; // rdata에 헤드 포인터의 노드의 data저장
		rnode = stack1->head; // rnode에 헤드 포인터가 가리키는 노드 저장
		stack1->head = stack1->head->next; // 헤드 포인터가 다음 노드를 가리키게 함
		free(rnode); // rnode의 동적 할당 해제
		stack1_len--; // 스택의 길이를 1 줄여줌
	}

	/* 스택의 번호가 1이 아닐 경우 */
	else
	{
		/* 스택이 비어있을 경우 */
		if (is_empty(stack2))
		{
			printf("Stack Memory Error!"); // 에러 메세지 출력
			exit(-1); // 프로그램 종료
		}

		rdata = stack2->head->data; // rdata에 헤드 포인터의 노드의 data저장
		rnode = stack2->head; // rnode에 헤드 포인터가 가리키는 노드 저장
		stack2->head = stack2->head->next; // 헤드 포인터가 다음 노드를 가리키게 함
		free(rnode); // rnode의 동적 할당 해제
		stack2_len--; // 스택의 길이를 1 줄여줌
	}

	return rdata; // 삭제된 데이터를 반환
}

/* 스택에 데이터가 Push되었을 때 스택의 데이터를 출력하는 함수 */
void display_push(Stack *stack1, Stack *stack2, int stack_num, Data data)
{
	Node *stack1_temp, *stack2_temp;
	// 스택의 헤드 포인터가 가리키는 노드 대신 사용 할 변수 선언
	int stack1_display_count, stack2_display_count;
	// 몇 번 데이터가 출력되어야 하는지 저장할 변수 선언

	stack1_temp = stack1->head; // stack1_temp에 스택1의 헤드 노드 저장
	stack2_temp = stack2->head; // stack2_temp에 스택2의 헤드 노드 저장

	printf("---Step %d : 스택%d %d 입력 ---\n", step++, stack_num, data);

	/* 스택1의 길이가 스택2의 길이보다 클 경우 */
	if (stack1_len > stack2_len)
	{
		/* 출력 카운트를 스택1의 길이로 저장 */
		stack1_display_count = stack1_len;
		stack2_display_count = stack1_len;
	}

	/* 스택2의 길이가 스택1의 길이보다 클 경우 */
	else
	{
		/* 출력 카운트를 스택2의 길이로 저장 */
		stack1_display_count = stack2_len;
		stack2_display_count = stack2_len;
	}

	/* 출력 카운트가 둘다 0이 될 때 까지 반복 */
	while (stack1_display_count > 0 && stack2_display_count > 0)
	{
		/* 출력 카운트 수 보다 스택의 길이가 작을 경우 */
		if (stack1_display_count > stack1_len)
			printf("│         │"); // 비어있는 스택 출력

		/* 스택의 길이보다 같거나 작은 경우 */
		else
		{
			printf("│ < %3d > │", stack1_temp->data); // 스택의 데이터 출력
			stack1_temp = stack1_temp->next; // 다음 노드를 가리킴
		}

		/* 출력 카운트 수 보다 스택의 길이가 작을 경우 */
		if (stack2_display_count > stack2_len)
			printf("│         │\n"); // 비어있는 스택 출력

		/* 스택의 길이보다 같거나 작은 경우 */
		else
		{
			printf("│ < %3d > │\n", stack2_temp->data); // 스택의 데이터 출력
			stack2_temp = stack2_temp->next; // 다음 노드를 가리킴
		}

		/* 출력 카운트를 1빼줌 */
		stack1_display_count--;
		stack2_display_count--;
	}

	printf("└─────────┘└─────────┘\n\n");
}

/* 스택에 데이터가 Pop되었을 때 스택의 데이터를 출력하는 함수 */
void display_pop(Stack *stack1, Stack *stack2, int stack_num, int rdata)
{
	Node *stack1_temp, *stack2_temp;
	// 스택의 헤드 포인터가 가리키는 노드 대신 사용 할 변수 선언
	int stack1_display_count, stack2_display_count;
	// 몇 번 데이터가 출력되어야 하는지 저장할 변수 선언

	stack1_temp = stack1->head; // stack1_temp에 스택1의 헤드 노드 저장
	stack2_temp = stack2->head; // stack2_temp에 스택2의 헤드 노드 저장

	printf("---Step %d : 스택%d %d 삭제 ---\n", step++, stack_num, rdata);

	/* 스택1의 길이가 스택2의 길이보다 클 경우 */
	if (stack1_len > stack2_len)
	{
		/* 출력 카운트를 스택1의 길이로 저장 */
		stack1_display_count = stack1_len;
		stack2_display_count = stack1_len;
	}

	/* 스택2의 길이가 스택1의 길이보다 클 경우 */
	else
	{
		/* 출력 카운트를 스택2의 길이로 저장 */
		stack1_display_count = stack2_len;
		stack2_display_count = stack2_len;
	}

	/* 출력 카운트가 둘다 0이 될 때 까지 반복 */
	while (stack1_display_count > 0 && stack2_display_count > 0)
	{
		/* 출력 카운트 수 보다 스택의 길이가 작을 경우 */
		if (stack1_display_count > stack1_len)
			printf("│         │"); // 비어있는 스택 출력

		/* 스택의 길이보다 같거나 작은 경우 */
		else
		{
			printf("│ < %3d > │", stack1_temp->data); // 스택의 데이터 출력
			stack1_temp = stack1_temp->next; // 다음 노드를 가리킴
		}

		/* 출력 카운트 수 보다 스택의 길이가 작을 경우 */
		if (stack2_display_count > stack2_len)
			printf("│         │\n"); // 비어있는 스택 출력

		/* 스택의 길이보다 같거나 작은 경우 */
		else
		{
			printf("│ < %3d > │\n", stack2_temp->data); // 스택의 데이터 출력
			stack2_temp = stack2_temp->next; // 다음 노드를 가리킴
		}

		/* 출력 카운트를 1빼줌 */
		stack1_display_count--;
		stack2_display_count--;
	}

	printf("└─────────┘└─────────┘\n\n");
}

int main() // 메인 함수 시작
{
	Stack s1, s2;
	// 스택1, 스택2 선언
	Data data;
	// 파일에서 받아온 데이터를 저장 할 변수 선언
	int stack_num, rdata;
	// 스택의 번호를 저장 할 변수와, 지워지는 데이터를 저장할 변수 선언
	char oper[5] = { 0 };
	// 연산자를 저장 할 문자열 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기모드로 염 */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n"); // 에러 메세지 출력
		exit(-1); // 프로그램 종료
	}

	/* 스택의 초기화 */
	init(&s1);
	init(&s2);

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %d", oper, &stack_num); // 파일에서 연산자와 스택의 번호를 입력

		/* 연산자가 push일 경우 */
		if (!strcmp(oper, "push"))
		{
			fscanf(fp, "%d", &data); // 파일에서 data 입력

			/* 스택 번호가 1일 경우 */
			if(stack_num == 1)
				push(&s1, &s2, stack_num, data); // 스택 1에 data push

			/* 스택 번호가 2일 경우 */
			else if (stack_num == 2)
				push(&s1, &s2, stack_num, data); // 스택 2에 data push

			display_push(&s1, &s2, stack_num, data); // 스택의 상태 출력
		}

		/* 연산자가 pop일 경우 */
		else if (!strcmp(oper, "pop"))
		{
			/* 스택 번호가 1일 경우 */
			if (stack_num == 1)
				rdata = pop(&s1, &s2, stack_num); // rdata에 스택 1의 pop데이터 저장

			/* 스택 번호가 2일 경우 */
			else if (stack_num == 2)
				rdata = pop(&s1, &s2, stack_num); // rdata에 스택 2의 pop데이터 저장

			display_pop(&s1, &s2, stack_num, rdata); // 스택의 상태 출력
		}

		/* 잘못된 연산자가 들어왔을 경우 */
		else
		{
			printf("Operator Error!\n"); // 에러 메세지 출력
			return 0; // 메인 함수 종료
		}
	}

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
