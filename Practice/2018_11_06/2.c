/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : Kruskal의 MST 알고리즘
 * 작성일 : 2018-11-06
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define MAX 200

int parent[MAX_VERTICES];
int num[MAX_VERTICES];

typedef struct
{
	int weight;
	int u;
	int v;
} element;

typedef struct
{
	element heap[MAX]; // MAX사이즈의 element 구조체 배열 필드
	int heap_size; // 히프의 크기를 저장하는 정수 필수
} HeapType; // HeapType 키워드 선언 가능

void set_init(int n);
void set_union(int s1, int s2);
int set_find(int vertex);

/* 힙을 초기화하는 함수 */
void init(HeapType *h);
/* 최소힙에 데이터를 삽입하는 함수 */
void insert_min_heap(HeapType *h, element item);
/* 힙의 데이터를 삭제하는 함수 */
element delete_min_heap(HeapType *h);

void insert_heap_edge(HeapType *h, int u, int v, int weight);

int main()
{
	element temp, check;
	HeapType h;

	int i;
	int edge_accepted = 0;
	int uset, vset, edge_check;
	int max = INT_MIN, cost = 0;

	init(&h);

	/* 파일 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	puts("- Kruskal의 최소 비용 신장 트리 프로그램 -\n");
	puts(">> 데이터 입력");

	while (!feof(fp))
	{
		fscanf(fp, " %d %d %d", &temp.u, &temp.v, &temp.weight);

		edge_check = FALSE;

		for (i = 0; i < h.heap_size; i++)
		{
			if ((temp.u == h.heap[i].u && temp.v == h.heap[i].v) ||
				(temp.v == h.heap[i].u && temp.u == h.heap[i].v))
			{
				printf("간선 %d - %d 은 이미 추가된 간선 입니다. -- 제외\n",
					temp.u, temp.v);

				edge_check = TRUE;
				break;
			}
		}

		if (max < temp.u || max < temp.v)
			(temp.u > temp.v) ? (max = temp.u) : (max = temp.v);

		if (edge_check)
			continue;

		else
		{
			insert_heap_edge(&h, temp.u, temp.v, temp.weight);
			printf("간선 %d - %d 추가 완료\n", temp.u, temp.v);
		}
	}

	puts("\n>> 과정");

	set_init(max + 1);

	while (edge_accepted < max)
	{
		temp = delete_min_heap(&h);

		uset = set_find(temp.u);
		vset = set_find(temp.v);

		if (uset != vset)
		{
			printf("간선 %d-%d : %d\n", temp.u, temp.v, temp.weight);
			edge_accepted++;
			set_union(uset, vset);

			cost += temp.weight;
		}

		else
		{
			if ((check.u == temp.v && check.v == temp.u) ||
				(check.u == temp.u && check.v == temp.v))
			{
				edge_accepted++;
				break;
			}

			printf("간선 %d-%d : %d - 사이클 생성으로 제외\n",
					temp.u, temp.v, temp.weight);
		}

		check = temp;
	}

	printf("\n< 필요한 최소 비용 %d >\n", cost);

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	return 0; // 메인 함수 종료
}

void set_init(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		parent[i] = -1;
		num[i] = 1;
	}
}

void set_union(int s1, int s2)
{
	if (num[s1] < num[s2])
	{
		parent[s1] = s2;
		num[s2] += num[s1];
	}

	else
	{
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

int set_find(int vertex)
{
	int p, s, i = -1;

	for (i = vertex; (p = parent[i]) >= 0; i = p);

	s = i;

	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;

	return s;
}

void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;

	e.u = u;
	e.v = v;
	e.weight = weight;

	insert_min_heap(h, e);
}

/**
 * [insert_min_heap 함수]
 * @param h    [힙 구조체]
 * @param item [삽입될 데이터]
 */
void insert_min_heap(HeapType *h, element item)
{
	int i;
	// 반복문에 사용될 변수 선언
	i = ++(h->heap_size);
	// i 변수에 h의 heap_size를 1더한값 대입

	/* i가 1이되거나 item의 key값이 클경우 반복문 탈출 */
	while ((i != 1) && (item.weight < h->heap[i / 2].weight))
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
 * [delete_min_heap 함수]
 * @param  h [힙 구조체]
 * @return   [힙의 최솟값]
 */
element delete_min_heap(HeapType *h)
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
		   오른쪽 자식 노드의 작을값이 클 경우*/
		if ((child < h->heap_size) &&
			(h->heap[child].weight) > h->heap[child + 1].weight)
			child++; // child 값 1 증가

		/* temp의 key값이 자식노드의 키값보다 작거나 같은 경우 */
		if (temp.weight <= h->heap[child].weight)
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
