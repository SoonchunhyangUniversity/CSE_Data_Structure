/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 스택 2
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define STACK_LEN 100

typedef struct _data
{
	char name[10];
	char phone_num[14];
	char gender[3];
} Data;

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
/* 스택의 출력 함수 */
void match(Stack *male, Stack *female);

int main()
{
	Data temp;
	Stack male, female;
	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	StackInit(&male);
	StackInit(&female);

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s", temp.name, temp.phone_num, temp.gender);

		if (!strcmp(temp.gender, "남"))
		{
			SPush(&male, temp);
			printf("<Push> 남자 - %s\n", temp.name);
		}
		else
		{
			SPush(&female, temp);
			printf("<Push> 여자 - %s\n", temp.name);
		}
	}

	printf("\n");
	match(&male, &female);

	return 0;
}

void match(Stack *male, Stack *female)
{
	int i = 1;
	Data male_temp, female_temp;

	while (!SIsEmpty(male) && !SIsEmpty(female))
	{
		male_temp = SPop(male);
		female_temp = SPop(female);
		printf("<%d호> %s(%s) - %s(%s)\n", i, male_temp.name, male_temp.phone_num, female_temp.name, female_temp.phone_num);
		i++;
	}

	if (!SIsEmpty(male))
		printf("%s씨는 짝이없습니다.\n", male->stackArr[male->topIndex].name);

	if(!SIsEmpty(female))
		printf("%s씨는 짝이없습니다.\n", female->stackArr[female->topIndex].name);
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
