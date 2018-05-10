/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 원형 연결 리스트
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 08
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#define DEL_DATA 172 // 기호상수 DEL_DATA 172 선언, 삭제할 데이터

/* 리스트의 노드 구조체 */
typedef struct ListNode
{
	int data; // 정수형 데이터
	struct ListNode *link; // 다음 노드를 가리키는 포인터 구조체
} ListNode; // typedef로 구조체 선언 없이 ListNode 키워드 사용 가능

/* 리스트의 처음 노드와 마지막 노드를 저장하는 더미노드 */
typedef struct List
{
	ListNode *head; // 처음 노드
	ListNode *tail; // 마지막 노드
} List; // typedef로 구조체 선언 없이 List 키워드 사용 가능

/* 리스트를 초기화하는 함수 */
void list_init(List *header)
{
	header->head = NULL; // 더미노드의 head를 NULL로 초기화
	header->tail = NULL; // 더미노드의 tail을 NULL로 초기화
}

/* 리스트에 노드를 삽입하는 함수 */
void insert_node(List *header, int data)
{
	/* 새로운 노드를 동적 할당 */
	ListNode *new_node = (ListNode *)malloc(sizeof(ListNode));

	/* 리스트에 데이터가 없다면 */
	if (header->head == NULL)
	{
		header->head = new_node; // header의 haed에 새 노드 저장
		header->tail = new_node; // header의 tail에 새 노드 저장
		new_node->data = data; // 새 노드의 데이터에 data 저장
		new_node->link = header->tail; // 새 노드의 link에 헤더의 tail 저장

		return; // 함수 종료
	}

	/* 그렇지 않다면 */
	else
	{
		new_node->link = header->head; // 새 노드의 link에 header의 head 저장
		new_node->data = data; // 새 노드의 데이터에 data 저장
		header->head = new_node; // header의 head에 새 노드 저장
		header->tail->link = header->head; // header의 tail의 link에 header의 head 저장

		return; // 함수 종료
	}
}

/* 리스트에서 key값에 해당하는 데이터를 삭제하는 함수 */
void delete_node(List *header, int key)
{
	int check = 1; // 반복 조건을 체크하기 위한 변수 선언 및 초기화

	/* check가 0이 될 때까지 반복 */
	while (check)
	{
		check = 0; // check에 0저장

		ListNode *curr = header->head; // curr에 header의 head 저장
		ListNode *prev = header->tail; // prev에 header의 tail 저장

		do
		{
			/* curr의 data가 삭제할 key값과 같다면 */
			if (curr->data == key)
			{
				/* curr가 header의 head일 경우 */
				if (curr == header->head)
				{
					header->tail->link = header->head->link;
					// header의 tail의 link에 header의 head의 link 저장
					header->head = header->head->link;
					// header의 head에 header의 head의 link 저장
					free(curr);
					// curr노드의 메모리 할당 해제
				}

				/* curr가 header의 tail일 경우 */
				else if (curr == header->tail)
				{
					prev->link = header->tail->link;
					// prev의 link에 header의 tail의 link 저장
					header->tail = header->tail->link;
					// header의 tail에 header의 tail의 link 저장
					free(curr);
					// curr노드의 메모리 할당 해제
				}

				/* curr가 header의 head나 tail이 아닐 경우 */
				else
				{
					prev->link = curr->link;
					// prev의 link에 curr의 link 저장
					free(curr);
					// curr노드의 메모리 할당 해제
				}

				check = 1; // 데이터가 삭제 됐으므로 check를 1로 저장
				break; // 안쪽 반복문 종료
			}

			/* curr의 데이터가 삭제할 key값과 다르면 */
			else
			{
				prev = curr; // prev에 curr 저장
				curr = curr->link; // curr을 다음 노드로 이동
			}

		} while (curr != header->head); // curr이 header의 head와 같으면 반복 종료
	}
}

/* 리스트를 역순으로 바꾸는 함수 */
List *reverse(List *header)
{
	ListNode *p, *q, *r; // 노드 p, q, r 선언

	/* 공백이거나 노드가 하나일 경우 즉, 바꿀필요가 없는 경우 */
	if (header->head->link == header->head || header->head == NULL)
		return header; // header 반환

	p = header->head->link; // 시작노드 주소 저장
	q = header->head; // q는 역순으로 만들 노드

	/* p가 header의 head와 같을때 까지 반복 */
	while (p != header->head)
	{
		/* r은 역순으로 된 리스트 r은 q, q는 p를 차례로 따라감 */
		r = q; // r에 q 저장
		q = p; // q에 p 저장
		p = p->link; // p를 다음 노드로 이동
		q->link = r; // q의 링크 방향을 변경
	}

	header->head = q; // header의 head노드에 q 저장
	header->tail = p; // header의 tail노드에 p 저장
	p->link = q; // p의 link에 q 저장

	return header; // header를 반환
}

/* 리스트의 항목 출력 */
void display(List *header)
{
	ListNode *cur = header->head;
	// header의 head 대신 사용할 cur 선언 및 초기화

	printf("< ");

	do
	{
		printf("%d ", cur->data); // 데이터 출력
		cur = cur->link; // 다음 노드로 이동
	} while (cur != header->head); // cur이 header의 head와 같으면 반복 탈출

	printf(">\n");

	printf("Head : %d\n", header->head->data); // header의 head의 데이터 출력
	printf("Tail : %d\n", header->tail->data); // header의 tail의 데이터 출력
	printf("Tail Next : %d\n", header->tail->link->data); // header의 tail의 link의 데이터 출력
}


int main() // 메인 함수 시작
{
	List list; // 리스트 구조체 list 선언
	int data; // 파일의 데이터를 임시로 저장할 변수 선언

	list_init(&list); // list_init함수로 list초기화

	/* 파일포인터 fp선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &data); // 파일의 정수형 데이터를 data에 저장
		insert_node(&list, data); // insert_node함수로 리스트에 데이터 저장
	}

	display(&list); // display함수로 리스트 데이터 출력
	printf("\n");

	delete_node(&list, DEL_DATA); // delete_node함수로 리스트이 DEL_DATA 삭제
	reverse(&list); // reverse함수로 리스트를 역순으로 변경

	printf("< Delete %d >\n", DEL_DATA);
	printf("< Reverse >\n\n");
	display(&list); // display함수로 리스트 데이터 출력

	fclose(fp); // 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
