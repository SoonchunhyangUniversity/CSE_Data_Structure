/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연결리스트 2
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 01
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <time.h> // srand 함수 사용을 위한 헤더파일 선언

typedef int element; // element 키워드로 int형 정수 선언 가능

/* 연결리스트의 노드 구조체 */
typedef struct ListNode
{
	element data; // 데이터
	struct ListNode *link; // 다음 노드를 가리키는 포인터 구조체
} ListNode; // ListNode 키워드로 선언 가능

/* 에러 출력 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
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
		new_node->link = NULL; // new_node의 다음 노드를 NULL로 대입
		*phead = new_node; // *phead에 new_node를 대입
	}

	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead; // new_node의 다음 노드를 *phead로 대입
		*phead = new_node; // *phead에 new_node 대입
	}

	else // 둘 다 아니면
	{
		new_node->link = p->link; // new_node의 다음 노드에 p의 다음 노드 대입
		p->link = new_node; // p의 다음 노드에 new_node 대입
	}
}

/* 연결 리스트의 데이터를 보여주는 함수 */
void display(ListNode *head)
{
	ListNode *p = head; // 헤드 대신에 사용할 포인터 노드 선언 및 대입

	/* p가 NULL일 때 까지 반복 */
	while (p != NULL)
	{
		printf("< %d >", p->data); // 노드의 데이터 출력
		p = p->link; // 다음 노드로 이동
	}
	printf("\n"); // 모두 출력했으면 개행
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node; // 데이터를 담을 노드 선언
	new_node = (ListNode *)malloc(sizeof(ListNode)); // 노드의 동적 할당

	/* 동적 할당에 실패 했을 경우 */
	if (new_node == NULL)
		error("메모리 할당 에러"); // 예외 처리

	new_node->data = data; // new_node의 데이터에 data 대입
	new_node->link = link; // new_node에 다음 노드에 link 대입

	return (new_node); // 동적 할당 후 데이터를 담은 노드 반환
}

/* 데이터를 교환하는 함수 */
void swap(ListNode *a, ListNode *b)
{
	int temp = a->data; // temp에 노드 a의 데이터 대입
	a->data = b->data; // 노드 a의 데이터에 노드 b의 데이터 대입
	b->data = temp; // 노드 b의 데이터에 temp 대입
}

/* 데이터를 정렬하는 함수 */
void sort(ListNode *phead)
{
	int check = 1; // 반복 조건을 체크하는 변수 선언 및 초기화
	ListNode *current; // 현재 노드를 가리킬 포인터 노드
	ListNode *follow = NULL; // 선행 노드를 가리킬 포인터 노드

	/* 데이터가 존재하지 않으면 */
	if (phead == NULL)
		return; // 함수 종료

	/* check가 0이 될 때 까지 반복 */
	while(check)
	{
		check = 0; // check에  0 대입
		current = phead; // node에 phead 대입

		/* 현재 노드의 다음 노드가 선행노드와 같지않으면 반복 */
		while (current->link != follow)
		{
			/* 현재 노드의 데이터가 선행 노드의 데이터 보다 크다면 */
			if (current->data > current->link->data)
			{
				swap(current, current->link); // 데이터의 교환
				check = 1; // check에 1 대입
			}

			current = current->link; // 다음 노드로 이동
		}

		follow = current; // 선행 노드에 현재 노드 대입
	}
}

int main() // 메인 함수 시작
{
	int num; // 갯수를 입력 받을 변수 선언
	int i; // 반복문에서 사용할 변수 선언
	ListNode *list = NULL; // 노드를 연결할 헤드 포인터 노드

	/* 난수 생성을 위하여 srand함수 사용 */
	srand((unsigned)time(NULL));

	printf("생성할 노드의 갯수를 입력하세요 : ");
	scanf("%d", &num); // 사용자에게 값을 입력 받는다.
	printf("\n");

	/* 입력값 num 만큼 반복 */
	for(i = 0; i < num; i++)
		insert_node(&list, NULL, create_node(rand() % 100 + 1, NULL));
		// rand함수로 1 부터 100 사이의 값 생성후 노드 생성 후 대입

	printf("생성된 리스트\n");
	display(list); // 정렬 전 리스트 출력
	printf("\n");

	printf("정렬된 리스트\n");
	sort(list); // 리스트를 정렬
	display(list); // 정렬 후 리스트 출력

	return 0; // 메인 함수 종료
}
