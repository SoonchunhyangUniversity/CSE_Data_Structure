/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 파일에서 자료 읽어오기1
 * 작성일 : 2018-09-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언

typedef int Data; // int형 데이터를 typedef선언으로 Data 키워드로 사용 가능

/* 연결리스트의 노드 구조체 */
typedef struct _node
{
	Data data; // Data형 data변수
	struct _node *next; // 다음 노드를 가리키는 포인터 구조체
} Node; // typedef선언으로 Node 키워드로 사용 가능

/* 노드를 동적 할당하여 생성하는 함수 */
Node *create_node(Data data, Node *next);
/* 연결 리스트에 노드를 삽입하는 함수 */
void insert(Node **phead, Node *p, Node *new_node);
/* 연결 리스트의 데이터를 출력하는 함수 */
void display(Node *head);
/* 두 노드의 데이터를 교환하는 함수 */
void swap(Node *a, Node *b);
/* 연결 리스트를 오름차순으로 정렬하는 함수 */
void down_to_up_sort(Node *head);
/* 연결 리스트를 내림차순으로 정렬하는 함수 */
void up_to_down_sort(Node *head);

int main()
{
	Node *list = NULL;
    // 연결 리스트의 헤드 노드 선언 및 초기화
	int count = 0;
    // 파일 안의 데이터의 개수를 저장하는 변수
	Data temp;
    // 파일에서 읽어온 데이터를 임시로 저장하는 변수

    /* 파일포인터 fp 선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

    /* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
        // fp의 정수형 데이터 하나를 temp에 저장
		count++;
        // 데이터의 개수를 하나 더한다.
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

    /* 데이터의 개수 만큼 반복하는 반복문 */
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d", &temp);
		// 정수형 데이터를 파일에서 읽어와 temp에 저장
		insert(&list, NULL, create_node(temp, NULL));
		// create_node함수로 temp의 데이터를 저장한 노드를 생성한 후
		// insert 함수를 이용하여 연결 리스트에 연결
	}

	printf("<오름차순 정렬>\n");
	down_to_up_sort(list);
	// down_to_up_sort 함수를 사용해 리스트를 오름차순으로 정렬
	display(list);
	// 리스트의 데이터 출력

	printf("\n");

	printf("<내림차순 정렬>\n");
	up_to_down_sort(list);
	// up_to_down_sort 함수를 사용해 리스트를 내림차순으로 정렬
	display(list);
	// display 함수로 리스트의 데이터 출력

	fclose(fp); // 열어춘 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/* 노드를 동적으로 생성하는 함수 */
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node; // 새 노드를 동적 할당할 포인터 노드 선언
	new_node = (ListNode *)malloc(sizeof(ListNode)); // 새 노드 동적 할당

	/* 동적 할당에 실패할 경우 */
	if (new_node == NULL)
		printf("메모리 할당 에러"); // 에러메세지 실행

	new_node->data = data; // 새 노드의 데이터에 매개 변수 데이터 저장
	new_node->link = link; // 새 노드의 링크에 매개 변수로 받은 노드 저장

	return (new_node); // 동적 할당한 후 데이터를 저장한 노드를 반환
}

/* 연결 리스트의 데이터를 출력하는 함수 */
void display(Node *head)
{
	Node *p = head;
	// 헤드포인터를 대신해 사용할 노드 포인터 선언 및 초기화

	/* 노드 p가 NULL일 때까지 반복 */
	while (p != NULL)
	{
		/* p가 마지막 노드일 경우 */
		if (p->next == NULL)
		{
			printf(" %d", p->data); // 데이터 출력
			break; // 반복문 종료
		}

		printf(" %d ->", p->data); // "->"를 붙여 데이터 출력
		p = p->next; // p를 다음 노드로 이동
	}

	printf("\n");
}

/* 연결 리스트에 노드를 삽입하는 함수 */
void insert(ListNode **phead, ListNode *p, ListNode *new_node)
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

/* 두 노드의 데이터를 교환하는 함수 */
void swap(Node *a, Node *b)
{
	int temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/* 연결 리스트를 오름차순으로 정렬하는 함수 */
void down_to_up_sort(Node *head)
{
	int check = 1;
	// 데이터의 정렬이 완료되었는지 확인하는 변수 선언 및 초기화
	Node *cur;
	// 현재 노드를 가리킬 변수 선언
	Node *pre = NULL;
	// 이전 노드를 가리킬 변수 선언

	/* 헤드 포인터가 NULL일 경우 */
	if (head == NULL)
		return; // 함수 종료

	/* check가 0이될 때 까지 반복 */
	while (check)
	{
		check = 0; // check에 0을 대입
		cur = head; // cur에 head 대입

		/* cur의 다음 노드가 pre일 때 까지 반복 */
		while (cur->next != pre)
		{
			/* cur의 데이터가 다음 노드의 데이터보다 클 경우 */
			if (cur->data > cur->next->data)
			{
				swap(cur, cur->next);
				// cur의 데이터와 cur다음 노드의 데이터를 swap함수로 교환
				check = 1;
				// 데이터 교환에 성공했으므로 check에 1대입
			}

			cur = cur->next; // cur을 다음 노드로 이동
		}

		pre = cur; // pre에 cur을 대입
	}
}

/* 연결 리스트를 내림차순으로 정렬하는 함수 */
void up_to_down_sort(Node *head)
{
	int check = 1;
	// 데이터의 정렬이 완료되었는지 확인하는 변수 선언 및 초기화
	Node *cur;
	// 현재 노드를 가리킬 변수 선언
	Node *pre = NULL;
	// 이전 노드를 가리킬 변수 선언

	/* 헤드 포인터가 NULL일 경우 */
	if (head == NULL)
		return; // 함수 종료

	/* check가 0이될 때 까지 반복 */
	while (check)
	{
		check = 0; // check에 0을 대입
		cur = head; // cur에 head 대입

		/* cur의 다음 노드가 pre일 때 까지 반복 */
		while (cur->next != pre)
		{
			/* cur의 데이터가 다음 노드의 데이터보다 작을 경우 */
			if (cur->data > cur->next->data)
			{
				swap(cur, cur->next);
				// cur의 데이터와 cur다음 노드의 데이터를 swap함수로 교환
				check = 1;
				// 데이터 교환에 성공했으므로 check에 1대입
			}

			cur = cur->next; // cur을 다음 노드로 이동
		}

		pre = cur; // pre에 cur을 대입
	}
}
