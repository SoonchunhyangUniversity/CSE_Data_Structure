#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct DlistNode
{
	element data;
	struct DlistNode *llink;
	struct DlistNode *rlink;
} DlistNode;

/* 이중 연결 리스트를 초기화 */
void init(DlistNode *phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

/* 이중 연결 리스트의 노드를 출력 */
void display(DlistNode *phead)
{
	DlistNode *p;

	printf("< ");

	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("%d ", p->data);

	printf(">\n");
}

DlistNode *create_node(element data)
{
	DlistNode *new_node = (DlistNode *)malloc(sizeof(DlistNode));

	new_node->data = data;
	new_node->llink = NULL;
	new_node->rlink = NULL;

	return new_node;
}


/* 노드 new_node를 노드 before의 왼쪽에 삽입 */
void dinsert_node(DlistNode *before, DlistNode * new_node)
{
	new_node->rlink = before;
	new_node->llink = before->llink;
	before->llink->rlink = new_node;
	before->llink = new_node;
}

/* 노드 removed를 삭제 */
void dremove_node(DlistNode *phead_node, DlistNode *removed)
{
	if (removed == phead_node)
		return;

	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;

	free(removed);
}

int main()
{
	int data, input;
	DlistNode list;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	init(&list);

	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		dinsert_node(&list, create_node(data));
	}

	display(&list);

	return 0;
}
