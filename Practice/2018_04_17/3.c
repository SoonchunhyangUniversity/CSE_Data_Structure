/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열로 구현된 연결리스트 3
	* 작성일 : 2018 - 04 - 17
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#define MAX 1000 // 기호상수 MAX를 1000으로 정의
#define TRUE 1 // 기호상쉬 TRUE를 1로 정의

typedef int Data; // typedef로 Data 키워드로 int 선언 가능

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
/* 배열 기반 리스트에서 홀수 번째 데이터를 지우는 함수 */
void delete(ArrayBaseList *plist);
/* 배열 기반 리스트에서 배열 안에 값이 있는지 검사하는 함수 */
int is_in(ArrayBaseList *plist, Data find_data);
/* 배열 기반 리스트에서 배열이 가득 차 있는지 검사하는 함수 */
int is_full(ArrayBaseList *plist);
/* 배열 기반 리스트에서 배열이 비어있는지 검사하는 함수 */
int is_empty(ArrayBaseList *plist);

int main() // 메인 함수 시작
{
	ArrayBaseList list; // 배열 기반 리스트 list 구조체 선언
	int i, temp;
	// 반복문에서 사용할 변수, 임시로 값을 저장할 변수 선언
	int input;
	// 사용자에게 입력을 받을 변수 선언

	/* 파일포인터 fp 선언 및 data3.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 읽은데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일을 여는데 실패했으면
	{
		fprintf(stderr, "FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	init(&list); // 배열 기반 리스트를 초기화

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp)) // fp의 끝까지 반복한다.
	{
		fscanf(fp, "%d", &temp); // 임시로 값을 temp에 저장
		Insert(&list, i, temp); // temp에 저장한 값을 배열 기반 리스트에 저장
		i++; // i를 1 더해준다.
	}

	display(&list); // 배열 기반 리스트의 데이터 출력
	printf("\n");
	delete(&list); // 홀수 번째 데이터들을 삭제
	display(&list); // 삭제 후 데이터 출력
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

/* 배열 기반 리스트에서 데이터를 지우는 함수 */
void delete(ArrayBaseList *plist)
{
	int i, j; // 반복문에서 사용할 변수 선언

	for (i = 0; i < (plist->length - 1); i++) // plist의 length - 1번 반복
	{
		if (!(i % 2 == 0)) // 홀수 번째 값이라면
		{
			for (j = i; j < (plist->length - 1); j++) // (plist->length - 1) - i번 반복
			{
				plist->arr[j] = plist->arr[j + 1]; // 배열의 값들을 한자리씩 옮김
			}
			plist->length--; // 값이 삭제되면 length를 1 줄임
		}
	}
}

/* 배열 기반 리스트에서 데이터를 출력하는 함수 */
void display(ArrayBaseList *plist)
{
	int i; // 반복문에서 사용할 변수
	for (i = 0; i < plist->length; i++) // plist의 length번 반복
		printf("%d->", plist->arr[i]); // 리스트의 데이터 출력
}

/* 배열 기반 리스트에서 배열 안에 값이 있는지 검사하는 함수 */
int is_in(ArrayBaseList *plist, Data find_data)
{
	int i; // 반복문에서 사용할 변수

	for (i = 0; i < plist->length; i++) // plist->length번 반복
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
