/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 3
 * 작성일 : 2018 - 06 - 05
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호 상수 TRUE를 1으로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의

typedef int element; // element 키워드로 int형 데이터 선언 가능

/* 덱의 노드 구조체 */
typedef struct DlistNode
{
	element data; // element형 데이터
	struct DlistNode *llink; // 왼쪽 노드를 가리킬 포인터 노드
	struct DlistNode *rlink; // 오른쪽 노드를 가리킬 포인터 노드
} DlistNode; // DlistNode 키워드로 선언 가능

/* 덱의 구조체 */
typedef struct DequeType
{
	DlistNode *head; // 덱의 맨 앞 노드를 가리키는 포인터 노드
	DlistNode *tail; // 덱의 맨 뒤 노드를 가리키는 포인터 노드
	int count; // 덱의 데이터 개수를 저장하는 변수
} DequeType; // DequeType 키워드로 선언 가능

/* 오류 처리 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/* 덱의 초기화 함수 */
void init(DequeType *dq)
{
	dq->head = NULL; // 덱의 헤드 포인터를 NULL로 초기화
	dq->tail = NULL; // 덱의 테일 포인터를 NULL로 초기화
	dq->count = 0; // 덱의 데이터 개수를 0으로 초기화
}

/* 노드를 동적으로 생성하는 함수 */
DlistNode *create_node(DlistNode *llink, element item, DlistNode *rlink)
{
	DlistNode *node = (DlistNode *)malloc(sizeof(DlistNode));
	// 데이터를 저장할 새로운 노드 선언 및 메모리 할당

	/* 메모리 할당에 실패할 경우 */
	if (node == NULL)
		error("메모리 할당 오류\n");

	node->llink = llink; // 새 노드의 llink에 llink 연결
	node->rlink = rlink; // 새 노드의 rlink에 rlink 연결
	node->data = item; // 새 노드의 데이터에 item 저장

	return node; // 새 노드 반환
}

/* 덱이 비어있는지 확인하는 함수 */
int is_empty(DequeType *dq)
{
	/* 덱이 비어있을 경우 */
	if (dq->head == NULL)
		return TRUE; // TRUE 반환

	/* 덱이 비어있지 않은 경우 */
	else
		return FALSE; // FALSE 반환
}

/* 덱의 뒷부분에서 삽입하는 함수 */
void add_rear(DequeType *dq, element item)
{
	DlistNode *new_node = create_node(dq->tail, item, NULL);
	// create_node함수를 사용하여 노드 생성 후 데이터 저장
	// llink에 덱의 테일 노드를 연결

	/* 덱이 비어있는 경우 */
	if (is_empty(dq))
		dq->head = new_node;
		// 덱의 헤드 포인터에 새로운 노드를 저장

	/* 덱이 비어있지 않은 경우 */
	else
		dq->tail->rlink = new_node;
		// 덱의 테일 포인터의 오른쪽 링크를 새 노드와 연결

	dq->tail = new_node; // 덱의 테일 포인터에 새 노드 저장
	dq->count++; // 덱의 데이터 개수를 1 증가
}

/* 덱의 앞부분에서 삽입하는 함수 */
void add_front(DequeType *dq, element item)
{
	DlistNode *new_node = create_node(NULL, item, dq->head);
	// create_node함수를 사용하여 노드 생성 후 데이터 저장
	// rlink에 덱의 헤드 노드를 연결

	/* 덱이 비어있는 경우 */
	if (is_empty(dq))
		dq->tail = new_node;
		// 덱의 테일 포인터에 새로운 노드 저장

	/* 덱이 비어있지 않은 경우 */
	else
		dq->head->llink = new_node;
		// 덱의 헤드 포인터의 왼쪽 링크를 새 노드와 연결

	dq->head = new_node; // 덱의 헤드 포인터에 새 노드 저장
	dq->count++; // 덱의 데이터 개수를 1 증가
}

/* 덱의 앞부분에서 삭제하는 함수 */
element delete_front(DequeType *dq)
{
	element item; // 삭제될 데이터를 저장할 변수
	DlistNode *removed_node; // 삭제될 노드를 가리킬 노드 포인터

	/* 덱이 비어있을 경우 */
	if (is_empty(dq))
		error("덱이 비어있습니다.\n");

	/* 덱이 비어있지 않은 경우 */
	else
	{
		removed_node = dq->head; // 삭제할 노드 저장
		item = removed_node->data; // 삭제될 데이터 저장
		dq->head = dq->head->rlink; // 덱의 헤드포인터 변경

		free(removed_node); // 노드의 메모리 할당 해제

		/* 덱의 헤드 포인터가 NULL일 경우 */
		if (dq->head == NULL)
			dq->tail = NULL; // 테일 포인터를 NULL로 저장

		/* 그렇지 않을 경우 */
		else
			dq->head->llink = NULL;
			// 덱의 헤드 포인터의 llink를 NULL로 저장

		dq->count--; // 덱의 데이터 개수를 1 감소
	}

	return item; // 삭제된 데이터 반환
}

/* 덱의 뒷부분에서 삭제하는 함수 */
element delete_rear(DequeType *dq)
{
	element item; // 삭제될 데이터를 저장할 변수
	DlistNode *removed_node; // 삭제될 노드를 가리킬 노드 포인터

	/* 덱이 비어있을 경우 */
	if (is_empty(dq))
		error("덱이 비어있습니다.\n");

	/* 덱이 비어있지 않은 경우 */
	else
	{
		removed_node = dq->tail; // 삭제할 노드 저장
		item = removed_node->data; // 삭제될 데이터 저장
		dq->tail = dq->tail->llink; // 덱의 헤드포인터 변경

		free(removed_node); // 노드의 메모리 할당 해제

		/* 덱의 테일 포인터가 NULL일 경우 */
		if (dq->tail == NULL)
			dq->head = NULL; // 덱의 헤드 포인터를 NULL로 저장

		/* 그렇지 않을 경우 */
		else
			dq->tail->rlink = NULL;
			// 덱의 테일 포인터의 rlink를 NULL로 저장

		dq->count--; // 덱의 데이터 개수를 1 감소
	}

	return item; // 삭제된 데이터 반환
}

/* 덱의 상태를 출력하는 함수 */
void display(DequeType *dq, char *oper, char *position, element item)
{
	DlistNode *temp = dq->head;
	// 원본 덱의 헤드 포인터 대신에 사용할 포인터 노드
	static int step = 1;
	// static 변수 선언으로 값이 유지되도록 설정
	int i;
	// 반복문에서 사용 할 변수

	/* 매개변수의 연산자가 "add"일 경우 */
	if (!strcmp(oper, "add"))
		printf("---Step %d : %s %s %d ---\n", step++, oper, position, item);

	/* 매개변수의 연산자가 "delete"일 경우 */
	else if(!strcmp(oper, "delete"))
		printf("---Step %d : %s %s ---\n", step++, oper, position);

	printf("┌");

	for (i = 0; i <= (dq->count * 3); i++)
		printf("─");

	printf("┐\n");

	/* temp가 NULL일 때 까지 반복하는 반복문 */
	while (temp != NULL)
	{
		printf("%3d ", temp->data); // temp노드의 데이터 출력
		temp = temp->rlink; // temp가 오른쪽 노드를 가리키게 함
	}

	printf("\n└");

	for (i = 0; i <= (dq->count * 3); i++)
		printf("─");

	printf("┘\n");
}

int main() // 메인 함수 시작
{
	DequeType deque;
	// 덱 구조체 선언
	element item;
	// 파일에서 입력받은 데이터를 저장할 변수 선언
	char oper[8] = { 0 };
	// 파일에서 입력받은 연산자를 저장할 문자열 선언 및 초기화
	char position[6] = { 0 };
	// 파일에서 입력받은 연산 위치를 저장할 문자열 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data3.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	init(&deque); // 덱의 초기화

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %s", oper, position);
		// 파일에서 연산자와 연산 위치를 입력

		/* 입력받은 연산자가 "add"인 경우 */
		if (!strcmp(oper, "add"))
		{
			fscanf(fp, "%d", &item); // 파일에서 정수형 데이터 입력

			/* 입력받은 연산 위치가 "front"인 경우 */
			if (!strcmp(position, "front"))
				add_front(&deque, item); // add_front함수로 데이터 삽입

			/* 입력받은 연산 위치가 "rear"인 경우 */
			else if (!strcmp(position, "rear"))
				add_rear(&deque, item); // add_rear함수로 데이터 삽입
		}

		/* 입력받은 연산자가 "delete"인 경우 */
		else if (!strcmp(oper, "delete"))
		{
			/* 입력받은 연산 위치가 "front"인 경우 */
			if (!strcmp(position, "front"))
				item = delete_front(&deque);
				// delete_front함수로 데이터 삭제 및 item에 저장

			/* 입력받은 연산 위치가 "rear"인 경우 */
			else if (!strcmp(position, "rear"))
				item = delete_rear(&deque);
				// delete_rear함수로 데이터 삭제 및 item에 저장
		}

		/* 잘못된 연산자가 들어왔을 경우 */
		else
		{
			fprintf(stderr, "잘못된 연산자입니다.\n");
			return 0;
		}

		display(&deque, oper, position, item); // display함수로 덱의 상태 출력
	}

	fclose(fp); // 파일 포인터를 닫아준다.

	return 0; // 메인 함수 종료
}
