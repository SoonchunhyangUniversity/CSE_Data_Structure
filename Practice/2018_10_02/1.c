/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 동물 히프
 * 작성일 : 2018-10-02
 */

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#define MAX 200 // 기호상수 MAX를 200으로 정의

/* 히프의 데이터 element 구조체 */
typedef struct
{
	int key; // 정수형 우선순위 필드
	char name[MAX]; // 문자열 이름 필드
} element; // element 키워드 선언 가능

/* 히프 구조체 */
typedef struct
{
	element heap[MAX]; // MAX사이즈의 element 구조체 배열 필드
	int heap_size; // 히프의 크기를 저장하는 정수 필수
} HeapType; // HeapType 키워드 선언 가능

void insert_max_heap(HeapType *h, element item);
void init(HeapType *h);
void display(HeapType h);
element delete_max_heap(HeapType *h);

int main()
{
	element temp;
	HeapType heap;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	init(&heap);

	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &temp.key, temp.name);
		insert_max_heap(&heap, temp);
		printf(">> %d:%s\n", temp.key, temp.name);
		display(heap);
	}

	printf("우선 순위 큐에 데이터를 넣을 동물의 우선순위오 이름을 입력하시오(완료시 우선순위 : 0)\n");

	do
	{
		printf(">> ");
		scanf("%d %s", &temp.key, temp.name);

		if (temp.key == 0)
			break;

		insert_max_heap(&heap, temp);
		display(heap);

	} while (1);

	fclose(fp);

	return 0;
}

void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

void display(HeapType h)
{
	HeapType *ph = &h;
	element item;

	while (ph->heap_size != 0)
	{
		item = delete_max_heap(ph);

		if (ph->heap_size == 0)
			printf("%d : %s\n", item.key, item.name);

		else
			printf("%d : %s > ", item.key, item.name);
	}

	printf("\n");
}


element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1, child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;

		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;

	return item;
}
