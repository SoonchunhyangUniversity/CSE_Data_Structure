/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : Prim의 MST 알고리즘
 * 작성일 : 2018-11-06
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1
#define FALSE 0
#define INF 1000L

int *selected;
int *dist;

int get_min_vertex(int n);
void prim(int **adj_mat, int s, int n);

int main()
{
	int **adj_mat;
	int i, j;
	int u, v, weight;
	int max = INT_MIN;

	/* 파일 fp 선언 및 data3.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d %d %d", &u, &v, &weight);

		if (max < u)
			max = u;

		if (max < v)
			max = v;
	}

	selected = (int *)malloc(sizeof(int) * (max + 1));
	dist = (int *)malloc(sizeof(int) * (max + 1));

	adj_mat = (int **)malloc(sizeof(int *) * (max + 1));

	for (i = 0; i <= max; i++)
		adj_mat[i] = (int *)malloc(sizeof(int) * (max + 1));

	for (i = 0; i <= max; i++)
	{
		for (j = 0; j <= max; j++)
			adj_mat[i][j] = INF;

		selected[i] = 0;
		dist[i] = 0;
	}

	rewind(fp);

	while(!feof(fp))
	{
		fscanf(fp, " %d %d %d", &u, &v, &weight);
		adj_mat[u][v] = weight;
		adj_mat[v][u] = weight;
	}

	puts("- Prim의 최소 비용 신장 트리 프로그램 -\n");

	puts(">> 과정");
	prim(adj_mat, 0, max);

	fclose(fp); // 열어준 파일 포인터 fp를 닫는다.

	for (i = 0; i <= max; i++)
		free(adj_mat[i]);

	free(adj_mat);
	free(selected), free(dist);

	return 0; // 메인 함수 종료
}

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
