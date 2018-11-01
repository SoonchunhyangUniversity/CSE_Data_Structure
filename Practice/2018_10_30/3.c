/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 그래프 깊이 우선 탐색 프로그램
 * 작성일 : 2018-10-30
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언

#define TRUE 1 // 기호 상수 TRUE 1로 정의
#define FALSE 0 // 기호 상수 FALSE 0으로 정의
#define MAX_VERTICES 50 // 기호 상수 MAX_VERTICES 50으로 정의

/* 그래프의 노드 구조체 */
typedef struct _graphnode
{
	int vertex; // 정점 필드
	struct _graphnode *link; // 링크 필드
} GraphNode; // GraphNode로 선언 가능

/* 그래프 구조체 */
typedef struct _graphtype
{
	int n; // 정점 개수 필드
	GraphNode *adj_list[MAX_VERTICES]; // 연결된 정점 포인터 노드 필드
} Graph; // Graph로 선언 가능

/* 그래프 초기화 함수 */
void graph_init(Graph *g);
/* 그래프에 정점을 삽입하는 함수 */
void insert_vertex(Graph *g, int v);
/* 그래프에 간선을 삽입하는 함수*/
void insert_edge(Graph *g, int u, int v);
/* 그래프 깊이 우선 탐색 함수 */
void dfs_list(Graph *g, int v);

int main()
{
	int i;
	// 반복문에서 사용 할 변수 선언
	int v, u;
	// 연결 할 두 정점을 저장 할 변수 선언
	char c;
	// 연산자를 저장 할 문자형 변수 선언

	Graph g;
	// 그래프 구조체 선언

	/* 파일 포인터 fp 선언 및 data3.txt를 읽기 모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	graph_init(&g); // graph_init 함수 호출로 그래프 초기화

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);
		// 파일에서 문자를 하나 읽어와 c에 저장

		/* c가 'v'일 경우 */
		if (c == 'v')
		{
			fscanf(fp, " %d", &v);
			// 파일에서 정수형 데이터를 읽어와 v에 저장
			insert_vertex(&g, v);
			// insert_vertex 함수 호출로 정점 삽입
		}

		/* c가 'e'일 경우 */
		else if (c == 'e')
		{
			fscanf(fp, " %d %d", &u, &v);
			// 파일에서 정수형 데이터를 두개 읽어와 u, v에 저장
			insert_edge(&g, u, v);
			// insert_edge 함수로 두 정점 u, v를 연결
		}

		/* 잘못된 문자가 들어온 경우 예외처리 */
		else
		{
			printf("'%c' OPERATION ERROR!\n", c);
			// 잘못 들어온 연산자 오류 출력
			return 0;
			// 메인 함수 종료
		}
	}

	puts("- 그래프 깊이 우선 탐색 결과 -");
	printf("<");

	dfs_list(&g, 0);
	// dfs_list 함수 호출로 그래프 깊이 우선 탐색 결과 출력

	printf(" >\n");

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/**
 * [graph_init 함수]
 * @param g [그래프 구조체]
 */
void graph_init(Graph *g)
{
	int v;
	// 반복문에서 사용할 변수 선언

	g->n = 0;
	// 정점의 개수를 0으로 초기화

	/* 최대 정점의 개수 만큼 반복하는 반복문 */
	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
		// 인접 리스트를 NULL로 초기화
}

/**
 * [insert_vertex 함수]
 * @param g [그래프 구조체]
 * @param v [추가 할 정점]
 */
void insert_vertex(Graph *g, int v)
{
	/* 정점의 개수가 최대 개수보다 클 경우 예외처리 */
	if (((g->n) + 1) > MAX_VERTICES)
	{
		puts("GRAPH VERTEX EXCEEDED"); // 에러 메세지 출력
		return; // 함수 종료
	}

	g->n++; // 정점의 개수 1 증가
}

/**
 * [insert_edge 함수]
 * @param g [그래프 구조체]
 * @param u [연결 할 첫번째 정점]
 * @param v [연결 할 두번째 정점]
 */
void insert_edge(Graph *g, int u, int v)
{
	GraphNode *node;
	// 삽입 할 노드를 동적 할당할 포인터 구조체 선언
	GraphNode *p;
	// 원본 리스트를 복사하여 사용할 구조체 포인터 선언

	/* 연결 할 두 정점이 정점의 수보다 클 경우 예외처리 */
	if (u > g->n || v > g->n)
	{
		puts("GRAPH VERTEX NUMBER ERROR!"); // 에러 메세지 출력
		return; // 함수 종료
	}

	/* 인접 리스트에 삽입 할 노드 동적 할당 */
	node = (GraphNode *)malloc(sizeof(GraphNode));

	/* 동적 할당에 실패했을 경우 예외 처리 */
	if (node == NULL)
	{
		puts("MEMORY ALLOCATION ERROR!"); // 에러 메세지 출력
		return; // 함수 종료
	}

	node->vertex = v;
	// 삽입 할 노드의 정점에 v 대입
	node->link = NULL;
	// 삽입 할 노드의 링크에 NULL 대입

	p = g->adj_list[u];
	// 정점 u의 원본 인접 리스트 복사

	/* 인접 리스트가 비어있을 경우 */
	if (p == NULL)
	{
		node->link = g->adj_list[u];
		// 새 노드의 링크를 u의 인접 리스트에 연결
		g->adj_list[u] = node;
		// u의 인접 리스트의 링크에 새 노드 연결
	}

	/* 인접 리스트가 비어있지 않은 경우 */
	else
	{
		/* 인접 리스트의 끝까지 반복하는 반복문 */
		while (p->link != NULL)
		{
			/* 현재 노드의 다음 노드가 NULL이 아닐 경우 */
			if (p->link != NULL)
			{
				/* 다음 노드의 정점의 값보다 삽입 될 노드의
				   정점의 크기가 작을 경우 노드의 삽입 위치 */
				if (p->link->vertex > node->vertex)
					break; // 반복문 탈출
			}

			p = p->link;
			// 삽입 위치를 찾지 못했으니 다음 노드로 이동
		}

		node->link = p; // 삽입 할 노드의 링크에 p 연결
		p->link = node; // 현재 노드의 링크에 새 노드 연결
	}
}

/**
 * [dfs_list 함수]
 * @param g [그래프 구조체]
 * @param v [탐색 할 정점]
 */
void dfs_list(Graph *g, int v)
{
	GraphNode *w;
	// 원본 인접 리스트의 변경을 막기 위해 사용할 포인터 노드 선언

	static int visited[MAX_VERTICES];
	// 그래프 방문 확인 배열, static 키워드로 내부 정적 변수 사용

	visited[v] = TRUE; // 현재 정점 방문 확인

	printf(" %d", v); // 현재 정점의 값 출력

	/* 인접 리스트의 끝까지 반복하는 반복문 */
	for (w = g->adj_list[v]; w; w = w->link)
	{
		/* 해당 리스트에 방문하지 않았을 경우 */
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
			// dfs_list 함수 재귀 호출 다음 정점 탐색
	}
}
