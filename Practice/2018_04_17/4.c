/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열로 구현된 연결리스트 4
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 17
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc 함수를 사용하기 위한 헤더파일 선언
#define MAX 1000 // 기호상수 MAX를 1000으로 정의
#define TRUE 1 // 기호상수 TRUE를 1로 정의

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
void Insert(ArrayBaseList *plist, int position, Data data);
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
	ArrayBaseList *list; // 배열 기반 리스트 포인터 변수 선언(동적 할당)
	ArrayBaseList struct_temp; // 임시로 구조체를 저장할 구조체 변수 선언
	int i, j, temp, count = 0;
	// 반복문에서 사용할 변수, 임시로 값을 저장할 변수, 데이터의 개수를 저장할 변수 선언
	int input;
	// 사용자에게 입력을 받을 변수 선언

	/* 파일포인터 fp 선언 및 data4.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data4.txt", "r");

	/* 파일을 읽은데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일을 여는데 실패했으면
	{
		fprintf(stderr, "FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp)) // fp의 끝까지 반복한다.
	{
		fscanf(fp, "%d %d %d %d", &temp, &temp, &temp, &temp); // 파일의 데이터를 임시로 저장
		count++; // count를 1 더해준다.
	}

	list = (ArrayBaseList *)malloc(sizeof(ArrayBaseList) * count); // 파일의 개수로 구조체 동적 할당

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 동적 할당한 배열 기반 리스트들을 초기화하는 반복문 */
	for (i = 0; i < count; i++) // count번 반복
		init(&list[i]); // 배열 기반 리스트들을 초기화

	/* 파일에서 가져온 데이터를 배열 기반 리스트에 저장 */
	for (i = 0; i < count; i++) // count번 반복
	{
		for (j = 0; j < 4; j++) // 4번 반복, 학번, 국어, 영어, 수학
		{
			fscanf(fp, "%d", &temp); // 파일 안의 데이터를 temp에 저장
			Insert(&list[i], j, temp); // 배열 기반 리스트에 temp에 저장된 데이터 삽입
		}
		list[i].arr[list[i].length] = (list[i].arr[1] + list[i].arr[2] + list[i].arr[3]);
		// 배열 기반 리스트에 저장한 국어, 영어, 수학 점수로 합을 저장
		list[i].length++;
		// 배열 기반 리스트의 length를 1 더해준다.
	}

	/* 정렬전 배열 기반 리스트의 데이터 출력*/
	printf("Before Sorting!!\n");
	printf("학번\t\t 국어\t 영어\t 수학\t 총점\t 평균\n");
	for (i = 0; i < count; i++) // count번 반복
		display(&list[i]); // 배열 기반 리스트의 데이터 출력

	printf("\n");;

	struct_temp = list[0]; // 정렬을 할 때 사용할 변수에 첫 번째 배열 기반 리스트 저장

	/* 배열 기발 리스트의 데이터를 버블 소팅 */
	for (i = 0; i < count; i++) // count번 반복
	{
		for (j = i; j < count; j++) // count번 반복
		{
			if (list[i].arr[4] < list[j].arr[4]) // 합을 기준으로 비교
			{
				struct_temp = list[i]; // temp에 list[i] 저장
				list[i] = list[j]; // list[i]에 list[j] 저장
				list[j] = struct_temp; // list[j]에 temp에 저장한 list[i] 저장
			}
		}
	}

	/* 정렬 후 배열 기반 리스트의 데이터 출력 */
	printf("After Sorting!!\n");
	printf("학번\t\t 국어\t 영어\t 수학\t 총점\t 평균\n");
	for (i = 0; i < count; i++) // count번 반복
		display(&list[i]); // 배열 기반 리시트의 데이터 출력

	free(list); // 동적 할당한 메모리 할당 해제

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

/* 배열 기반 리스트에서 데이터를 출력하는 함수 */
void display(ArrayBaseList *plist)
{
	int i; // 반복문에서 사용할 변수
	double avg; // 평균을 저장할 변수

	for (i = 0; i < plist->length; i++) // plist->length번 반복
	{
		printf("%d\t", plist->arr[i]); // 리스트의 값을 출력
	}
	printf("%.2f\t\n", (double)plist->arr[4] / 3); // 평균 값을 출력
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
