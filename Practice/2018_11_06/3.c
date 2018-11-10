/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : Prim의 MST 알고리즘
 * 작성일 : 2018-11-06
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define INF 1000L // 기호 상수 INF를 1000L로 정의

int *selected;
int *dist;

/* 최소 비용의 정점을 반환하는 함수 */
int get_min_vertex(int n);
/* Prim의 최소 비용 신장 트리 알고리즘 함수 */
void prim(int **adj_mat, int s, int n);

int main()
{
	int **adj_mat;
	// 인접 행렬 배열을 동적 할당할 배열 선
	int i, j;
	// 반복문에서 사용 할 변수 선언
	int u, v, weight;
	// 정점의 정보와 가중치를 저장할 변수 선언
	int max = INT_MIN;
	// 정점의 숫자의 최댓값을 저장 할 변수 선언 및 초기화

	/* 파일 fp 선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d %d %d", &u, &v, &weight);
		// 파일에서 정수형 데이터 3개를 읽어와 변수에 저장

		/* 정점의 최댓값을 찾는 조건문 */
		if (max < u || max < v)
			(u > v) ? (max = u) : (max = v);
			// u, v중 큰 값을 max변수에 대입
	}

	selected = (int *)malloc(sizeof(int) * (max + 1));
	// 전역 변수 selected 배열 동적 할당
	dist = (int *)malloc(sizeof(int) * (max + 1));
	// 전역 변수 dist 배열 동적 할당

	/* 인접 행렬 배열 동적 할당 행 우선 동적 할당 진행 */
	adj_mat = (int **)malloc(sizeof(int *) * (max + 1));

	/* 행의 개수 만큼 반복하는 반복문 */
	for (i = 0; i <= max; i++)
		adj_mat[i] = (int *)malloc(sizeof(int) * (max + 1));
		// 각 행의 열을 동적 할당 진행

	/* 인접 행렬과 전역 배열 초기화 */
	for (i = 0; i <= max; i++)
	{
		for (j = 0; j <= max; j++)
			adj_mat[i][j] = INF;
			// 모든 인접 행렬의 값을 INF로 초기화

		selected[i] = 0;
		// selected의 max번 째 인덱스 까지 0으로 초기화
		dist[i] = 0;
		// dist의 max번 째 인덱스 까지 0으로 초기화
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 파일의 끝까지 반복하는 반복문 */
	while(!feof(fp))
	{
		fscanf(fp, " %d %d %d", &u, &v, &weight);
		// 파일에서 간선의 정보를 읽어 각 변수에 저장

		/* 인접 행렬에 가중치 삽입 */
		adj_mat[u][v] = weight;
		adj_mat[v][u] = weight;
	}

	puts("- Prim의 최소 비용 신장 트리 프로그램 -\n");

	puts(">> 과정");
	prim(adj_mat, 0, max);
	// prim 함수 호출로 Prim의 최소 비용 신장 트리 알고리즘 수행

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	/* 인접 행렬의 행만큼 반복하는 반복문 */
	for (i = 0; i <= max; i++)
		free(adj_mat[i]);
		// 각 행의 열의 메모리 할당 해제

	free(adj_mat); // 인접 행렬 행의 메모리 할당 해제
	free(selected), free(dist); // 전역 배열 변수 메모리 할당 해제

	return 0; // 메인 함수 종료
}

/**
 * [get_min_vertex description]
 * @param  n [description]
 * @return   [description]
 */
int get_min_vertex(int n)
{
	int v, i;

	for (i = 0; i <= n; i++)
	{
		if (!selected[i])
		{
			v = i;
			break;
		}
	}

	for (i = 0; i <= n; i++)
	{
		if (!selected[i] && (dist[i] < dist[v]))
			v = i;
	}

	return v;
}

/**
 * [prim description]
 * @param adj_mat [description]
 * @param s       [description]
 * @param n       [description]
 */
void prim(int **adj_mat, int s, int n)
{
	int i, u, v;
	int cost = 0;

	int *visited = (int *)malloc(sizeof(int) * n);

	for (u = 0; u <= n; u++)
	{
		dist[u] = INF;
		selected[u] = FALSE;
	}

	dist[s] = 0;

	for (i = 0; i <= n; i++)
	{
		u = get_min_vertex(n);

		selected[u] = TRUE;

		if (dist[u] == INF)
			return;

		printf("%d >> ", i + 1);

		for (v = 0; v <= n; v++)
		{
			if (adj_mat[u][v] != INF)
			{
				if (!selected[v] && adj_mat[u][v] < dist[v])
				{
					dist[v] = adj_mat[u][v];
				}
			}
		}

		visited[i] = u;

		for (v = 0; v <= i; v++)
			printf("%d ", visited[v]);

		cost += dist[u];
		printf(": %d\n", cost);
	}

	printf("\n< 필요한 최소 비용 %d >\n", cost);
}
