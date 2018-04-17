/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열로 구현된 연결리스트 2
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 17
	*
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define TRUE 1

typedef int Data;

typedef struct _arraybaselist
{
	Data arr[MAX];
	int length;
} ArrayBaseList;

void init(ArrayBaseList *plist);
void Insert(ArrayBaseList *plist, int position, Data data);
void display(ArrayBaseList *plist);
Data delete(ArrayBaseList *plist, int position);
int is_in(ArrayBaseList *plist, Data find_data);
int is_full(ArrayBaseList *plist);
int is_empty(ArrayBaseList *plist);

int main()
{
	ArrayBaseList list;
	int i, temp, count = 0;
	int input, check;

	FILE *fp = fopen("data2.txt", "r");

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

	while (TRUE)
	{
		printf("값을 입력하세요<종료 : 0> : ");
		scanf("%d", &input);

		if (input == 0)
			break;

		check = 0;

		printf("%d은(는) 리스트", input);
		for (i = 0; i < list.length; i++)
		{
			if (list.arr[i] == input)
			{
				printf("%d ", i + 1);
				check = 1;
			}
		}
		if (check == 1)
			printf("번째에 있습니다.\n\n");
		else
			printf("에 없습니다.\n\n");
	}

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

Data delete(ArrayBaseList *plist, int position)
{
	int i;
	Data item;

	if (position < 0 || position >= plist->length)
		printf("ERROR!\n");

	item = plist->arr[position];

	for (i = position; i < (plist->length - 1); i++)
		plist->arr[i] = plist->arr[i + 1];

	plist->length--;

	return item;
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
