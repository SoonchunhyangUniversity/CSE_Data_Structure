/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 2
 * 작성일 : 2018 - 06 - 05
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp 함수 사용을 위한 헤더파일 선언

typedef int element; // element 키워드로 int형 데이터 선언 가능

/* 연결 리스트 기반 큐의 노드 구조체 */
typedef struct QueueNode
{
	element item; // element형 데이터
	struct QueueNode *link; // 다음 노드를 가리킬 포인터 노드
} QueueNode; // QueueNode 키워드로 선언

/* 연결 리스트 기반 큐의 구조체 */
typedef struct
{
	QueueNode *front; // 큐의 맨 앞 노드를 가리킬 포인터 노드
	QueueNode *rear; // 큐의 맨 뒤 노드를 가리킬 포인터 노드
	int count; // 큐의 데이터 개수를 저장할 정수형 변수
} QueueType; // QueueType 키워드로 선언

/* 오류를 출력하는 함수 */
void error(char *messgae)
{
	fprintf(stderr, "%s\n", messgae);
	exit(1);
}

/* 큐의 초기화 함수 */
void init(QueueType *q)
{
	q->front = NULL; // 큐의 front를 NULL로 저장
	q->rear = NULL; // 큐의 rear를 NULL로 저장
	q->count = 0; // 큐의 count를 0으로 저장
}

/* 큐가 비어있는지 확인하는 함수 */
int is_empty(QueueType *q)
{
	return (q->front == NULL);
	// 큐의 front가 NULL일 경우 큐가 비어있는 상태이므로 TURE 반환
	// 그렇지 않은 경우 FALSE 반환
}

/* 큐의 데이터 삽입 함수 */
void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	// 데이터를 저장할 노드를 동적 할당

	/* 동적 할당에 실패할 경우 */
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다.\n");

	else
	{
		temp->item = item; // 데이터 저장
		temp->link = NULL; // 노드의 다음 노드를 NULL로 저장

		/* 큐가 비어있을 경우 */
		if (is_empty(q))
		{
			q->front = temp;
			q->rear = temp;
			// 큐의 front와 rear가 새 노드를 가리키도록 함
		}

		/* 큐가 비어있지 않을 경우 */
		else
		{
			q->rear->link = temp;
			q->rear = temp;
			// 큐의 rear의 링크가 새 노드를 가리키도록함
			// 큐의 rear를 새 노드로 저장
		}

		q->count++; // 큐의 데이터 개수 카운트를 1 증가
	}
}

/* 큐의 데이터 삭제 함수 */
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front; // 삭제될 노드를 temp에 저장
	element item; // 삭제될 노드의 데이터를 저장할 변수

	/* 큐가 비어있을 경우 */
	if (is_empty(q))
		error("큐가 비어있습니다.\n");

	/* 큐가 비어있지 않을 경우 */
	else
	{
		item = temp->item; // 데이터를 저장
		q->front = q->front->link; // front가 다음 노드를 가리키게 한다.

		/* 큐가 비어있는 상태가 될 경우 */
		if (q->front == NULL)
			q->rear = NULL;

		free(temp); // 노드의 메모리 할당 해제
		q->count--; // 큐의 데이터 개수 카운트를 1 감소

		return item; // 삭제된 데이터 반환
	}
}

/* 큐의 peek 함수 */
element peek(QueueType *q)
{
	/* 큐가 비어있을 경우 */
	if (is_empty(q))
		error("큐가 비어있습니다.\n");

	else
		return q->front->item; // 큐의 front 노드의 item 반환
}

/* 큐의 상태를 출력하는 함수 */
void display(QueueType *q, char *oper, element item)
{
	QueueNode *temp = q->front;
	// 큐의 front노드를 가리킬 변수 선언 및 대입
	static int step = 1;
	// static 변수 선언으로 값이 유지되도록 함
	int i;
	// 반복문에서 사용할 변수

	/* 연산자가 "addq"일 경우 */
	if (!strcmp(oper, "addq"))
		printf("---Step %d : %s %d ---\n", step++, oper, item);

	/* 연산자가 "deleteq"일 경우 */
	else if (!strcmp(oper, "deleteq"))
		printf("---Step %d : %s ---\n", step++, oper);

	printf("┌");

	for (i = 0; i <= (q->count * 3); i++)
		printf("─");

	printf("┐\n ");

    /* temp가 NULL이 될 때 까지 반복하는 반복문 */
	while (temp != NULL)
	{
		printf("%3d ", temp->item); // temp의 데이터 출력
		temp = temp->link; // temp가 다음 노드를 가리키게 한다.
	}

	printf("\n└");

	for (i = 0; i <= (q->count * 3); i++)
		printf("─");

	printf("┘\n");
}

int main() // 메인 함수 시작
{
	QueueType q; // 연결 리스트 기반 큐 선언
	element item; // 파일에서 입력 받은 데이터를 저장할 변수 선언
	char oper[8] = { 0 }; // 파일에서 연산자를 입력 받을 문자열 선언

    /* 파일 포인터 fp선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

    /* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	init(&q); // 큐의 초기화

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s", oper); // 파일에서 연산자를 oper에 입력

        /* 연산자가 "addq"일 경우 */
		if (!strcmp(oper, "addq"))
		{
			fscanf(fp, "%d ", &item); // 파일에서 데이터를 item에 입력
			enqueue(&q, item); // 큐에 입력받은 데이터 삽입
		}

        /* 연산자가 "deleteq"일 경우 */
		else if (!strcmp(oper, "deleteq"))
			item = dequeue(&q); // 큐에서 삭제되는 데이터를 item에 저장

        /* 잘못된 연산자가 들어왔을 경우 */
		else
		{
			fprintf(stderr, "잘못된 연산자 입니다.\n");
			return 0;
		}

		display(&q, oper, item); // 큐의 상태를 출력
	}

	fclose(fp); // 열어준 파일포인터를 닫아준다.

	return 0; // 메인 함수 종료
}
