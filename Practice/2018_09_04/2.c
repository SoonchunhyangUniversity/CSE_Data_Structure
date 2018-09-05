/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 파일에서 자료 읽어오기2
 * 작성일 : 2018-09-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#define NAME_LEN 20 // 기호 상수 NAME_LEN 20으로 정의

/* 학생의 데이터를 저장하는 구조체 */
typedef struct _data
{
	int std_num; // 학번을 저장할 정수형 변수
	char name[NAME_LEN]; // 이름을 저장할 문자열 변수
	int math; // 수학 점수를 저장할 정수형 변수
	int eng; // 영어 점수를 저장할 정수형 변수
	int kor; // 국어 점수를 저장할 정수형 변수
	int sum; // 점수 합을 저장할 정수형 변수
	double avg; // 평균을 저장할 실수형 변수
}Data; // typedef 선언으로 Data 키워드로 사용 가능

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
/* 연결 리스트를 정렬하는 함수 */
void sort(Node *head);

int main()
{
	Node *list = NULL;
	// 연결 리스트의 헤드 노드 선언 및 초기화
	Data temp;
	// 파일에서 읽어온 데이터를 임시로 저장하는 변수
	int count = 0;
	// 파일 안의 데이터의 개수를 저장하는 변수
	char len_check[NAME_LEN] = { NULL };
	// 파일의 데이터를 한 줄 통쨰로 받아 저장할 변수

	/* 파일포인터 fp 선언 및 data2.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s", len_check);
		// fp의 문자열 데이터를 len_check에 저장
		count++;
		// 데이터의 개수를 하나 더한다.
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 데이터의 개수 만큼 반복하는 반복문 */
	for (int i = 0; i < count / 5; i++)
	{
		fscanf(fp, "%d %s %d %d %d",
					&temp.std_num, temp.name, &temp.math, &temp.eng, &temp.kor);
		// fp의 데이터를 temp 변수에 저장

		temp.sum = temp.kor + temp.eng + temp.math;
		// 합계를 계산하여 temp의 sum변수에 저장
		temp.avg = temp.sum / 3.0;
		// 계산한 합계로 평균을 구하여 temp의 avg변수에 저장

		insert(&list, NULL, create_node(temp, NULL));
		// create_node함수로 temp의 데이터를 저장한 노드를 생성한 후
		// insert 함수를 이용하여 연결 리스트에 연결
	}

	sort(list); // sort 함수로 리스트를 정렬
	display(list); // display 함수로 리스트의 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/* 노드를 동적으로 생성하는 함수 */
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

/* 연결 리스트의 데이터를 출력하는 함수 */
void display(Node *head)
{
	Node *p = head;
	// 헤드포인터를 대신해 사용할 노드 포인터 선언 및 초기화

	printf("│========================================================│\n");
	printf("│ 학     번 │ 이 름 │ 수학 │ 영어 │ 국어 │ 총 점 │ 평 균 │\n");
	printf("│========================================================│\n");

	/* 노드 p가 NULL일 때까지 반복 */
	while (p != NULL)
	{
		printf("│ %9d │ %s│  %3d │  %3d │  %3d │  %3d  │ %.2f │\n",
			p->data.std_num, p->data.name,
			p->data.math, p->data.eng, p->data.kor,
			p->data.sum, p->data.avg);

		p = p->next; // p를 다음 노드로 이동
	}

	printf("│========================================================│\n");
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
	Data temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/* 연결 리스트를 정렬하는 함수 */
void sort(Node *head)
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
			/* cur의 데이터중 평균이 다음 노드의 평균보다 클 경우 */
			if (cur->data.avg < cur->next->data.avg)
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
