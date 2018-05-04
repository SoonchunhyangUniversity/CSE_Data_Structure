/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연결리스트 3
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

/* 홀수번 째 노드만 삭제하는 함수 */
void remove_odd_node(ListNode **phead)
{
	ListNode *ph = *phead; // 포인터 헤드 대신에 사용할 변수 선언 및 대입
	ListNode *prev = NULL; // 이전 노드를 가리킬 변수 선언 및 초기화
	int count = 0; // 몇 번째 데이터인지 확인할 변수 선언 및 초기화

	/* ph가 NULL일 때 까지 반복 */
	while (ph != NULL)
	{
		/* 홀수번 째 노드 이면 */
		if (count % 2 == 0) // 0부터 시작 했기 때문에 짝수 -> 홀수
		{
			remove_node(phead, prev, ph); // 데이터 삭제

			if (prev != NULL) // prev 노드가 NULL이 아니면
				ph = prev->link; // ph에 prev 다음 노드 대입

			else // 그렇지 않으면
				ph = *phead; // ph에 *phead 대입
		}

		/* 짝수번 째 노드 이면 */
		else
		{
			prev = ph; // prev에 ph 대입
			ph = ph->link; // ph를 다음 노드로 이동
		}
		count++; // count를 1 더한다
	}
}

/* 리스트를 출력하는 함수 */
void display(ListNode *head)
{
	ListNode *p = head; // 헤드 대신에 사용할 포인터 노드 p 선언

	/* p가 NULL일 때 까지 반복 */
	while (p != NULL)
	{
		if (p->link == NULL) // 마지막 노드이면
			printf("%d\n", p->data); // -> 빼고 출력

		else // 그렇지 않으면
			printf("%d -> ", p->data); // -> 포함해서 출력

		p = p->link; // p를 다음 노드로 이동
	}
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
	ListNode *list = NULL; // 헤드 노드 포인터 선언 및 초기화
	int data; // 파일에서 데이터를 받아 임시로 담을 변수 선언

	/* 파일포인터 fp 선언 및 data3.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR\n");
		return 0; // 예외 처리
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		// fp의 정수 데이터 하나를 data에 저장
		insert_node(&list, NULL, create_node(data, NULL));
		// data에 저장한 변수를 노드에 추가하여 리스트 연결
	}

	// 데이터 삭제 전 리스트의 데이터 출력
	display(list);

	// 홀수번 째 데이터 삭제
	remove_odd_node(&list);

	// 데이터 삭제 후 리스트의 데이터 출력
	display(list);

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
