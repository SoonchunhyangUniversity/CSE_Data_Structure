#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int data_count = 0;

typedef int element;

typedef struct ListNode
{
	element data;
	struct ListNode *link;
} ListNode;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/*
phead : 리스트의 헤드 포인터의 포인터
p : 선행 노트
new_node : 삽입될 노드
*/
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}

	data_count++;
}

/*
phead : 헤드 포인터의 포인터
p : 삭제될 노드의 선행 노트
removed : 삭제될 노드
*/
void remove_node(ListNode **phead, ListNode *p, ListNode *remove)
{
	if (p == NULL)
		*phead = (*phead)->link;
	else
		p->link = remove->link;

	free(remove);

	data_count--;
}

void display(ListNode *head)
{
	ListNode *p = head;

	while (p != NULL)
	{
		printf("< %d >", p->data);
		p = p->link;
	}
	printf("\n");
}

void display_recur(ListNode *head)
{
	ListNode * p = head;

	if (p != NULL)
	{
		printf("%d->", p->data);

		display_recur(p->link);
	}
}

ListNode *search(ListNode *head, int x)
{
	ListNode *p;
	p = head;

	while (p != NULL)
	{
		if (p->data == x)
			return p; // 탐색 성공

		p = p->link;
	}

	return p; // 탐색 실패일 경우 NULL 반환
}

/*
head1 = (a1, a2, ..., an) head2 = (b1, b2, ..., bn)을
(a1, ..., an, b1, ..., bn)으로 변환
*/
ListNode *concat(ListNode *head1, ListNode *head2)
{
	ListNode *p;

	if (head1 == NULL)
		return head2;
	else if (head2 == NULL)
		return head1;
	else
	{
		p = head1;

		while (p->link != NULL)
		{
			p = p->link;
			p->link = head2;

			return head1;
		}
	}
}

/* (e1, e2, ... en)을 (en, en-1, ..., e1)로 변환 */
ListNode *reverse(ListNode * head)
{
	// 순회 포인터로 p, q, r을 사용
	ListNode *p, *q, *r;
	p = head; // p는 아직 처리되지 않은 노드
	q = NULL; // q는 역순으로 만들 노드

	while (p != NULL)
	{
		r = q; // r은 역순으로 된 노드
		q = p; // r은 q, q는 p를 차례로 따라간다.
		p = p->link;
		q->link = r; // q의 링크 방향을 바꾼다.
	}

	return q; // q는 역순으로 된 리스트의 헤드포인터
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));

	if (new_node == NULL)
		error("메모리 할당 에러");

	new_node->data = data;
	new_node->link = link;

	return (new_node);
}

int func_compare(const void * first, const void * second)
{
	if (*(int*)first > *(int *)second)
		return 1;
	else if (*(int*)first < *(int *)second)
		return -1;
	else
		return 0;
}

void sort(ListNode *phead)
{
	ListNode *i = phead;
	int idx = 0, j;
	int iTemp[100] = { 0 };

	while (i != NULL)
	{
		iTemp[idx] = i->data;
		idx++;
		i = i->link;
	}

	i = phead;

	qsort(iTemp, data_count, sizeof(int), func_compare);

	if (i == NULL)
		return;
	else
	{
		j = 0;
		for (; i; i = i->link)
		{
			i->data = iTemp[j];
			j++;
		}
	}
}

int main()
{
	int num;
	int i;
	ListNode *list = NULL;

	srand((unsigned)time(NULL));

	printf("생성할 노드의 갯수를 입력하세요 : ");
	scanf("%d", &num);
	printf("\n");

	for(i = 0; i < num; i++)
		insert_node(&list, NULL, create_node(rand() % 100 + 1, NULL));

	printf("생성된 리스트\n");
	display(list);
	printf("\n");
	printf("정렬된 리스트\n");
	sort(list);
	display(list);

	return 0;
}
