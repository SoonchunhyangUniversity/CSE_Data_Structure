/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연결리스트 1
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 01
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 사용을 위한 헤더파일 선언

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

/*
	phead : 헤드 포인터의 포인터
	p : 삭제될 노드의 선행 노트
	removed : 삭제될 노드
*/
void remove_node(ListNode **phead, ListNode *p, ListNode *removed)
{
	if (p == NULL) // 선행 노드가 NULL이라면
		*phead = (*phead)->link; // *phead에 (*phead)의 다음 노드 대입

	else // 그렇지 않으면
		p->link = removed->link; // 선행노드의 다음노드에 removed노드의 다음 노드 대입

	free(removed); // removed 노드의 메모리 할당 해제
}

/* 연결 리스트의 데이터를 보여주는 함수 */
void display(ListNode *head)
{
	ListNode *p = head; // 헤드 대신에 사용할 포인터 노드 선언 및 대입

	/* p가 NULL일 때 까지 반복 */
	while (p != NULL)
	{
		printf("%d->", p->data); // 노드의 데이터 출력
		p = p->link; // 다음 노드로 이동
	}

	printf("\n"); // 모두 출력했으면 개행
}

/* 연결 리스트의 재귀적 출력 함수 */
void display_recur(ListNode *head)
{
	ListNode * p = head; // 헤드 대신에 사용할 포인터 노드 선언 및 대입

	if (p != NULL) // p가 NULL이면 탈출
	{
		printf("%d->", p->data); // 노드의 데이터 출력

		display_recur(p->link); // 다음 노드 함수 호출
	}
}

/* 연결 리스트에서 데이터를 찾는 함수 */
ListNode *search(ListNode *head, int x)
{
	ListNode *p; // 헤드 대신에 사용할 포인터 노드 선언
	p = head; // 포인터 노드에 head 대입

	/* p가 NULL일 때 까지 반복 */
	while (p != NULL)
	{
		if (p->data == x) // 값이 존재 하면
			return p; // 탐색 성공

		p = p->link; // 다음 노드로 이동
	}

	return p; // 탐색 실패일 경우 NULL 반환
}

/*
	head1 = (a1, a2, ..., an) head2 = (b1, b2, ..., bn)을
	(a1, ..., an, b1, ..., bn)으로 변환
*/
ListNode *concat(ListNode *head1, ListNode *head2)
{
	ListNode *p; // 헤드 대신에 사용할 포인터 노드 선언

	/* head1에 데이터가 없다면 */
	if (head1 == NULL)
		return head2; // head2 반환

	/* head2에 데이터가 없다면 */
	else if (head2 == NULL)
		return head1; // head1 반환

	else // 둘다 데이터가 있다면
	{
		p = head1; // p에 head1 대입

		/* p의 다음 노드가 없을 때 까지 반복 */
		while (p->link != NULL)
		{
			p = p->link; // p의 다음 노드로 이동
			p->link = head2; // p의 다음 노드에 head2 연결

			return head1; // head1을 반환
		}
	}
}

/* (e1, e2, ... en)을 (en, en-1, ..., e1)로 변환 */
ListNode *reverse(ListNode * head)
{
	// 순회 포인터로 p, q, r을 사용
	ListNode *p, *q, *r;
	p = head; // p는 아직 처리되지 않은 노드
	q = NULL; // q는 역순으로 만들 노드

	while (p != NULL)
	{
		r = q; // r은 역순으로 된 노드
		q = p; // r은 q, q는 p를 차례로 따라간다.
		p = p->link; // p를 다음 노드로 이동
		q->link = r; // q의 링크 방향을 바꾼다.
	}

	return q; // q는 역순으로 된 리스트의 헤드포인터
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

int main() // 메인 함수 시작
{
	/* 연결 리스트의 헤드 list1, list2 선언 및 초기화 */
	ListNode *list1 = NULL, *list2 = NULL;
	ListNode *p; // 탐색한 데이터 노드를 담을 포인터 노드

	// list1 = 30->20->10
	insert_node(&list1, NULL, create_node(10, NULL));
	insert_node(&list1, NULL, create_node(20, NULL));
	insert_node(&list1, NULL, create_node(30, NULL));
	display(list1);

	// list1 = 20->10
	remove_node(&list1, NULL, list1);
	display(list1);

	// list2 = 80->70->60
	insert_node(&list2, NULL, create_node(60, NULL));
	insert_node(&list2, NULL, create_node(70, NULL));
	insert_node(&list2, NULL, create_node(80, NULL));
	display(list2);

	// list1 = list1 + list2
	list1 = concat(list1, list2);
	display(list1);

	// list1을 역순으로
	list1 = reverse(list1);
	display(list1);

	// list1에서 20 탐색
	p = search(list1, 20);
	printf("탐색성공 : %d\n", p->data);

	return 0; // 메인 함수 종료
}
