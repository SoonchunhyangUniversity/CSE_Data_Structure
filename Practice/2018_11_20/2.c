/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 위상 정렬
 * 작성일 : 2018-11-20
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#include <string.h> // strcpy 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define SUBJECT_LEN 20 // 기호 상수 SUBJECT_LEN를 20으로 정의
#define MAX_VERTICES 50 // 기호 상수 MAX_VERTICES를 50으로 정의
#define STACK_LEN 200 // 기호 상수 STACK_LEN을 200으로 정의

/* 인접 리스트 그래프의 노드 구조체 */
typedef struct GraphNode
{
	int vertex;
	// 정점 번호 필드
	char sub[SUBJECT_LEN];
	// 과목 이름 필드
	struct GraphNode *link;
	// 링크 필드
} GraphNode; // GraphNode로 선언

/* 인접 리스트 그래프 구조체 */
typedef struct Graph
{
	int n;
	// 정점 개수 필드
	GraphNode *adj_list[MAX_VERTICES];
	// 인접 리스트 필드
} Graph; // Graph로 선언

/* 배열 기반 스택의 스택 구조체 */
typedef struct _arrayStack
{
	int stack[STACK_LEN];
	// 정수형 데이터를 저장하는 STACK_LEN길이의 배열
	int top;
	// 스택의 최상위 인덱스의 값
} Stack; // typedef로 Stack 키워드로 선언 가능

/* 그래프 초기화 함수 */
void graph_init(Graph *g);
/* 그래프 정점 삽입 함수 */
void insert_vertex(Graph *g, int v, char sub[]);
/* 그래프 간선 삽입 함수 */
void insert_edge(Graph *h, int u, int v);
/* 위상 정렬 함수 */
void topo_sort(Graph *g);

/* 배열 기반 스택 초기화 함수 */
void stack_init(Stack *s);
/* 배열 기반 스택 삽입 함수 */
void push(Stack * s, int data);
/* 배열 기반 스택 삭제 함수 */
int pop(Stack *s);
/* 배열 기반 스택 공백 확인 함수 */
int is_empty(Stack *s);
/* 배열 기반 스택 포화 확인 함수 */
int is_full(Stack *s);

int main()
{
	Graph g;
	// 그래프 구조체 선언

	int u, v;
	// 정점의 정보를 저장 할 변수 선언
	char c;
	// 연산자를 저장 할 변수 선언
	char sub[SUBJECT_LEN];
	// 과목 이름을 저장 할 변수 선언

	/* 파일 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		// 에러 메세지 출력
		return 0;
		// 메인 함수 종료
	}

	graph_init(&g);
	// graph_init 함수 호출로 그래프 초기화

	puts("< 데이터 >");
	puts("----------------");

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);
		// 파일 fp에서 문자 하나를 읽어와 c에 저장

		/* c가 'v'일 경우 */
		if (c == 'v')
		{
			fscanf(fp, " %d %s", &v, sub);
			// 파일에서 정수형 데이터와 문자열을 읽어와 저장

			insert_vertex(&g, v, sub);
			// insert_vertex 함수 호출로 정점 정보 삽입
		}

		/* c가 'e'일 경우 */
		else if (c == 'e')
		{
			fscanf(fp, " %d %d", &u, &v);
			// 파일에서 정수형 데이터 두개를 읽어와 저장

			insert_edge(&g, u, v);
			// insert_edge 함수 호출로 간선 정보 삽입
		}

		/* 잘못된 연산자일 경우 */
        else
        {
            printf("> %c < OPERATION ERROR!", c);
            // 에러 메세지 출력
            return 0;
            // 메인 함수 종료
        }
	}

	puts("----------------\n");

	puts("< 위상 순서 출력 >");
	puts("----------------");
	topo_sort(&g);
	// topo_sort 함수 호출로 위상 정렬 실행

	puts("----------------");

	fclose(fp);
	// 열어준 파일 포인터 fp를 닫아준다.

	return 0;
	// 메인 함수 종료
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

	/* 그래프의 최대 정점 번호가 v보다 작을 경우 */
	if (g->n < v)
		g->n = v;
		// 최대 정점 번호 갱신

	g->adj_list[v] = (GraphNode *)malloc(sizeof(GraphNode));
	// 정점 v의 인접 리스트 노드 동적 할당
	strcpy(g->adj_list[v]->sub, sub);
	// sub 필드에 과목명 저장
	g->adj_list[v]->link = NULL;
	// 링크 필드를 NULL로 저장
	printf("%d-%s\n", v, sub);
	// 삽입된 정점의 정보 출력
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
		puts("GRAPH VERTEX NUMBER ERROR!");
		// 에러 메세지 출력
		return;
		// 함수 종료
	}

	/* 인접 리스트에 삽입 할 노드 동적 할당 */
	node = (GraphNode *)malloc(sizeof(GraphNode));

	/* 동적 할당에 실패했을 경우 예외 처리 */
	if (node == NULL)
	{
		puts("MEMORY ALLOCATION ERROR!");
		// 에러 메세지 출력
		return;
		// 함수 종료
	}

	node->vertex = v;
	// 삽입 할 노드의 정점에 v 대입
	node->link = NULL;
	// 삽입 할 노드의 링크에 NULL 대입
	node->link = g->adj_list[u];
	// 새 노드의 링크를 u의 인접 리스트에 연결
	strcpy(node->sub, g->adj_list[u]->sub);
	// 인접 리스트의 과목 이름을 node의 sub에 복사
	g->adj_list[u] = node;
	// u의 인접 리스트의 링크에 새 노드 연결
}

/**
 * [topo_sort 함수]
 * @param g [그래프 구조체]
 */
void topo_sort(Graph *g)
{
	int i;
	// 반복문에서 사용 할 변수 선언
	int count = 0;
	// 위상 정렬 순서를 저장 할 변수 선언 및 초기화
	Stack s;
	// 스택 구조체 선언
	GraphNode *node;
	// 그래프의 포인터 노드 구조체 선언

	int *in_degree = (int *)malloc((g->n + 1) * sizeof(int));
	// 진입 차수를 저장 할 포인터 변수 선언 및 배열 동적 할당

	/* 최대 정점 번호만큼 반복 */
	for (i = 0; i <= g->n; i++)
		in_degree[i] = 0;
		// 배열의 초기화

	/* 최대 정점 번호만큼 반복 */
	for (i = 0; i <= g->n; i++)
	{
		node = g->adj_list[i];
		// 정점 i의 인접리스트 복사

		/* 인접리스트가 NULL일 떄 까지 반복 */
		while (node != NULL)
		{
			/* 현재 노드의 다음 노드가 NULL일 경우 */
			if (node->link == NULL)
				break;
				// 반복문 탈출

			in_degree[node->vertex]++;
			// 정점의 진입 간선 개수 증가
			node = node->link;
			// 다음 노드로 이동
		}
	}

	stack_init(&s);
	// stack_init 함수 호출로 스택 초기화

	/* 최대 정점 번호만큼 반복 */
	for (i = 0; i <= g->n; i++)
	{
		/* 진입 간선 개수가 9이면서 인접 리스트가 NULL이 아닌 경우 */
		if (in_degree[i] == 0 && g->adj_list[i] != NULL)
			push(&s, i);
			// push 함수 호출로 스택에 정점 번호 삽입
	}

	/* 스택이 비어있을 때 까지 반복 */
	while(!is_empty(&s))
	{
		int w = pop(&s);
		// pop 함수 호출로 진입 차수가 없는 정점 번호 삭제 후 저장

		printf("%d. %d-%s\n", ++count, w, g->adj_list[w]->sub);
		// 삭제된 순서와, 정점 번호, 정점의 과목명 출력

		node = g->adj_list[w];
		// 정점 w의 진입 차수 변경

		/* 인접리스트가 NULL일 때 까지 반복 */
		while (node != NULL)
		{
			/* 현재 노드의 다음 노드가 NULL일 경우 */
			if (node->link == NULL)
				break;
				// 반복문 탈출

			int u = node->vertex;
			// 진입 차수가 없는 정점
			in_degree[u]--;
			// 진입 차수 감소

			/* 진입 차수가 0일 경우 */
			if (in_degree[u] == 0)
				push(&s, u);
				// 스택에 정점 번호 삽입

			node = node->link;
			// 다음 노드로 이동(연결된 간선 제거)
		}
	}

	free(in_degree);
	// 배열의 메모리 할당 해제
}

/**
 * [stack_init 함수]
 * @param s [스택 구조체]
 */
void stack_init(Stack *s)
{
	s->top = -1;
	// 스택의 최상위 인덱스 값을 -1로 저장
}

/**
 * [push 함수]
 * @param s    [스택 구조체]
 * @param data [삽입될 데이터]
 */
void push(Stack *s, int data)
{
	/* 스택이 가득 차 있을 경우 */
	if(is_full(s))
	{
		puts("STACK MEMORY FULL ERROR!");
		// 에러 메세지 출력
		exit(-1);
		// 프로그램 종료
	}

	s->stack[++(s->top)] = data;
	// 스택에 배열의 top 다음 인덱스에 값을 삽입한다.
}

/**
 * [pop 함수]
 * @param  s [스택 구조체]
 * @return   [삭제된 데이터]
 */
int pop(Stack *s)
{
	int remove_idx; // 사라질 인덱스를 임시로 저장할 변수

	/* 스택이 비어있을 경우 */
	if (is_empty(s))
	{
		puts("STACK MEMORY EMPTY ERROR!");
		// 에러 메세지 출력
		exit(-1);
		// 프로그램 종료
	}

	remove_idx = (s->top)--;
	// remove_idx에 스택의 top저장 후 1을 뺸다.

	return s->stack[remove_idx];
	// 스택의  remove_idx번째 데이터 반환
}

/**
 * [is_empty 함수]
 * @param  s [스택 구조체]
 * @return   [스택 공백 여부]
 */
int is_empty(Stack *s)
{
	return (s->top == -1)
	// top가 -1일 경우 비어있으므로 TRUE반한
	// 그렇지 않을 경우 FALSE 반환
}

/**
 * [is_full 함수]
 * @param  s [스택 구조체]
 * @return   [스택 포화 여부]
 */
int is_full(StackType *s)
{
	return (s->top == (STACK_LEN - 1));
	// 스택의 최상위 인덱스가 STACK_LEN - 1이면 True
	// 그렇지 않으면 False 반환
}
