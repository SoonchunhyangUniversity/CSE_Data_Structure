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
void Insert(ArrayBaseList *plist,int position, Data data);
void display(ArrayBaseList *plist);
void delete(ArrayBaseList *plist, int position);
int is_in(ArrayBaseList *plist, Data find_data);
int is_full(ArrayBaseList *plist);
int is_empty(ArrayBaseList *plist);

int main()
{
	ArrayBaseList list;
	int test_case, i;

	srand((unsigned)time(NULL));

	printf("생성할 랜덤 숫자 개수를 입력하세요 : ");
	scanf("%d", &test_case);

	init(&list);

	for (i = 0; i < test_case; i++)
	{
		Insert(&list, i, (rand() % 999 + 1));
	}
	printf("[ 배열로 구현된 연결리스트에 추가된 데이터 ]\n");
	display(&list);
	printf("\n");

	return 0;
}

void init(ArrayBaseList *plist)
{
	plist->length = 0;
}

void Insert(ArrayBaseList *plist,int position, Data data)
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

void display(ArrayBaseList *plist)
{
	int i, j;
	int check = 0;
	int max = plist->arr[0];
	int min = plist->arr[0];

	for (i = 0; i < plist->length; i++)
	{
		for (j = 0; j < plist->length; j++)
		{
			if (max < plist->arr[i])
				max = plist->arr[i];
			if (min > plist->arr[i])
				min = plist->arr[i];
		}
	}

	for (i = 0; i < plist->length; i++)
	{
		printf("%3d\t", plist->arr[i]);

		if ((i + 1) % 15 == 0 && i != 0)
		{
			while (TRUE)
			{
				if (plist->arr[check] == max)
					printf("MAX\t");
				else if (plist->arr[check] == min)
					printf("MIN\t");
				else
					printf("\t");

				check++;

				if (check % 15 == 0)
				{
					printf("\n");
					break;
				}
			}
		}
	}
}

void delete(ArrayBaseList *plist, int position)
{
	int i;
	Data item;

	if (position < 0 || position >= plist->length)
		printf("ERROR!\n");

	item = plist->arr[position];

	for (i = position; i < (plist->length - 1); i++)
		plist->arr[i] = plist ->arr[i + 1];

	plist->length--;

	return item;
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
