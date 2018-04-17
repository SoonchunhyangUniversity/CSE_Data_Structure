#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 1000
#define TRUE 1

typedef int Data;

typedef struct _arraybaselist
{
	Data arr[1000];
	int length;
} ArrayBaseList;

void init(ArrayBaseList *plist);
void Insert(ArrayBaseList *plist, int position, Data data);
void display(ArrayBaseList *plist);
void delete(ArrayBaseList *plist);
int is_in(ArrayBaseList *plist, Data find_data);
int is_full(ArrayBaseList *plist);
int is_empty(ArrayBaseList *plist);

int main()
{
	ArrayBaseList list;
	int i, temp, count = 0;
	int input, check;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	init(&list);

	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		count++;
	}

	rewind(fp);

	for (i = 0; i < count; i++)
	{
		fscanf(fp, "%d", &temp);
		Insert(&list, i, temp);
	}

	display(&list);
	printf("\n");
	delete(&list);
	display(&list);
	printf("\n");

	return 0;
}

void init(ArrayBaseList *plist)
{
	plist->length = 0;
}

void Insert(ArrayBaseList *plist, int position, Data data)
{
	if (!is_full(plist) && (position >= 0) && (position <= plist->length))
	{
		int i;
		for (i = (plist->length - 1); i >= position; i--)
			plist->arr[i + 1] = plist->arr[i];

		plist->arr[position] = data;
		plist->length++;
	}
}

void delete(ArrayBaseList *plist)
{
	int i, j;

	for (i = 0; i < (plist->length - 1); i++)
	{
		if (!(i % 2 == 0))
		{
			for (j = i; j < (plist->length - 1); j++)
			{
				plist->arr[j] = plist->arr[j + 1];
			}
			plist->length--;
		}
	}

}

void display(ArrayBaseList *plist)
{
	int i;
	for (i = 0; i < plist->length; i++)
		printf("%d->", plist->arr[i]);
}

int is_in(ArrayBaseList *plist, Data find_data)
{
	int i;

	for (i = 0; i < MAX; i++)
	{
		if (plist->arr[i] == find_data)
			return i;
	}

	return -1;
}

int is_full(ArrayBaseList *plist)
{
	return plist->length == MAX;
}

int is_empty(ArrayBaseList *plist)
{
	return plist->length == 0;
}
