/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열로 구현된 연결리스트 1
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 17
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <time.h> // srand 함수를 사용하기 위한 헤더파일 선언
#include <stdlib.h> // malloc 함수를 사용하기 위한 헤더파일 선언
#define MAX 1000 // 기호상수 MAX를 1000으로 정의
#define TRUE 1 // 기호상쉬 TRUE를 1로 정의

typedef int Data; // typedef로 Data형으로 int 선언 가능

/* 배열 기반 연결 리스트의 typedef 선언 */
typedef struct _arraybaselist
{
	Data arr[MAX]; // 데이터를 저장할 배열
	int length; // 배열 기반 리스트의 길이
} ArrayBaseList; // 구조체 선언을 하지않고 ArrayBaseList로 선언 가능

/* 배열 기반 구조체를 초기화하는 함수 */
void init(ArrayBaseList *plist);
/* 배열 기반 구조체의 데이터 삽입 함수 */
void Insert(ArrayBaseList *plist,int position, Data data);
/* 배열 기반 리스트에서 데이터를 출력하는 함수 */
void display(ArrayBaseList *plist);
/* 배열 기반 리스트에서 데이터를 지우는 함수 */
Data delete(ArrayBaseList *plist, int position);
/* 배열 기반 리스트에서 배열 안에 값이 있는지 검사하는 함수 */
int is_in(ArrayBaseList *plist, Data find_data);
/* 배열 기반 리스트에서 배열이 가득 차 있는지 검사하는 함수 */
int is_full(ArrayBaseList *plist);
/* 배열 기반 리스트에서 배열이 비어있는지 검사하는 함수 */
int is_empty(ArrayBaseList *plist);

int main() // 메인 함수 시작
{
	ArrayBaseList list; // 배열 기반 리스트 list 구조체 선언
	int test_case, i;
	// 사용자에게 값을 입력받을 변수 test_case와 반복문에서 사용할 변수 i 선어

	/* srand함수를 사용하여 난수를 생성할 때 시드값을 준다 */
	srand((unsigned)time(NULL));

	printf("생성할 랜덤 숫자 개수를 입력하세요 : ");
	scanf("%d", &test_case); // 생성 할 난수의 개수를 입력 받는다.

	init(&list); // 배열 기반 리스트를 초기화 한다.

	/* 입력 받은 test_case만큼 반복하여 배열 기반 리스트에 값을 저장 */
	for (i = 0; i < test_case; i++) // test_case번 반복
	{
		Insert(&list, i, (rand() % 999 + 1));
		// Insert 함수를 이용해 list에 i번째에 난수 저장
	}
	printf("[ 배열로 구현된 연결리스트에 추가된 데이터 ]\n");
	display(&list); // display 함수를 이용해 list의 값 출력
	printf("\n");

	return 0; // 메인 함수 종료
}

/* 배열 기반 구조체를 초기화하는 함수 */
void init(ArrayBaseList *plist)
{
	plist->length = 0; // 파라미터로 받은 plist의 lenth를 0으로 초기화
}

/* 배열 기반 구조체의 데이터 삽입 함수 */
void Insert(ArrayBaseList *plist,int position, Data data)
{
	/* 배열 기반 구조체에 데이터를 넣은 수 있는 알맞은 위치인지 확인 */
	if (!is_full(plist) && (position >= 0) && (position <= plist->length))
	{
		int i; // 반복문에서 사용하는 변수 선언
		for (i = (plist->length - 1); i >= position; i--) // 배열의 끝에서 넣을 위치까지 반복
			plist->arr[i + 1] = plist->arr[i]; // 배열의 값을 하나씩 이동

		plist->arr[position] = data; // 배열의 position위치에 데이터 저장
		plist->length++; // 리스트의 length를 1 더한다.
	}
}

/* 배열 기반 리스트에서 데이터를 출력하는 함수 */
void display(ArrayBaseList *plist)
{
	int i, j; // 반복문에서 사용할 변수 선언
	int check = 0; // 최댓값 최솟값을 출력할 때 사용할 변수 선언 및 초기화
	int max = plist->arr[0]; // 최댓값을 리스트의 처음 값으로 지정
	int min = plist->arr[0]; // 최솟값을 리스트의 처음 값을 지정

	/* 배열에서 최댓값 최솟값을 판별하는 중첩 반복문 */
	for (i = 0; i < plist->length; i++) // plist의 length번 반복
	{
		for (j = 0; j < plist->length; j++) // plist의 length번 반복
		{
			if (max < plist->arr[i]) // 값의 크기를 판별
				max = plist->arr[i]; // 리스트의 값이 크다면 최댓값에 저장
			if (min > plist->arr[i]) // 값의 크기를 판별
				min = plist->arr[i]; // 리스트의 값이 작다면 최댓값에 저장
		}
	}

	/* 데이터를 출력하는 중첩 반복문 */
	for (i = 0; i < plist->length; i++) // plsit의 length번 반복
	{
		printf("%3d\t", plist->arr[i]); // 값 출력

		if ((i + 1) % 15 == 0 && i != 0) // 15개의 값이 출력되면 실행
		{
			while (TRUE) // 최댓값 최솟값을 출력하는 반복문
			{
				if (plist->arr[check] == max) // 리스트의 값이 최댓값과 같으면
					printf("MAX\t"); // MAX 출력
				else if (plist->arr[check] == min) // 리스트의 값이 최솟값과 같으면
					printf("MIN\t"); // MIN 출력
				else // 최댓값과 최솟값이 아니면
					printf("\t"); // 탭 출력

				check++; // check를 1 더해준다.

				if (check % 15 == 0) // 공백, 최대, 최소의 값이 15개(한 줄) 출력되면
				{
					printf("\n"); // 개행
					break;
				}
			}
		}
	}
}

/* 배열 기반 리스트에서 데이터를 지우는 함수 */
Data delete(ArrayBaseList *plist, int position)
{
	int i; // 반복문에서 사용할 변수
	Data item; // int형 데이터 item 선언

	/* 데이터를 지울수 없는 위치일 경우 */
	if (position < 0 || position >= plist->length)
		printf("ERROR!\n"); // 에러메세지 출력

	item = plist->arr[position]; // item에 지울 값을 저장

	for (i = position; i < (plist->length - 1); i++) // position에서 값의 끝까지 반복
		plist->arr[i] = plist ->arr[i + 1]; // 데이터를 하나씩 이동

	plist->length--; // 리스트의 length를 1 뺀다.

	return item; // 지워지는 데이터인 item을 반환
}

/* 배열 기반 리스트에서 배열 안에 값이 있는지 검사하는 함수 */
int is_in(ArrayBaseList *plist, Data find_data)
{
	int i; // 반복문에서 사용할 변수

	for (i = 0; i < MAX; i++) // 배열의 처음부터 끝까지 반복
	{
		if (plist->arr[i] == find_data) // 배열에서 값이 있는지 찾는다.
			return i; // 값이 존재하면 그 idx값 반환
	}

	return -1; // 없다면 -1을 반환
}

/* 배열 기반 리스트에서 배열이 가득 차 있는지 검사하는 함수 */
int is_full(ArrayBaseList *plist)
{
	return plist->length == MAX;
	// 리스트의 길이가 MAX와 같으면 배열이 가득 차있으므로 true 반환 그렇지 않으면 false 반환
}

/* 배열 기반 리스트에서 배열이 비어있는지 검사하는 함수 */
int is_empty(ArrayBaseList *plist)
{
	return plist->length == 0;
	// 리스트의 길이가 0이면 배열이 비어있으므로 true 반환 그렇지 않으면 false 반환
}
