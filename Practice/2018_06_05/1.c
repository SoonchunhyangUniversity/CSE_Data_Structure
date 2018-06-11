/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 문제 1
 * 작성일 : 2018 - 06 - 05
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#define MAX_QUEUE_SIZE 100 // 기호상수 MAX_QUEUE_SIZE를 100으로 정의

/* 학생의 데이터를 저장할 구조체*/
typedef struct _std
{
	char name[20]; // 학생의 이름
	int std_num; // 학번
	int kor; // 국어 점수
	int mat; // 수학 점수
	int eng; // 영어 점수
} element; // element 키워드로 구조체 사용

/* 배열 기반 큐 구조체 */
typedef struct
{
	element queue[MAX_QUEUE_SIZE]; // MAX_QUEUE_SIZE의 학생 구조체 배열
	int front; // 큐의 front
	int rear; // 큐의 rear
} QueueType; // QueueType 키워드로 구조체 사용

/* 에러 메세지를 출력하는 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/* 큐의 초기화 함수 */
void init(QueueType *q)
{
	q->front = q->rear = 0;
	// 큐의 front와 rear 맴버를 0으로 초기화
}

/* 큐가 비어있는지 확인하는 함수 */
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
	// 큐의 front와 rear가 같으면
	// 비어있으므로 TRUE 반환
	// 그렇지 않으면 FALSE 반환
}

/* 큐가 가득 차있는지 확인하는 함수 */
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
    // 큐의 rear + 1을 배열의 최대 사이즈와 mod 연산 결과가
    // 큐의 front와 같으면 큐가 가득 차 있으므로 TRUE 반환
    // 그렇지 않으면 FALSE 반환
}

/* 큐의 삽입 함수 */
void enqueue(QueueType *q, element item)
{
    /* 큐가 가득 차 있을 경우 */
	if (is_full(q))
		error("큐가 포화상태입니다.\n");

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    // 큐의 rear를 1더하고 배열의 최대 사이즈와 mod 연산 후 저장
	q->queue[q->rear] = item;
    // 큐의 rear번 째 배열의 데이터 저장
}

/* 큐의 삭제 함수 */
element dequeue(QueueType *q)
{
    /* 큐가 비어있을 경우 */
	if (is_empty(q))
		error("큐가 공백상태입니다.\n");

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    // 큐의 front를 1더하고 배열의 최대 사이즈와 mod 연산 후 저장
	return q->queue[q->front];
    // 큐의 front번 째 배열의 데이터 반환
}

/* 큐의 피크 함수 */
element peek(QueueType *q)
{
    /* 큐가 비어있을 경우 */
	if (is_empty(q))
		error("큐가 공백상태입니다.\n");

	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
    // 큐의 front 다음 배열의 데이터 반환
}

/* 큐의 데이터를 삽입할 때 상태를 출력하는 함수 */
void add_display(QueueType *q, element item)
{
	printf("add(%s  %d  %d  %d  %d)\n", item.name, item.std_num, item.kor, item.mat, item.eng);
	printf("front = %d  rear = %d\n\n", q->front, q->rear);
}

/* 큐의 데이터를 삭제할 때 상태를 출력하는 함수 */
void delete_display(QueueType *q, element item)
{
	printf("delete(%s  %d  %d  %d  %d)\n", item.name, item.std_num, item.kor, item.mat, item.eng);
	printf("front = %d  rear = %d\n\n", q->front, q->rear);
}

int main() // 메인 함수 시작
{
	QueueType q; // 큐 구조체 q 선언
	element item; // 데이터를 저장할 구조체  item 선언

    /* 파일 포인터 fp 선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

    /* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	init(&q); // 큐의 초기화

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %d %d %d %d", item.name, &item.std_num, &item.kor, &item.mat, &item.eng);
        // 파일에서 데이터를 읽어와 item 구조체에 저장
		enqueue(&q, item);
        // 입력받은 item 구조체를 큐 q구조체에 삽입
		add_display(&q, item);
        // 삽입된 item 구조체의 데이터와 큐의 상태 출력
	}

    /* 큐가 비어있을 때 까지 반복하는 반복문 */
	while (!is_empty(&q))
	{
		item = dequeue(&q);
        // 삭제되는 구조체를 item에 저장
		delete_display(&q, item);
        // 삭제된 item 구조체의 데이터와 큐의 상태 출력
	}

	fclose(fp); // 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
