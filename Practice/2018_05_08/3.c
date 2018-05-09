/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 이중 연결 리스트
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 08
	*
*/

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

void display_add_reverse(DlistNode *phead)
{
	DlistNode *p;

	printf("< ");
	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("%d ", p->data);
	printf(">\n");

	printf("< ");
	for (p = phead->llink; p != phead; p = p->llink)
		printf("%d ", p->data);
	printf(">\n\n");
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

void delete_node(DlistNode *phead, int key)
{
	int check = 1;

	while (check)
	{
		check = 0;
		DlistNode *temp = phead;
		DlistNode *f = NULL;

		if (phead->data == key)
		{
			if (phead->rlink != NULL)
			{
				phead = phead->rlink;
				phead->llink = NULL;
			}

			else
				phead = NULL;

			check = 1;
			free(temp);
		}

		while (temp->rlink != phead)
		{
			if (temp->rlink->data == key)
			{
				f = temp->rlink;

				temp->rlink = temp->rlink->rlink;
				temp->rlink->llink = temp;

				free(f);
				check = 1;
			}
			temp = temp->rlink;
		}
	}
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

	do
	{
		printf("지울 값을 입력하세요(0 : 종료) : ");
		scanf("%d", &input);

		if (input == 0)
			break;

		delete_node(&list, input);
		display_add_reverse(&list);

	} while (input != 0);

	fclose(fp);

	return 0;
}
