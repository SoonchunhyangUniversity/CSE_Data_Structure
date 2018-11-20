/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 위상 정렬
 * 작성일 : 2018-11-20
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SUBJECT_LEN 20
#define MAX_VERTICES 50
#define STACK_LEN 200

typedef struct GraphNode
{
	int vertex;
	char sub[SUBJECT_LEN];
	struct GraphNode *link;
} GraphNode;

typedef struct Graph
{
	int n;
	GraphNode *adj_list[MAX_VERTICES];
} Graph;

/* 배열 기반 스택의 스택 구조체 */
typedef struct _arrayStack
{
	int stackArr[STACK_LEN];
	// 정수형 데이터를 저장하는 STACK_LEN길이의 배열
	int topIndex;
	// 스택의 최상위 인덱스의 값
} Stack; // typedef로 Stack 키워드로 선언 가능

void graph_init(Graph *g);
void insert_vertex(Graph *g, int v, char sub[]);
void insert_edge(Graph *h, int u, int v);
void topo_sort(Graph *g);

void stack_init(Stack *s);
void push(Stack * pstack, int data);
int is_empty(Stack *s);
int pop(Stack *s);

int main()
{
	Graph g;

	int u, v;
	char c;
	char sub[SUBJECT_LEN];

	/* 파일 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	graph_init(&g);

	puts("< 데이터 >");
	puts("----------------");

	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);

		if (c == 'v')
		{
			fscanf(fp, " %d %s", &v, sub);

			insert_vertex(&g, v, sub);
		}

		else if (c == 'e')
		{
			fscanf(fp, " %d %d", &u, &v);

			insert_edge(&g, u, v);
		}
	}

	puts("----------------\n");

	puts("< 위상 순서 출력 >");
	puts("----------------");
	topo_sort(&g);

	puts("----------------");

	fclose(fp);

	return 0;
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
void insert_vertex(Graph *g, int v, char sub[])
{
	/* 정점의 개수가 최대 개수보다 클 경우 예외처리 */
	if (((g->n) + 1) > MAX_VERTICES)
	{
		puts("GRAPH VERTEX EXCEEDED"); // 에러 메세지 출력
		return; // 함수 종료
	}

	if (g->n < v)
		g->n = v;

	g->adj_list[v] = (GraphNode *)malloc(sizeof(GraphNode));
	strcpy(g->adj_list[v]->sub, sub);
	g->adj_list[v]->link = NULL;
	printf("%d-%s\n", v, sub);
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
	node->link = g->adj_list[u];
	// 새 노드의 링크를 u의 인접 리스트에 연결
	strcpy(node->sub, g->adj_list[u]->sub);
	g->adj_list[u] = node;
	// u의 인접 리스트의 링크에 새 노드 연결
}

void topo_sort(Graph *g)
{
	int i;
	int count = 0;
	Stack s;
	GraphNode *node;

	int *in_degree = (int *)malloc((g->n + 1) * sizeof(int));

	for (i = 0; i <= g->n; i++)
		in_degree[i] = 0;

	for (i = 0; i <= g->n; i++)
	{
		node = g->adj_list[i];

		while (node != NULL)
		{
			if (node->link == NULL)
				break;

			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	stack_init(&s);

	for (i = 0; i <= g->n; i++)
	{
		if (in_degree[i] == 0 && g->adj_list[i] != NULL)
			push(&s, i);
	}

	while(!is_empty(&s))
	{
		int w;
		w = pop(&s);

		printf("%d. %d-%s\n", ++count, w, g->adj_list[w]->sub);

		node = g->adj_list[w];

		while (node != NULL)
		{
			if (node->link == NULL)
				break;

			int u = node->vertex;
			in_degree[u]--;

			if (in_degree[u] == 0)
				push(&s, u);

			node = node->link;
		}
	}

	free(in_degree);
}

/* 스택을 초기화 하는 함수 */
void stack_init(Stack * pstack)
{
	pstack->topIndex = -1; // 스택의 최상위 인덱스 값을 -1로 저장
}

/* 스택이 비어있는지 검사하는 함수 */
int is_empty(Stack * pstack)
{
	/* 스택의 최상위 인덱스가 -1이면 */
	if (pstack->topIndex == -1)
		return TRUE; // TRUE 반환

	/* 그렇지 않으면 */
	else
		return FALSE; // FALSE 반환
}

/* 스택에 데이터를 삽입하는 함수 */
void push(Stack * pstack, int data)
{
	pstack->stackArr[++(pstack->topIndex)] = data;
	// 스택에 배열의 topIndex 다음 인덱스에 값을 삽입한다.
}

/* 스택의 맨 위 데이터를 꺼내는 함수 */
int pop(Stack * pstack)
{
	int rIdx; // 사라질 인덱스를 임시로 저장할 변수

	/* 스택이 비어있는지 확인 */
	if (is_empty(pstack)) // 비어있다면
	{
		printf("Stack Memory Error!"); // 에러 메세지 출력
		exit(-1); // 프로그램 종료
	}

	rIdx = (pstack->topIndex)--; // rIdx에 스택의 topIndex저장 후 1을 뺸다.

	return pstack->stackArr[rIdx]; // 스택의  rIdx번째 데이터 반환
}
