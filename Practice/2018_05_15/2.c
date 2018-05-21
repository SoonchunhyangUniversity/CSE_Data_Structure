/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 스택 1
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // rand함수 사용을 위한 해더파일 선언
#include <time.h> // srand함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TRUE를 1으로 정의
#define FALSE 0 // 기호상수 FALSE를 0으로 정의
#define STACK_LEN 100 // 기호상수 STACK_LEN을 100으로 정의

typedef int Data; // typedef로 Data키워드로 int형 데이터 선언 가능

/* 배열 기반 스택의 스택 구조체 */
typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	// 정수형 데이터를 저장하는 STACK_LEN길이의 배열
	int topIndex;
	// 스택의 최상위 인덱스의 값
} Stack; // typedef로 Stack 키워드로 선언 가능

/* 스택을 초기화 하는 함수 */
void StackInit(Stack * pstack)
{
	pstack->topIndex = -1; // 스택의 최상위 인덱스 값을 -1로 저장
}

/* 스택이 비어있는지 검사하는 함수 */
int SIsEmpty(Stack * pstack)
{
	/* 스택의 최상위 인덱스가 -1이면 */
	if (pstack->topIndex == -1)
		return TRUE; // TRUE 반환

	/* 그렇지 않으면 */
	else
		return FALSE; // FALSE 반환
}

/* 스택에 데이터를 삽입하는 함수 */
void SPush(Stack * pstack, Data data)
{
	pstack->stackArr[++(pstack->topIndex)] = data;
	// 스택에 배열의 topIndex 다음 인덱스에 값을 삽입한다.
}

/* 스택의 맨 위 데이터를 꺼내는 함수 */
Data SPop(Stack * pstack)
{
	int rIdx; // 사라질 인덱스를 임시로 저장할 변수

	/* 스택이 비어있는지 확인 */
	if (SIsEmpty(pstack)) // 비어있다면
	{
		printf("Stack Memory Error!"); // 에러 메세지 출력
		exit(-1); // 프로그램 종료
	}

	rIdx = (pstack->topIndex)--; // rIdx에 스택의 topIndex저장 후 1을 뺸다.

	return pstack->stackArr[rIdx]; // 스택의  rIdx번째 데이터 반환
}

/* 스택의 맨 위 데이터를 확인하는 함수 */
Data SPeek(Stack * pstack)
{
	/* 스택이 비어있는지 확인 */
	if (SIsEmpty(pstack)) // 비어있다면
	{
		printf("Stack Memory Error!"); // 에러 메세지 출력
		exit(-1); // 프로그램 종료
	}

	return pstack->stackArr[pstack->topIndex]; // 스택에 배열의 topIndex번째 값 반환
}

/* 스택에 랜덤한 데이터를 삽입하는 함수 */
void push_rand_data(Stack *pstack)
{
	int i, j; // 반복문에서 사용할 변수
	int temp_data; // 랜덤으로 생성한 값을 저장할 변수
	int temp_arr[STACK_LEN]; // 값 중복을 방지하기 위한 배열 선언

	/* 10번 반복하는 반복문 */
	for (i = 0; i < 10; i++)
	{
		/* 스택의 처음 데이터 라면 */
		if (i == 0)
		{
			temp_data = rand() % 20 + 1; // 1 ~ 20 사이 난수 생성

			SPush(pstack, temp_data); // 스택에 데이터 삽입
			temp_arr[i] = temp_data; // temp_arr에 데이터 삽입
		}

		/* 스택의 처음 데이터가 아니라면 */
		else
		{
			temp_data = rand() % 20 + 1; // 1~ 20 사이 난수 생성

			/* 스택에 저장된 데이터 수 만큼 반복하는 반복문 */
			for (j = 0; j < pstack->topIndex + 1; j++)
			{
				/* temp_arr에 중복되는 값이 있다면 */
				if (temp_arr[j] == temp_data)
				{
					temp_data = rand() % 20 + 1; // 난수 재생성
					j = -1; // j를 -1으로 저장 반복문 처음부터 다시
				}
			}

			SPush(pstack, temp_data); // 스택에 데이터 삽입
			temp_arr[i] = temp_data; // temp_arr에 데이터 삽입
		}
	}
}

/* 숫자 게임을 진행하는 함수 */
void num_game(Stack *pstack)
{
	int i;
	// 반복문에서 사용할 변수 선언
	int a_pop_data, b_pop_data;
	// 스택에서 꺼내온 데이터를 임시로 저장할 변수 선언
	int a_win_count = 0, b_win_count = 0;
	// 숫자 게임에서 이긴 횟수를 저장할 변수 선언 및 초기화

	/* 5번 반복하는 반복문 */
	for (i = 0; i < 5; i++)
	{
		a_pop_data = SPop(pstack); // 스택의 데이터를 꺼내 a_pop_data에 저장
		b_pop_data = SPop(pstack); // 스택의 데이터를 꺼내 b_pop_data에 저장

		/* 회차 정보와 꺼내온 데이터 출력 */
		printf("< %d회차 >\n", i + 1);
		printf("A : %-3d - B : %-3d\n", a_pop_data, b_pop_data);

		/* a의 데이터가 더 크다면 */
		if (a_pop_data > b_pop_data)
			a_win_count++; // a의 승리 횟수를 1 더해준다.

		/* b의 데이터가 더 크다면 */
		else
			b_win_count++; // b의 승리 횟수를 1 더해준다.
	}

	/* 승패 결과를 출력 */
	printf("\n< 승 패 >\n");
	printf("A - 승 : %-3d\t 패 : %-3d\n", a_win_count, 5 - a_win_count);
	printf("B - 승 : %-3d\t 패 : %-3d\n", b_win_count, 5 - b_win_count);
}

int main() // 메인 함수 시작
{
	/* Stack의 생성 */
	Stack stack;

	/* 난수 생성을 위한 시드값 생성 */
	srand((unsigned)time(NULL));

	/* 스택을 초기화 */
	StackInit(&stack);

	/* stack에 데이터를 삽입 */
	push_rand_data(&stack);

	/* 숫자 게임을 진행 */
	num_game(&stack);

	return 0; // 메인 함수 종료
}
