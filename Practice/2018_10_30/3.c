#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50

typedef struct _graphnode
{
	int vertex;
	struct _graphnode *link;
} GraphNode;

typedef struct _graphtype
{
	int n;
	GraphNode *adj_list[MAX_VERTICES];
} Graph;

void graph_init(Graph *g);
void insert_vertex(Graph *g, int v);
void insert_edge(Graph *g, int u, int v);
void dfs_list(Graph *g, int v);

int visited[MAX_VERTICES];

int main()
{
	int i;
	int v, u;
	char c;

	Graph g;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		puts("FILE OPEN ERRO!");
		return 0;
	}

	graph_init(&g);

	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);

		if (c == 'v')
		{
			fscanf(fp, " %d", &v);
			insert_vertex(&g, v);
		}

		else if (c == 'e')
		{
			fscanf(fp, " %d %d", &u, &v);
			insert_edge(&g, u, v);
		}

		else
		{
			printf("'%c' OPERATION ERROR!\n", c);
			return 0;
		}
	}

	puts("- 그래프 깊이 우선 탐색 결과 -");
	printf("<");

	dfs_list(&g, 0);
	printf(" >\n");

	fclose(fp);

	return 0;
}

void graph_init(Graph *g)
{
	int v;

	g->n = 0;

	for (v = 0; v < MAX_VERTICES; v++)
		g->adj_list[v] = NULL;
}

void insert_vertex(Graph *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		puts("GRAPH VERTEX EXCEEDED");
		return;
	}

	g->n++;
}

void insert_edge(Graph *g, int u, int v)
{
	GraphNode *node, *p;

	if (u > g->n || v > g->n)
	{
		puts("GRAPH VERTEX NUMBER ERROR!");
		return;
	}

	node = (GraphNode *)malloc(sizeof(GraphNode));

	node->vertex = v;
	node->link = NULL;

	p = g->adj_list[u];

	if (p == NULL)
	{
		node->link = g->adj_list[u];
		g->adj_list[u] = node;
	}

	else
	{
		while (p->link != NULL)
		{
			if (p->link != NULL)
			{
				if (p->link->vertex > node->vertex)
					break;
			}

			p = p->link;
		}

		p->link = node;
	}
}

void dfs_list(Graph *g, int v)
{
	GraphNode *w;

	visited[v] = TRUE;

	printf(" %d", v);

	for (w = g->adj_list[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
	}
}
