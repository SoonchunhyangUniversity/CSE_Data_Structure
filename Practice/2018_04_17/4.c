/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열로 구현된 연결리스트 4
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
void delete(ArrayBaseList *plist, int position);
int is_in(ArrayBaseList *plist, Data find_data);
int is_full(ArrayBaseList *plist);
int is_empty(ArrayBaseList *plist);

int main()
{
	ArrayBaseList *list;
	ArrayBaseList struct_temp;
	int i, j, temp, count = 0;
	int input, check;

	FILE *fp = fopen("data4.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %d %d%d", &temp, &temp, &temp, &temp);
		count++;
	}

	list = (ArrayBaseList *)malloc(sizeof(ArrayBaseList) * count);

	rewind(fp);

	for(i = 0; i < count; i++)
		init(&list[i]);

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < 4; j++)
		{
			fscanf(fp, "%d", &temp);
			Insert(&list[i], j, temp);
		}
		list[i].arr[list[i].length] = (list[i].arr[1] + list[i].arr[2] + list[i].arr[3]);
	}

	printf("Before Sorting!!\n");
	printf("학번\t\t 국어\t 영어\t 수학\t 총점\t 평균\n");
	for (i = 0; i < count; i++)
		display(&list[i]);

	printf("\n");;

	struct_temp = list[0];

	for (i = 0; i < count; i++)
	{
		for (j = i; j < count; j++)
		{
			if (list[i].arr[4] < list[j].arr[4])
			{
				struct_temp = list[i];
				list[i] = list[j];
				list[j] = struct_temp;
			}
		}
	}

	printf("After Sorting!!\n");
	printf("학번\t\t 국어\t 영어\t 수학\t 총점\t 평균\n");
	for (i = 0; i < count; i++)
		display(&list[i]);


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
	int sum = 0;
	double avg;

	for (i = 0; i < plist->length; i++)
	{
		printf("%d\t", plist->arr[i]);
		if (i != 0)
		{
			sum += plist->arr[i];
		}
	}
	printf("%d\t %.2f\t\n", sum, (double)sum / 3);
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
