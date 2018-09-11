/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : HW 1
 * 작성일 : 2018-09-10
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp함수 사용을 위한 헤더파일 선언
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
} Data; // typedef 선언으로 Data 키워드로 사용 가능

/* 연결리스트의 노드 구조체 */
typedef struct _node
{
	Data data; // Data형 data변수
	struct _node *next; // 다음 노드를 가리키는 포인터 구조체
} Node; // typedef선언으로 Node 키워드로 사용 가능

/* 노드를 동적 할당하여 생성하는 함수 */
Node *create_node(Data data, Node *next);
/* 연결 리스트에 노드를 삽입하는 함수 */
void insert(Node **phead, Node *new_node);
/* 연결 리스트의 데이터를 출력하는 함수 */
void display(Node *head);
/* 두 노드의 데이터를 교환하는 함수 */
void swap(Node *a, Node *b);
/* 연결 리스트를 학생들의 총합으로 정렬하는 함수 */
void sort_by_sum(Node *head);
/* 연결 리스트를 학생들의 이름으로 정렬하는 함수 */
void sort_by_name(Node *head);
/* 연결 리스트를 학생들의 학번으로 정렬하는 함수 */
void sort_by_std_num(Node *head);

int main()
{
	Node *list = NULL;
	// 연결 리스트의 헤드 노드 선언 및 초기화
	Data temp;
	// 파일에서 읽어온 데이터를 임시로 저장하는 변수
	char len_check[NAME_LEN] = { NULL };
	// 파일의 데이터를 한 줄 통쨰로 받아 저장할 변수

	/* 파일포인터 fp 선언 및 data3.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %d %d %d",
			&temp.std_num, temp.name, &temp.math, &temp.eng, &temp.kor);
		// fp의 데이터를 temp 변수에 저장

		temp.sum = temp.kor + temp.eng + temp.math;
		// 합계를 계산하여 temp의 sum변수에 저장
		temp.avg = temp.sum / 3.0;
		// 계산한 합계로 평균을 구하여 temp의 avg변수에 저장

		insert(&list, create_node(temp, NULL));
		// create_node함수로 temp의 데이터를 저장한 노드를 생성한 후
		// insert 함수를 이용하여 연결 리스트에 연결
	}

	printf("┌------------------------ 정렬전 ------------------------┐\n");
	display(list);

	printf("┌------------------- 총합 순으로 정렬 -------------------┐\n");
	sort_by_sum(list); // sort_by_sum 함수로 리스트를 총합으로 정렬
	display(list); // display 함수로 리스트의 데이터 출력

	printf("┌------------------- 이름 순으로 정렬 -------------------┐\n");
	sort_by_name(list); // sort_by_name 함수로 리스트를 이름으로 정렬
	display(list); // display 함수로 리스트의 데이터 출력

	printf("┌------------------- 학번 순으로 정렬 -------------------┐\n");
	sort_by_std_num(list); // sort_by_std_num 함수로 리스트를 학번으로 정렬
	display(list); // display 함수로 리스트의 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/* 노드를 동적으로 생성하는 함수 */
Node *create_node(Data data, Node *next)
{
	Node *new_node; // 새 노드를 동적 할당할 포인터 노드 선언
	new_node = (Node *)malloc(sizeof(Node)); // 새 노드 동적 할당

	/* 동적 할당에 실패할 경우 */
	if (new_node == NULL)
		printf("메모리 할당 에러"); // 에러메세지 실행

	new_node->data = data; // 새 노드의 데이터에 매개 변수 데이터 저장
	new_node->next = next; // 새 노드의 링크에 매개 변수로 받은 노드 저장

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
		printf("│ %9d │ %s│  %3d │  %3d │  %3d │  %3d  │ %4.2f │\n",
			p->data.std_num, p->data.name,
			p->data.math, p->data.eng, p->data.kor,
			p->data.sum, p->data.avg);

		p = p->next; // p를 다음 노드로 이동
	}

	printf("│========================================================│\n\n");
}

/* 연결리스트에 노드를 삽입하는 함수 */
void insert(Node **phead, Node *new_node)
{
	Node *cur = *phead;
	// 헤드 포인터 대신에 사용할 노드 선언 및 초기화

	/* 헤드 포인터가 NULL일 경우 */
	if ((*phead) == NULL)
		(*phead) = new_node;

	/* 리스트에 노드가 존재할 경우 */
	else
	{
		/* 리스트의 끝까지 이동 */
		while (cur->next != NULL)
			cur = cur->next;

		cur->next = new_node; // cur의 next에 new_node 연결
	}
}

/* 두 노드의 데이터를 교환하는 함수 */
void swap(Node *a, Node *b)
{
	Data temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/* 연결 리스트를 학생들의 총합으로 정렬하는 함수 */
void sort_by_sum(Node *head)
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
			/* cur의 데이터중 총합이 다음 노드의 총합보다 클 경우 */
			if (cur->data.sum > cur->next->data.sum)
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

/* 연결 리스트를 학생들의 이름으로 정렬하는 함수 */
void sort_by_name(Node *head)
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
			/* cur의 데이터중 이름이 다음 노드의 이름보다 클 경우 */
			if (strcmp(cur->data.name, cur->next->data.name) > 0)
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

/* 연결 리스트를 학생들의 학번으로 정렬하는 함수 */
void sort_by_std_num(Node *head)
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
			/* cur의 데이터중 학번이 다음 노드의 평균보다 클 경우 */
			if (cur->data.std_num > cur->next->data.std_num)
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
