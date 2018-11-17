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

int *selected; // 선택된 정점인지 확인할 배열을 동적 할당할 전역 변수
int *dist; // 간선의 최솟값을 저장 할 배열을 동적 할당할 전역 변수

/* 최소 비용의 정점을 반환하는 함수 */
int get_min_vertex(int n);
/* Prim의 최소 비용 신장 트리 알고리즘 함수 */
void prim(int **adj_mat, int s, int n);

int main()
{
	int **adj_mat;
	// 인접 행렬 그래프 배열을 동적 할당 할 이중 포인터 변수 선언
	int i, j;
	// 반복문에서 사용 할 변수 선언
	int u, v, weight;
	// 정점의 정보와 가중치를 저장할 변수 선언
	int max = INT_MIN;
	// 정점의 숫자의 최댓값을 저장 할 변수 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data3.txt를 읽기모드로 연다. */
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
 * [get_min_vertex 함수]
 * @param  n [최대 정점 번호]
 * @return   [최소값을 갖는 정점]
 */
int get_min_vertex(int n)
{
	int v, i;
	// 정점의 정보를 저장 할 변수 v, 반복문에서 사용 할 변수 i 선언

	for (i = 0; i <= n; i++)
	{
		/* 아직 선택되지 않은 정점일 경우 */
		if (!selected[i])
		{
			v = i; // v에 정점 번호 저장
			break;
		}
	}

	/* 최대 정점의 번호만큼 반복하는 반복문 */
	for (i = 0; i <= n; i++)
	{
		/* 선택되지 않은 정점이면서 최소 거리 탐색 */
		if (!selected[i] && (dist[i] < dist[v]))
			v = i; // 정점 번호 저장
	}

	return v; // 정점 번호 반환
}

/**
 * [prim 함수]
 * @param adj_mat [인접 행렬 그래프]
 * @param s       [시작 정점 번호]
 * @param n       [최대 정점 번호]
 */
void prim(int **adj_mat, int s, int n)
{
	int i, u, v;
	// 정점의 번호를 저장 할 변수와 반복문에서 사용 할 변수 선언
	int cost = 0;
	// 비용을 저장할 변수 선언 및 초기화

	int *visited = (int *)malloc(sizeof(int) * n);
	// 방문한 순서를 저장 할 포인터 변수 선언 및 동적 할당

	/* 전역 배열을 초기화 하는 반복문 */
	for (u = 0; u <= n; u++)
	{
		dist[u] = INF;
		selected[u] = FALSE;
	}

	dist[s] = 0; // 시작 정점의 거리 초기화

	for (i = 0; i <= n; i++)
	{
		u = get_min_vertex(n);
		// get_min_vertex 함수 호출로 반환된 정점 번호 u에 저장

		selected[u] = TRUE;
		// 정점 u 방문 표시

		/* 경로가 없을 경우 */
		if (dist[u] == INF)
			return; // 함수 종료

		printf("%d >> ", i + 1); // 방문한 정점 표시

		for (v = 0; v <= n; v++)
		{
			/* 선택된 정점을 기준으로 연결되어 있는 모든 정점 거리 비교 */
			if (adj_mat[u][v] != INF)
			{
				/* 아직 선택되지 않았으며 거리가 작을 경우 */
				if (!selected[v] && adj_mat[u][v] < dist[v])
				{
					dist[v] = adj_mat[u][v];
					// dist[v]값 갱신
				}
			}
		}

		visited[i] = u;
		// 방문한 순서를 저장

		/* 지금까지 방문한 순서를 출력하는 반복문 */
		for (v = 0; v <= i; v++)
			printf("%d ", visited[v]);

		cost += dist[u];
		// 현재까지의 최소비용 증가
		printf(": %d\n", cost);
		// 현재 최소 비용 출력
	}

	printf("\n< 필요한 최소 비용 %d >\n", cost);
	// 모든 정점을 탐색했을 때 최소 비용 출력
}
