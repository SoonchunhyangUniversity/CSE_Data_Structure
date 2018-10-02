#include <stdio.h>
#define MAX 200

typedef struct
{
	int key;
	char name[MAX];
} element;

typedef struct
{
	element heap[MAX];
	int heap_size;
} HeapType;

void insert_max_heap(HeapType *h, element item);
void init(HeapType *h);
void inorder(HeapType *h, int idx);
element delete_max_heap(HeapType *h);

int main()
{
	element temp;
	HeapType heap;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	init(&heap);

	while (!feof(fp))
	{
		fscanf(fp, "%d %s", &temp.key, temp.name);
		insert_max_heap(&heap, temp);
	}

	printf("우선 순위 큐에 데이터를 넣을 동물의 우선순위오 이름을 입력하시오(완료시 우선순위 : 0)\n");

	printf(">> ");
	scanf("%d %s", &temp.key, temp.name);
	insert_max_heap(&heap, temp);

	printf(">> ");
	scanf("%d %s", &temp.key, temp.name);
	insert_max_heap(&heap, temp);

	printf("\n< 만들어진 우선 순위 큐 데이터 출력 >\n");

	for (int i = heap.heap_size; i > 0; i--)
	{
		temp = delete_max_heap(&heap);
		printf("%d - %s\n", temp.key, temp.name);
	}

	fclose(fp);

	return 0;
}

void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key > h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}

	h->heap[i] = item;
}

void init(HeapType *h)
{
	h->heap_size = 0;
}

element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1, child = 2;

	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;

		if (temp.key >= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}

	h->heap[parent] = temp;

	return item;
}
