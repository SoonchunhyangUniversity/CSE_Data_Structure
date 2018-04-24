#include <stdio.h>
#define MAX 100

typedef int Data;

typedef struct _arraybaselist
{
	Data data[MAX];
	int length;
}ArrayBaseList;

void BubbleSort(Data *arr, int len)
{
	int temp;

	for (int i = 0; i < len; i++)
	{
		for (int j = i; j < len; j++)
		{
			if (arr[i] > arr[j])
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

Data Get_num(int num)
{
	int result = 0;
    
	if (num / 10000000 == 1)
	{
		result = 2 * 2 * 2 * 2 * 2 * 2 * 2;
		return result + Get_num(num % 100000000);
	}
	else if (num / 1000000 == 1)
	{
		result = 2 * 2 * 2 * 2 * 2 * 2;
		return result + Get_num(num % 10000000);
	}
	else if (num / 100000 == 1)
	{
		result = 2 * 2 * 2 * 2 * 2;
		return result + Get_num(num % 100000);
	}
	else if (num / 10000 == 1)
	{
		result = 2 * 2 * 2 * 2;
		return result + Get_num(num % 10000);
	}
	else if (num / 1000 == 1)
	{
		result = 2 * 2 * 2;
		return result + Get_num(num % 1000);
	}
	else if (num / 100 == 1)
	{
		result = 2 * 2;
		return result + Get_num(num % 100);
	}
	else if (num / 10 == 1)
	{
		result = 2;
		return result + Get_num(num % 10);
	}
	else if (num == 1)
		return 1;
}

int main()
{
	ArrayBaseList list;
	int temp;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* list Init */
	list.length = 0;

	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		list.data[list.length++] = Get_num(temp);
	}

	printf("- 리스트의 정렬 전 데이터 -\n");
	for (int i = 0; i < list.length; i++)
	{
		printf("< ");
		printf("%d", list.data[i]);
		printf(" > ");
	}
	printf("\n");

	BubbleSort(list.data, list.length);

	printf("- 리스트의 정렬 후 데이터 -\n");
	for (int i = 0; i < list.length; i++)
	{
		printf("< ");
		printf("%d", list.data[i]);
		printf(" > ");
	}
	printf("\n");

	fclose(fp);

	return 0;
}
