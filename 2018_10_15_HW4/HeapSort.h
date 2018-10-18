#ifndef __HEAP__SORT__
#define __HEAP__SORT__

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언

typedef int element;
// typedef선언으로 int형 데이터를 element타입으로 선언 가능

 /* 히프 구조체 */
typedef struct
{
	element *heap; // MAX사이즈의 element 구조체 배열 필드
	int heap_size; // 히프의 크기를 저장하는 정수 필수
} HeapType; // HeapType 키워드 선언 가능

/**
 * [insert_max_heap 함수]
 * @param h    [힙 구조체]
 * @param item [삽입될 데이터]
 */
void insert_max_heap(HeapType *h, element item)
{
	int i;
	// 반복문에 사용될 변수 선언
	i = ++(h->heap_size);
	// i 변수에 h의 heap_size를 1더한값 대입

	/* i가 1이되거나 item의 key값이 작을경우 반복문 탈출 */
	while ((i != 1) && (item > h->heap[i / 2]))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
		// i를 2로 나누면서 힙의 상단으로 이동
	}

	h->heap[i] = item; // 힙의 i번째 배열에 item 데이터 삽입
}

/**
 * [init 함수]
 * @param h [힙 구조체]
 */
void init(HeapType *h)
{
	h->heap_size = 0; // 힙의 사이즈를 0으로 초기화
}

/**
 * [delete_max_heap 함수]
 * @param  h [힙 구조체]
 * @return   [힙의 최댓값]
 */
element delete_max_heap(HeapType *h)
{
	int parent, child;
	// 힙의 부모노드와 자식노드 인덱스 변수 선언
	element item, temp;
	// 삭제될 데이터를 저장할 변수와 임시로 데이터를 저장할 변수 선언

	item = h->heap[1];
	// 삭제될 데이터에 힙의 최댓값 item에 저장
	temp = h->heap[(h->heap_size)--];
	// 힙의 가장 작은 데이터 temp에 저장
	parent = 1, child = 2;
	// 부모, 자식노드 인덱스값 초기화

	/* 자식노드 인덱스가 힙의 사이즈보다 크면 탈출하는 반복문 */
	while (child <= h->heap_size)
	{
		/* child의 인덱스가 힙 사이즈보다 작고
		   오른쪽 자식 노드의 키값이 클 경우*/
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++; // child 값 1 증가

		/* temp의 key값이 자식노드의 키값보다 크거나 같은 경우 */
		if (temp >= h->heap[child])
			break; // 반복문 탈출

		h->heap[parent] = h->heap[child];
		// 부모노드에 자식노드 대입
		parent = child;
		// 자식노드의 인덱스를 부모노드에 대입
		child *= 2;
		// 자식노드를 2 곱해준다.
	}

	h->heap[parent] = temp;
	// 반복이 끝난 부모노드에 temp 대입

	return item; // 삭제된 데이터 반환
}

/**
 * [heap_sort 함수]
 * @param arr [정렬할 배열]
 * @param n   [데이터의 개수]
 */
void heap_sort(int arr[], int n)
{
	int i;
	// 반복문에서 사용할 변수 선언
	HeapType h;
	// 히프 정렬에 사용할 히프 구조체 선언

	/* 히프의 배열을 데이터의 개수만큼 동적 할당 */
	h.heap = (element *)malloc(sizeof(element) * n);

	init(&h); // 히프 초기화

	/* 데이터의 개수만큼 반복 */
	for (i = 0; i < n; i++)
		insert_max_heap(&h, arr[i]);
		// 히프에 데이터 삽입

	/* 데이터의 개수만큼 반복 */
	for (i = (n - 1); i >= 0; i--)
		arr[i] = delete_max_heap(&h);
		// 히프에서 데이터를 삭제하면서 배열에 저장
}

#endif
