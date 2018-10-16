/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 기수 정렬
 * 작성일 : 2018-10-16
 */

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#define BUCKET_NUM 10 // 기호 상수 BUCKET_NUM을 10으로 정의

typedef int Data; // int형 변수를 Data키워드로 선언 가능

/* 연결 리스트 기반 큐의 노드 구조체 */
typedef struct _node
{
	Data data; // 정수형 데이터 필드
	struct _node * next; // 다음 노드를 가리키는 구조체 포인터
} Node; // typedef 선언으로 Node 키워드로 선언 가능

/* 큐 구조체 */
typedef struct _lQueue
{
	Node * front; // 맨 앞 노드를 가리키는 포인터 구조체
	Node * rear; // 맨 끝 노드를 가리키는 포인터 구조체
} Queue; // typedef 선언으로 QueueInit 키워드로 선언 가능

/* 연결 리스트 기반 큐 초기화 함수 */
void QueueInit(Queue *pq);
/* 연결 리스트 기반 큐 삽입 함수 */
void Enqueue(Queue *pq, Data data);
/* 연결 리스트 기반 큐 공백 확인 함수 */
int QIsEmpty(Queue *pq);
/* 연결 리스트 기반 큐 삭제 함수 */
Data Dequeue(Queue *pq);

/* 기수 정렬 함수 */
void radix_sort(int arr[], int count, int maxLen);
/* 배열의 데이터를 출력하는 함수 */
void display(int arr[], int count);

int main()
{
	int *arr = NULL;
	// 정수형 배열을 동적 할당할 포인터 변수 선언 및 초기화
	int count = 0;
	// 학생의 수를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	/* 파일 포인터 fp선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 예외처리
	}

	/* 퍼일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		// 파일에서 데이터를 읽어와 임시로 저장
		count++;
		// 데이터의 개수를 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 데이터의 개수만큼 배열 동적 할당 */
	arr = (int *)malloc(sizeof(int) * count);

	/* 데이터의 개수 만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &arr[i]);
		// 파일에서 데이터를 읽어와 배열에 저장

	printf("< 정렬전 데이터 >\n");
	display(arr, count); // display 함수로 배열의 데이터 출력

	printf("\n< 정렬 과정 >\n");
	radix_sort(arr, count, 3); // radix_sort 함수 호출하여 기수 정렬

	printf("< 정렬후 데이터 >\n");
	display(arr, count); // display 함수로 배열의 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.
	free(arr); // 동적 할당한 배열의 메모리 할당 해제

	return 0; // 메인 함수 종료
}

/**
 * [QueueInit 함수]
 * @param pq [큐 구조체]
 */
void QueueInit(Queue *pq)
{
	pq->front = NULL; // 큐의 front 변수를 NULL로 초기화
	pq->rear = NULL; // 큐의 rear 변수를 NULL로 초기화
}

/**
 * [Enqueue 함수]
 * @param pq   [큐 구조체]
 * @param data [삽입될 데이터]
 */
void Enqueue(Queue *pq, Data data)
{
	Node *newNode = (Node*)malloc(sizeof(Node));
	// 삽입될 노드 동적 할당
	newNode->next = NULL;
	// 새 노드의 링크를 NULL로 초기화
	newNode->data = data;
	// 새 노드의 데이터 필드에 data 저장

	/* 큐가 비어있는지 확인 */
	if (QIsEmpty(pq)) // 비어있는 경우
	{
		pq->front = newNode;
		// 큐의 front에 새 노드 연결
		pq->rear = newNode;
		// 큐의 rear에 새 노드 연결
	}

	else // 비어있지 않은 경우
	{
		pq->rear->next = newNode;
		// rear에 다음 노드를 newNode 연결
		pq->rear = newNode;
		// rear을 newNode로 저장
	}
}

/**
 * [QIsEmpty 함수]
 * @param  pq [큐 구조체]
 * @return    [큐 공백 여부]
 */
int QIsEmpty(Queue *pq)
{
	return pq->front == NULL;
	// 큐의 front가 NULL인 경우 TRUE
	// NULL이 아닌 경우 FALSE
}

/**
 * [Dequeue 함수]
 * @param  pq [큐 구조체]
 * @return    [삭제된 데이터]
 */
Data Dequeue(Queue *pq)
{
	Node *delNode;
	// 삭제될 노드를 저장할 포인터 노드 구조체 선언
	Data retData;
	// 반환될 데이터를 저장할 변수 선언

	/* 큐가 비어있는지 확인 */
	if (QIsEmpty(pq)) // 큐가 비어있는 경우
	{
		printf("Queue Memory Error!"); // 에러 출력
		exit(-1); // 예외 처리 종료
	}

	delNode = pq->front;
	// 삭제될 노드에 front 저장
	retData = delNode->data;
	// 삭제될 노드에서 데이터를 retData 데이터에 저장
	pq->front = pq->front->next;
	// 쿠의 front를 다음 노드로 이동

	free(delNode); // 삭제되는 노드 메모리 할당 해제

	return retData; // 삭제된 데이터 반환
}

/**
 * [radix_sort 함수]
 * @param arr    [정수형 배열]
 * @param count  [데이터 개수]
 * @param maxLen [데이터의 최대 자리수]
 */
void radix_sort(int arr[], int count, int maxLen)
{
	Queue buckets[BUCKET_NUM];
	// 0 부터 9까지의 자리수를 저장할 큐 배열 선언
	int bi, pos, di, i;
	// 반복문에서 사용할 변수 선언
	int divfac = 1;
	// 나눌 자리수를 저장할 변수 선언 및 초기화
	int radix;
	// 현재 자리수를 저장할 변수 선언

	/* 총 10개의 버킷 초기화 */
	for (bi = 0; bi < BUCKET_NUM; bi++)
		QueueInit(&buckets[bi]);

	/* 가장 긴 데이터의 길이반큼 반복 */
	for (pos = 0; pos < maxLen; pos++)
	{
		printf("- Digit %d -\n", pos + 1);

		/* 정렬대상의 수만큼 반복 */
		for (di = 0; di < count; di++)
		{
			/* N번째 자리의 숫자 추출 */
			radix = (arr[di] / divfac) % 10;

			/* 추출한 숫자를 근거로 버킷에 데이터 저장 */
			Enqueue(&buckets[radix], arr[di]);
		}

		/* 버킷 수만큼 반복 */
		for (bi = 0, di = 0; bi < count; bi++)
		{
			printf("Bucket[%d] : ", bi);

			/* 큐가 비어있을 경우 */
			if (QIsEmpty(&buckets[bi]))
				printf("Empty");

			/* 버킷에 저장된 것 순서대로 다 꺼내서 다시 arr에 저장 */
			while (!QIsEmpty(&buckets[bi]))
			{
				i = Dequeue(&buckets[bi]);
				arr[di++] = i;
				printf(" %d", i);
			}

			printf("\n");
		}
		printf("\n");
		/* N번째 자리의 숫자 추출을 위한 피제수의 증가 */
		divfac *= 10;
	}
}

/**
 * [display 함수]
 * @param arr   [정수형 배열]
 * @param count [데이터 개수]
 */
void display(int arr[], int count)
{
	int i;

	/* 데이터의 개수만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
	{
		/* 마지막 데이터일 경우 */
		if (i == count - 1)
			printf("%d", arr[i]);

		/* 그렇지 않은 경우 */
		else
			printf("%d > ", arr[i]);
	}

	printf("\n");
}
