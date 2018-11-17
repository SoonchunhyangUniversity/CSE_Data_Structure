/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : Kruskal의 MST 알고리즘
 * 작성일 : 2018-11-06
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define MAX_VERTICES 100 // 기호 상수 MAX_VERTICES를 100으로 정의
#define MAX 200 // 기호 상수 MAX를 200으로 정의

int parent[MAX_VERTICES]; // 부모 노드를 저장 할 전역 배열 선언
int num[MAX_VERTICES]; // 각 집합의 크기를 저장 할 전역 배열 선언

/* 간선의 정보를 저장 할 히프의 요소 구조체 정의 */
typedef struct
{
	int weight; // 가중치 필드
	int u; // 정점 1
	int v; // 정점 2
} element; // element 키워드로 선언 가능

/* 히프 구조체 정의 */
typedef struct
{
	element heap[MAX]; // MAX사이즈의 element 구조체 배열 필드
	int heap_size; // 히프의 크기를 저장하는 정수 필수
} HeapType; // HeapType 키워드 선언 가능

/* union find 알고리즘 초기화 함수 */
void set_init(int n);
/* 두 원소가 속한 집합을 합치는 함수 */
void set_union(int s1, int s2);
/* 정점이 속하는 집합을 반환하는 함수 */
int set_find(int vertex);

/* 히프을 초기화하는 함수 */
void heap_init(HeapType *h);
/* 최소히프에 데이터를 삽입하는 함수 */
void insert_min_heap(HeapType *h, element item);
/* 히프의 데이터를 삭제하는 함수 */
element delete_min_heap(HeapType *h);

/* 히프에 간선의 정보를 삽입하는 함수 */
void insert_heap_edge(HeapType *h, int u, int v, int weight);

int main()
{
	element temp, check;
	// 파일에서 받아올 데이터를 저장 할 변수와 사이클을 확인 할 구조체 변수 선언
	HeapType h;
	// 히프 구조체 선언

	int i;
	// 반복문에서 사용 할 변수 선언
	int edge_accepted = 0;
	// 현재까지 선택된 간선의 수를 저장 할 변수 선언
	int uset, vset, edge_check;
	// 정점 u와 정점 v의 집합 번호를 저장할 변수와 이미 연결된 간선 확인 변수 선언
	int max = INT_MIN, cost = 0;
	// 정점 번호의 최댓값을 저장 할 변수와 크루스칼 알고리즘의 비용을 저장 할 변수 선언 및 초기화

	heap_init(&h); // heap_init 함수 호출로 히프 초기화

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	puts("- Kruskal의 최소 비용 신장 트리 프로그램 -\n");
	puts(">> 데이터 입력");

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d %d %d", &temp.u, &temp.v, &temp.weight);
		// 파일에서 정점 두 개의 정보와 가중치를 읽어와 temp에 저장

		edge_check = FALSE;
		// 간선 연결 확인 변수에 FALSE 대입

		/* 히프에 데이터의 개수만큼 반복하는 반복문 */
		for (i = 0; i < h.heap_size; i++)
		{
			/* 이미 연결된 정점들인지 확인하는 조건문 */
			if ((temp.u == h.heap[i].u && temp.v == h.heap[i].v) ||
				(temp.v == h.heap[i].u && temp.u == h.heap[i].v))
			{
				printf("간선 %d - %d 은 이미 추가된 간선 입니다. -- 제외\n",
					temp.u, temp.v); // 예외 출력

				edge_check = TRUE; // 간선 연결 확인 변수에 TRUE 대입
				break; // for loop 탈출
			}
		}

		/* 현재 정점 번호의 최댓값을 판별하는 변수 선언 */
		if (max < temp.u || max < temp.v)
			(temp.u > temp.v) ? (max = temp.u) : (max = temp.v);
			// max에 두 정점 중 최댓값 대입

		/* 두 정점이 이미 연결되어 있을 경우 */
		if (edge_check)
			continue; // 다음 while loop로 이동

		/* 두 정점이 연결되어있지 않을 경우 */
		else
		{
			insert_heap_edge(&h, temp.u, temp.v, temp.weight);
			// insert_heap_edge 함수 호출로 히프에 간선 정보 삽입
			printf("간선 %d - %d 추가 완료\n", temp.u, temp.v);
			// 삽입된 간선 정보 출력
		}
	}

	puts("\n>> 과정");

	set_init(max + 1); // set_init 함수 호출로 집합 배열 초기화

	/* 모든 간선을 확인할 때 까지 반복하는 반복문 */
	while (edge_accepted < max)
	{
		temp = delete_min_heap(&h);
		// delete_min_heap 함수 호출로 히프 데이터 삭제 후 temp에 대입

		uset = set_find(temp.u);
		// 정점 u의 집합 번호 대입
		vset = set_find(temp.v);
		// 정점 v의 집합 번호 대입

		/* 서로 다른 집합일 경우 */
		if (uset != vset)
		{
			printf("간선 %d-%d : %d\n", temp.u, temp.v, temp.weight);
			// 간선 정보와 비용 출력
			edge_accepted++;
			// 선택된 간선 갯수 1 증가
			set_union(uset, vset);
			// set_union 함수 호출로 두 집합을 결합

			cost += temp.weight;
			// 비용을 현재 간선의 가중치 만큼 증가
		}

		/* 같은 집합일 경우 */
		else
		{
			/* 이전에 탐색했던 간선과 같은 간선일 경우 */
			if ((check.u == temp.v && check.v == temp.u) ||
				(check.u == temp.u && check.v == temp.v))
			{
				edge_accepted++;
				// 선택된 간선 갯수 1 증가
				continue;
				// 다음 while loop 진행
			}

			printf("간선 %d-%d : %d - 사이클 생성으로 제외\n",
					temp.u, temp.v, temp.weight);
			// 사이틀 생성으로 제외된 간선 정보 출력
		}

		check = temp;
		// check 구조체에 탐색한 간선 대입
	}

	printf("\n< 필요한 최소 비용 %d >\n", cost);
	// Kruskal 알고리즘으로 구한 비용 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	return 0; // 메인 함수 종료
}

/**
 * [set_init 함수]
 * @param n [정점의 개수]
 */
void set_init(int n)
{
	int i;
	// 반복문에서 사용 할 변수 선언

	/* 정점의 개수만큼 반복하는 반복문 */
	for (i = 0; i < n; i++)
	{
		parent[i] = -1; // parent 배열 초기화
		num[i] = 1; // num 배열 초기화
	}
}

/**
 * [set_union 함수]
 * @param s1 [트리1의 루트 인덱스]
 * @param s2 [트리2의 루트 인덱스]
 */
void set_union(int s1, int s2)
{
	/* s2의 루트 값이 클 경우 */
	if (num[s1] < num[s2])
	{
		parent[s1] = s2;
		// parent의 s1번째 데이터에 s2 대입
		num[s2] += num[s1];
		// num의 s2번째 데이터에 num의 s1번째 데이터 값 증가
	}

	/* s1의 루트 값이 더 클 경우 */
	else
	{
		parent[s2] = s1;
		// parent의 s2번째 데이터에 s1 대입
		num[s1] += num[s2];
		// num의 s1번째 데이터에 num의 s2번째 데이터 값 증가
	}
}

/**
 * [set_find 함수]
 * @param  vertex [탐색 할 정점]
 * @return        [집합 대표 원소]
 */
int set_find(int vertex)
{
	int p, i = -1;
	// 반복문에서 사용 할 변수 선언
	int s;
	// 집합의 대표 원소를 저장 할 변수 선언

	/* 루트 노드까지 반복하는 반복문 */
	for (i = vertex; (p = parent[i]) >= 0; i = p);

	s = i; // 집합의 대표 원소 값 s에 대입

	/* 집합의 끝까지 반복하는 반복문 */
	for (i = vertex; (p = parent[i]) >= 0; i = p)
		parent[i] = s;
		// 집합의 모든 원소들의 부모를 s로 설정

	return s; // 집합의 대표 원소 반환
}

/**
 * [insert_heap_edge 함수]
 * @param h      [히프 구조체]
 * @param u      [정점1 번호]
 * @param v      [정점2 번호]
 * @param weight [간선의 가중치]
 */
void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	// 간선의 정보를 저장 할 구조체 변수 선언

	/* 간선의 정보 대입 */
	e.u = u;
	e.v = v;
	e.weight = weight;

	insert_min_heap(h, e);
	// insert_min_heap 함수 호출로 히프에 간선 정보 삽입
}

/**
 * [insert_min_heap 함수]
 * @param h    [히프 구조체]
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
		// i를 2로 나누면서 히프의 상단으로 이동
	}

	h->heap[i] = item; // 히프의 i번째 배열에 item 데이터 삽입
}

/**
 * [heap_init 함수]
 * @param h [히프 구조체]
 */
void heap_init(HeapType *h)
{
	h->heap_size = 0; // 히프의 사이즈를 0으로 초기화
}

/**
 * [delete_min_heap 함수]
 * @param  h [히프 구조체]
 * @return   [히프의 최솟값]
 */
element delete_min_heap(HeapType *h)
{
	int parent, child;
	// 히프의 부모노드와 자식노드 인덱스 변수 선언
	element item, temp;
	// 삭제될 데이터를 저장할 변수와 임시로 데이터를 저장할 변수 선언

	item = h->heap[1];
	// 삭제될 데이터에 히프의 최댓값 item에 저장
	temp = h->heap[(h->heap_size)--];
	// 히프의 마지막 인덱스 데이터 temp에 저장
	parent = 1, child = 2;
	// 부모, 자식노드 인덱스값 초기화

	/* 자식노드 인덱스가 히프의 사이즈보다 크면 탈출하는 반복문 */
	while (child <= h->heap_size)
	{
		/* child의 인덱스가 히프 사이즈보다 작고
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
