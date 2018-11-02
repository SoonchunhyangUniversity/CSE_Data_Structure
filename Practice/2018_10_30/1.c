/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 삽입 정렬 프로그램
 * 작성일 : 2018-10-30
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언

/* 학생 정보 구조체 */
typedef struct _std
{
	int num; // 학번
	int kor; // 국어 점수
	int eng; // 영어 점수
	int mat; // 수학 점수
	int sum; // 총점
	double avg; // 평균
} Student; // Student 키워드로 선언 가능

/* 연결 리스트의 노드 구조체 */
typedef struct _node
{
	Student data; // 데이터 필드
	struct _node *link; // 링크 필드
} Node; // Node 키워드로 선언 가능

/* 노드를 동적 할당 하는 함수 */
Node *create_node(Student data, Node *link);
/* 연결리스트에 노드를 삽입하는 함수 */
void insert_node(Node **phead, Node *new_node);
/* 연결리스트의 데이터를 출력하는 함수 */
void display(Node *head);
/* 삽입 정렬에 사용 할 삽입 함수 */
void sorted_insert(Node **phead, Node *new_node);
/* 삽입 정렬 함수 */
void insertion_sort(Node **phead);

int main()
{
	Node *list = NULL;
	// 연결 리스트 포인터 노드 선언 및 초기화
	Student temp;
	// 파일에서 받아온 데이터를 저장할 Student 구조체 선언

	int count = 0;
	// 데이터의 개수를 저장 할 변수 선언 및 초기화

	/* 파일 fp 선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d %d",
				&temp.num, &temp.kor, &temp.eng, &temp.mat);
		// 파일 fp에서 정수형 데이터 4개를 읽어와 temp에 저장
		temp.sum = (temp.kor + temp.eng + temp.mat);
		// 읽어온 데이터를 기반으로 총점 계산
		temp.avg = (double)temp.sum / 3.0;
		// 계산한 총점을 기반으로 평균 계산

		insert_node(&list, create_node(temp, NULL));
		// 계산이 끝난 데이터를 create_node 함수로 노드를 생성 한 후
		// insert_node 함수로 list에 삽입

		count++; // 데이터의 개수 1 증가
	}

	/* display 함수를 호출하여 정렬 전 데이터 출력 */
	puts("<정렬 전>");
	display(list);

	/* insertion_sort 함수를 호출하여 연결 리스트 정렬 */
	insertion_sort(&list);

	/* display 함수를 호출하여 정렬 후 데이터 출력 */
	puts("<정렬 후>");
	display(list);

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	return 0; // 메인 함수 종료
}

/**
 * [create_node 함수]
 * @param  data [삽입 할 데이터]
 * @param  link [연결 할 노드 포인터]
 * @return      [완성된 노드]
 */
Node *create_node(Student data, Node *link)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	// 새로운 노드 포인터 선언 및 동적 할당

	/* 동적 할당에 실패했을 경우 예외처리 */
	if (new_node == NULL)
	{
		printf("MEMORY ALLOCATION ERROR!\n"); // 에러 메세지 출력
		return NULL; // 함수 종료
	}

	new_node->data = data;
	// 새로운 노드의 데이터 필드에 data 대입
	new_node->link = link;
	// 새로운 노드의 링크 필드에 link 대입

	return new_node; // 완성된 노드 반환
}

/**
 * [insert_node 함수]
 * @param phead    [연결 리스트 헤드 포인터]
 * @param new_node [삽입 할 노드]
 */
void insert_node(Node **phead, Node *new_node)
{
	/* 데이터가 없을 경우 */
	if (*phead == NULL)
	{
		new_node->link = NULL;
		// new_node의 링크 필드에 NULL 대입
		*phead = new_node;
		// 헤드 포인터에 삽입 할 노드 연결
	}

	/* 데이터가 존재 할 경우 */
	else
	{
		Node *p = *phead;
		// 원본 변경을 막기 위한 변수 선언 및 초기화

		/* 리스트의 맨 끝까지 반복하는 반복문 */
		while (p->link != NULL)
			p = p->link; // 다음 노드로 이동

		p->link = new_node;
		// 마지막 노드의 링크 필드에 삽입 할 노드 연결
	}
}

/**
 * [display 함수]
 * @param head [리스트의 헤드 노드]
 */
void display(Node *head)
{
	Node *p = head;
	// 원본의 변경을 막기 위한 변수 선언 및 초기화

	puts("|========|=============================|");
	puts("|  학번  | 국어| 영어| 수학|총 점|평 균|");

	/* 리스트의 끝 까지 반복하는 반복문 */
	while (p != NULL)
	{
		printf("|%8d| %3d | %3d | %3d | %3d |%2.2lf|\n",
				p->data.num, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		// 학생의 데이터 출력

		p = p->link;
		// 다음 노드로 이동
	}

	puts("|========|=============================|\n");
}

/**
 * [sorted_insert 함수]
 * @param phead    [연결 리스트의 헤드 포인터]
 * @param new_node [삽입 할 노드]
 */
void sorted_insert(Node **phead, Node *new_node)
{
	Node *current;
	// 현재재 노드를 저장 할 변수 선언

	/* 노드가 없을 경우 또는 삽입 할 노드의 값이 큰 경우
	   -> 연결 리스트의 맨 앞에 삽입되는 경우 */
	if ((*phead == NULL) ||
			((*phead)->data.sum < new_node->data.sum))
	{
		new_node->link = *phead;
		// 새 노드의 링크 필드에 헤드 포인터 연결
		*phead = new_node;
		// 헤드 포인터에 삽입 할 노드 대입
	}

	/* 맨 앞에 삽입되는 경우가 아닐 경우 */
	else
	{
		current = *phead;
		// 원본의 변경을 막기 위한 변수 선언 및 초기화

		/* 새로운 노드가 삽입될 위치를 찾을 떄 까지 반복하는 반복문 */
		while (current->link != NULL &&
					(current->link->data.sum > new_node->data.sum))
		{
			current = current->link;
			// 다음 노드로 이동
		}

		new_node->link = current->link
		// 삽입될 노드의 링크에 현재 노드의 링크 연결
		current->link = new_node;
		// 현재 노드의 링크에 삽입될 노드 연결
	}
}

/**
 * [insertion_sort 함수]
 * @param phead [연결 리스트의 헤드 포인터]
 */
void insertion_sort(Node **phead)
{
	Node *sorted = NULL;
	// 새로 정렬된 리스트를 저장할 노드 포인터 선언 및 초기화
	Node *current = *phead;
	// 원본의 변경을 막기 위한 변수 선언 및 초기화

	/* 리스트의 끝까지 반복하는 반복문 */
	while (current != NULL)
	{
		Node *next = current->link;
		// 다음에 이동할 노드를 저장할 노드 포인터 선언 및 초기화

		sorted_insert(&sorted, current);
		// sorted_insert 함수를 호출하여 sorted 리스트에 현재 노드 삽입

		current = next;
		// 다음 노드로 이동
	}

	*phead = sorted;
	// 정렬된 연결 리스트를 원본 리스트 헤드 포인터에 연결
}
