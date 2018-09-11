/**
* 작성자 : 김민수
* 학번 : 20174444
* 학과 : 컴퓨터소프트웨어공학과
* 프로그램명 : 이중 연결 리스트의 이동 연산
* 작성일 : 2018-09-11
*/
#include <stdio.h> // 표준입출력 라이브러레 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언

typedef char Data; // typedef 선언으로 Data키워드로 사용 가능

/**
 * Name : DlistNode
 * type : struct
 * Dscription
 * [이중 연결리스트의 노드 구조체]
 */
typedef struct DlistNode
{
	Data data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

/* 이중연결리스트의 초기화 함수 정의 */
void init(DlistNode *phead);
/* 이중연결리스트의 데이터를 출력하는 함수 정의 */
void display(DlistNode *phead);
/* 이중연결리스트의 노드에 데이터를 삽입하는 함수 정의 */
void insert(DlistNode *head, DlistNode *new_node);
/* 선택정렬 함수 정의 */
void selection_sort(DlistNode *phead);
/* 노드 교환 함수 정의 */
void swap(DlistNode *a, DlistNode *b);
/* 노드를 생성하는 함수 정의*/
DlistNode *create_node(Data data);

int main()
{
	char temp;
    // 문자를 임시로 저장할 변수 선언
	DlistNode head;
    // 이중연결리스트의 헤드 노드 선언

    /* 파일 포인터 fp 선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

    /* 파일 오픈에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPNE ERROR!\n");
		return 0;
	}

	init(&head); // 이중연결리스트의 초기화

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c", &temp);
        // 파일에서 문자열을 하나 읽어온다.
		insert(&head, create_node(temp));
        // 노드를 생성해 이중연결리스트에 삽입
	}

	display(&head); // 정렬 전 데이터 출력

	selection_sort(&head); // 선택 정렬 진행

	return 0; // 메인 함수 종료
}

/**
 * [init 함수]
 * @param phead [이중연결리스트 헤드 노드]
 */
void init(DlistNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

/**
 * [display 함수]
 * @param phead [이중연결리스트 헤드 노드]
 */
void display(DlistNode *phead)
{
	DlistNode *p;
    // 헤드 포인터 대신에 사용할 노드 선언 및 초기화

	printf("< ");

    /* 이중연결리스트의 끝까지 이동하며 출력 */
	for (p = phead->llink; p->llink != phead; p = p->llink)
		printf("%c ", p->data);

	printf(">\n");
}

/**
 * [insert 함수]
 * @param head     [이중연결리스트 헤드 노드]
 * @param new_node [삽입할 노드]
 */
void insert(DlistNode *phead, DlistNode *new_node)
{
	new_node->llink = phead;
	new_node->rlink = phead->rlink;
	phead->rlink->llink = new_node;
	phead->rlink = new_node;
}

/**
 * [swap 함수]
 * @param a [순서를 변경할 노드]
 * @param b [순서를 변경할 노드]
 */
void swap(DlistNode *a, DlistNode *b)
{
	Data temp = a->data;
	a->data = b->data;
	b->data = temp;
}

/**
 * [selection_sort 함수]
 * @param phead [이중연결리스트 헤드 노드]
 */
void selection_sort(DlistNode *phead)
{
	DlistNode *p;
    // 헤드 포인터 대신에 사용할 노드 선언
	DlistNode *q;
    // p의 선행 노드
	int count = 1;
    // 정렬 횟수를 저장할 변수 선언 및 초기화

    /* p의 llink가 phead와 같아질 때 까지 반복하는 반복문 */
	for (p = phead->llink; p->llink != phead; p = p->llink)
	{
		DlistNode *min = p;
        // 최솟값을 저장하고 있는 노드를 저장할 변수 선언 및 초기화

        /* q의 llink가 phead와 같아질 때 까지 반복하는 반복문 */
		for (q = p->llink; q->llink != phead; q = q->llink)
		{
            /* q의 데이터가 min의 데이터보다 작다면 */
			if (min->data > q->data)
				min = q; // min에 q를 저장
		}

		swap(p, min); // 노드를 교환

        /* 정렬 과정을 출력 */
		printf("%d ", count++);
		display(phead);
	}
}

/**
 * [create_node 함수]
 * @param  data [노드에 저장할 데이터]
 * @return      [데이터를 담은 노드]
 */
DlistNode *create_node(Data data)
{
	DlistNode *new_node;
	new_node = (DlistNode *)malloc(sizeof(DlistNode));

	if (new_node == NULL)
		printf("메모리 할당 에러");

	new_node->data = data;

	return (new_node);
}
