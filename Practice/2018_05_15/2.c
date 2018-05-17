/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 스택 1
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef int Data;

typedef struct _arrayStack
{
	Data stackArr[STACK_LEN];
	int topIndex;
} ArrayStack;

typedef ArrayStack Stack;

/* 스택의 초기화 */
void StackInit(Stack * pstack);
/* 스택이 비었는지 확인 */
int SIsEmpty(Stack * pstack);
/* 스택의 push 연산 */
void SPush(Stack * pstack, Data data);
/* 스택의 pop 연산 */
Data SPop(Stack * pstack);
/* 스택의 peek 연산 */
Data SPeek(Stack * pstack);

int main()
{
	/* Stack의 생성 및 초기화 */
	Stack stack;
	int temp_data, temp_arr[STACK_LEN];
	int a_pop_data, b_pop_data;
	int a_win_count = 0, b_win_count = 0;
	int i, j;

	srand((unsigned)time(NULL));

	StackInit(&stack);

	for (i = 0; i < 10; i++)
	{

		if (i == 0)
		{
			temp_data = rand() % 20 + 1;

			SPush(&stack, temp_data);
			temp_arr[i] = temp_data;
		}

		else
		{
			temp_data = rand() % 20 + 1;

			for (j = 0; j < stack.topIndex + 1; j++)
			{
				if (temp_arr[j] == temp_data)
				{
					temp_data = rand() % 20 + 1;
					j = 0;

					continue;
				}
			}

			SPush(&stack, temp_data);
			temp_arr[i] = temp_data;
		}
	}



	/* 데이터 꺼내기 */
	for (i = 0; i < 5; i++)
	{
		a_pop_data = SPop(&stack);
		b_pop_data = SPop(&stack);

		printf("< %d회차 >\n", i + 1);
		printf("A : %-3d - B : %-3d\n", a_pop_data, b_pop_data);

		if (a_pop_data > b_pop_data)
			a_win_count++;

		else if (b_pop_data > a_pop_data)
			b_win_count++;
	}

	printf("\n< 승 패 >\n");
	printf("A - 승 : %-3d\t 패 : %-3d\n", a_win_count, 5 - a_win_count);
	printf("B - 승 : %-3d\t 패 : %-3d\n", b_win_count, 5 - b_win_count);

	return 0;
}


void StackInit(Stack * pstack)
{
	pstack->topIndex = -1;
}

int SIsEmpty(Stack * pstack)
{
	if (pstack->topIndex == -1)
		return TRUE;
	else
		return FALSE;
}

void SPush(Stack * pstack, Data data)
{
	pstack->topIndex += 1;
	pstack->stackArr[pstack->topIndex] = data;
}

Data SPop(Stack * pstack)
{
	int rIdx;

	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	rIdx = pstack->topIndex;
	pstack->topIndex -= 1;

	return pstack->stackArr[rIdx];
}

Data SPeek(Stack * pstack)
{
	if (SIsEmpty(pstack))
	{
		printf("Stack Memory Error!");
		exit(-1);
	}

	return pstack->stackArr[pstack->topIndex];
}
