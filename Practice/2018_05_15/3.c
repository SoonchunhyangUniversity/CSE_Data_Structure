/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 스택 2
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // exit 함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp 함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TURE를 1로 정의
#define FALSE 0 // 기호상수 FALSE를 0으로 정의
#define STACK_LEN 100 // 기호상수 STACK_LEN을 100으로 정의

/* 스택에서 사용할 데이터 구조체 정의 */
typedef struct _data
{
	char name[10]; // 이름을 저장할 문자열
	char phone_num[14]; // 휴대폰 번호를 저장할 문자열
	char gender[3]; // 성별을 저장할 문자열
} Data; // Data키워드로 구조체 선언 가능

/* 배열 기반 스택의 구조체 정의 */
typedef struct _arrayStack
{
	Data stackArr[STACK_LEN]; // 배열 기반 스택의 데이터 배열
	int topIndex; // 스택의 최상위 인덱스 값
} Stack; // Stack키워드로 구조체 선언 가능

		 /* 스택을 초기화 하는 함수 */
void StackInit(Stack * pstack)
{
	pstack->topIndex = -1; // 스택의 topIndex를 -1로 저장
}

/* 스택이 비어있는지 검사하는 함수 */
int SIsEmpty(Stack * pstack)
{
	if (pstack->topIndex == -1) // 스택의 최상위 인덱스가 -1 이면
		return TRUE; // 스택이 비어있으므로 TRUE 반환
	else // 그렇지 않으면
		return FALSE; // FALSE 반환
}

/* 스택에 데이터를 삽입하는 함수 */
void SPush(Stack * pstack, Data data)
{
	pstack->stackArr[++(pstack->topIndex)] = data;
	// 스택의 데이터 배열의 최상위 인덱스 다음 인덱스에 데이터 삽입
}

/* 스택의 최상위 인덱스를 꺼내고 삭제하는 함수 */
Data SPop(Stack * pstack)
{
	int rIdx; // 삭제 할 인덱스를 임시로 저장할 변수

			  /* 스택이 비어있는지 검사 */
	if (SIsEmpty(pstack)) // 스택이 비어있다면
	{
		printf("Stack Memory Error!"); // 예외처리
		exit(-1); // 프로그램 종료
	}

	rIdx = pstack->topIndex; // rIdx에 스택의 최상위 인덱스 저장
	pstack->topIndex -= 1; // 스택의 최상위 인덱스를 1 뺀다.

	return pstack->stackArr[rIdx]; // 스택의 rIdx 데이터 값 반환
}

/* 스택에 있는 데이터로 짝을 찾는 함수 */
void match(Stack *male, Stack *female)
{
	int i = 1; // 몇 번째 쌍인지 확인할 변수 선언 및 초기화
	Data male_temp, female_temp;

	printf("\n");

	/* 두 스택모두 비어있지 않으면 반복 */
	while (!SIsEmpty(male) && !SIsEmpty(female))
	{
		male_temp = SPop(male); // male스택의 최상위 데이터를 임시로 저장
		female_temp = SPop(female); // female스택의 최상위 데이터를 임시로 저장

		printf("<%d호> %s(%s) - %s(%s)\n", i,
			male_temp.name, male_temp.phone_num, female_temp.name, female_temp.phone_num);
		// 짝을 찾아서 데이터를 출력

		i++; // i에 1을 더해준다.
	}

	while (!SIsEmpty(male)) // male 스택이 비어있지 않으면
		printf("%s씨는 짝이없습니다.\n", SPop(male).name); // 출력

	while (!SIsEmpty(female)) // female 스택이 비어있지 않으면
		printf("%s씨는 짝이없습니다.\n", SPop(female).name); // 출력
}

int main() // 메인 함수 시작
{
	Data temp; // 구조체 데이터를 임시로 저장할 구조체 변수 선언
	Stack male, female; // male 스택과 female 스택 선언

						/* 파일 포인터 fp선언 및 data3.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일 오픈에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메시지 출력
		return 0; // 메인 함수 종료
	}

	/* 스택을 초기화 */
	StackInit(&male);
	StackInit(&female);

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %s", temp.name, temp.phone_num, temp.gender);
		// temp 구조체에 임시로 데이터를 저장

		/* temp의 gender요소가 '남'일 경우 */
		if (!strcmp(temp.gender, "남"))
		{
			SPush(&male, temp); // male 스택에 데이터 삽입
			printf("<Push> 남자 - %s\n", temp.name); // 삽입 결과 출력
		}

		/* temp의 gender요소가 '여'일 경우 */
		else
		{
			SPush(&female, temp); // female 스택에 데이터 삽입
			printf("<Push> 여자 - %s\n", temp.name); // 삽입 결과 출력
		}
	}

	match(&male, &female); // match 함수로 데이터 출력

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
