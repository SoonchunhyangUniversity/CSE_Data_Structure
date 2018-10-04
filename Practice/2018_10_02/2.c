/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 손님 관리 프로그램
 * 작성일 : 2018-10-02
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 200

typedef struct _TreeNode
{
	char name[MAX];
	struct _TreeNode *left;
	struct _TreeNode *right;
} TreeNode;;

typedef struct
{
	int key;
	char name[MAX];
} element;

typedef struct _HeapType
{
	element heap[MAX];
	int heap_size;
} HeapType;

void insert_min_heap(HeapType *h, element item);
void display(HeapType *h, int idx);
void init(HeapType *h);
TreeNode *make_tree(TreeNode *left, TreeNode *right);
element delete_min_heap(HeapType *h);

int main()
{
	char oper;
	int key = 0;
	element temp;
	HeapType heap;

	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	init(&heap);

	while (!feof(fp))
	{
		fscanf(fp, " %c", &oper);

		if (oper == 'i')
		{
			fscanf(fp, "%s", temp.name);
			temp.key = ++key;

			insert_min_heap(&heap, temp);

			printf(">> 손님(%s) 입장\n", temp.name);
			printf("< 히프 중위 순회 출력 >\n");
			display(&heap, 1);
			printf("\n");
		}

		else if (oper == 'o')
		{
			temp = delete_min_heap(&heap);
			key--;

			printf(">> 손님(%s) 퇴장\n", temp.name);
			printf("< 히프 중위 순회 출력 >\n");
			display(&heap, 1);
			printf("\n");
		}

		else
		{
			printf("OPER INPUT ERROR!\n");
			return 0;
		}
	}

	fclose(fp);

	return 0;
}

void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void display(HeapType *h, int idx)
{
	if (idx > h->heap_size)
		return;

	display(h, 2 * idx);
	printf("%d - %s\n", h->heap[idx].key, h->heap[idx].name);
	display(h, 2 * idx + 1);
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

TreeNode *make_tree(TreeNode *left, TreeNode *right)
{
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));

	if (node == NULL)
	{
		printf("MALLOC ERROR!\n");
		exit(1);
	}

	node->left = left;
	node->right = right;

	return node;
}

element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1, child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;

		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;

	for(int i = h->heap_size; i > 0; i--)
		h->heap[i].key--;

	return item;
}
