/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 포인터로 구현된 단순 연결 리스트
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 08
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TRUE 1 선언
#define FALSE 0 // 기호상수 FALSE 0 선언

typedef int element; // typedef로 int 키워드 대신 element 키워드 사용 가능

/* 리스트의 노드 구조체 */
typedef struct ListNode
{
	element data; // 정수형 데이터
	struct ListNode *link; // 다음 노드를 가리키는 포인터 구조체
} ListNode; // typedef로 구조체 선언 없이 ListNode 키워드 사용 가능

/* 에러메세지를 출력하는 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message); // 에러메세지 출력
	exit(1); // 프로그램 종료
}

/*
	phead : 리스트의 헤드 포인터의 포인터
	p : 선행 노트
	new_node : 삽입될 노드
*/
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL; // 새 노드의 link에 NULL 저장
		*phead = new_node; // 헤드 포인터에 새 노드 저장
	}

	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead; // 새 노드의 link에 헤드 포인터 저장
		*phead = new_node; // 헤드 포인터에 새 노드 저장
	}

	else
	{
		new_node->link = p->link; // 새 노드의 링크의 p의 link 저장
		p->link = new_node; // p의 링크에 새 노드 저장
	}
}

/* 리스트의 데이터 출력하는 함수 */
void display(ListNode *head)
{
	ListNode *p = head;
	// 헤드 포인터를 대신해서 사용할 변수 선언 및 초기화

	printf("< ");
	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		printf("%d ", p->data); // 데이터 출력
		p = p->link; // 다음 노드로 이동
	}
	printf(">");
	printf("\n");
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node; // 새 노드를 동적 할당할 포인터 노드 선언
	new_node = (ListNode *)malloc(sizeof(ListNode)); // 새 노드 동적 할당

	/* 동적 할당에 실패할 경우 */
	if (new_node == NULL)
		error("메모리 할당 에러"); // 에러메세지 실행

	new_node->data = data; // 새 노드의 데이터에 매개 변수 데이터 저장
	new_node->link = link; // 새 노드의 링크에 매개 변수로 받은 노드 저장

	return (new_node); // 동적 할당한 후 데이터를 저장한 노드를 반환
}

/* 리스트의 가운데 노드를 반환하는 함수 */
ListNode *get_mid_node(ListNode *head, int count)
{
	int i; // 반복문에서 사용할 변수 선언
	ListNode *mid = head; // 가운데 노드를 저장할 포인터 노드 선언 및 초기화

	/* 노드의 개수가 홀수면 */
	if (count % 2 != 0)
	{
		for (i = 0; i < count / 2; i++) // (노드의 개수/2)번 반복
			mid = mid->link; // mid를 다음 노드로 이동
	}

	/* 노드의 개수가 짝수면 */
	else
	{
		for (i = 0; i < count / 2 - 1; i++) // (노드의 개수/2-1)번 반복
			mid = mid->link; // mid를 다음 노드로 이동
	}

	return mid; // 가운데 노드를 반환
}

int main() // 메인 함수 시작
{
	ListNode *list = NULL;
	// 리스트의 헤드 노드 선언 및 초기화
	ListNode *mid = NULL;
	// 리스트의 가운데 노드를 저장 할 구조체 선언 및 초기화
	int data, input;
	// 데이터를 임시로 저장할 변수, 사용자에게 값을 입력 받을 변수 선언
	int data_count = 0;
	// 리스트의 노드의 개수를 저장할 변수 선언 및 초기화

	/* 파일포인터 fp 선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		// fp의 정수형 데이터를 data에 저장
		insert_node(&list, NULL, create_node(data, NULL));
		// 저장한 data를 create_node함수로 노드를 생성한 후 insert_node함수로 list노드에 삽입
		data_count++;
		// 데이터의 개수를 하나 더함
	}

	/* 사용자가 0을 입력할 때 까지 반복 */
	do
	{
		mid = get_mid_node(list, data_count);
		// mid에 get_mid_node함수로 가운데 노드 저장

		display(list); // 리스트의 데이터 출력
		printf("삽입 할 값을 입력하세요( 0 : 종료) : ");
		scanf("%d", &input); // 사용자에게 입력값을 받는다

		/* 사용자의 입력값이 0이면 */
		if (input == 0)
			break; // 반복문 종료

		/* 그렇지 않으면 */
		else
		{
			insert_node(&list, mid, create_node(input, NULL));
			// insert_node 함수로 리스트의 가운데에 input값 노드 저장
			data_count++;
			// 데이터의 개수를 하나 더함
		}

	} while (TRUE); // 무한 루프

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
