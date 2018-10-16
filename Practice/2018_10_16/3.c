#include <stdio.h>
#include <stdlib.h>

void Swap(int *a, int *b);
void QuickSort(int arr[], int left, int right);
void Display(int arr[], int start, int count);
int Partition(int arr[], int left, int right);

int main()
{
	int *arr = NULL;
	int count = 0;
	int i;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		count++;
	}

	rewind(fp);

	arr = (int *)malloc(sizeof(int) * count);

	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &arr[i]);

	printf("< 정렬되지 않은 리스트 >\n");
	Display(arr, 0, count);
	printf("\n");

	printf("\n< 정렬 과정 >\n");
	QuickSort(arr, 0, count - 1);

	printf("\n< 정렬된 리스트 >\n");
	Display(arr, 0, count);
	printf("\n");

	fclose(fp);

	return 0;
}

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void QuickSort(int arr[], int left, int right)
{
	/* right가 left보다 크면 실행 */
	if (left <= right)
	{
		int pivot = Partition(arr, left, right);
		// 둘로 나눠서
		QuickSort(arr, left, pivot - 1);
		// 왼쪽 영역을 정렬
		QuickSort(arr, pivot + 1, right);
		// 오른쪽 영역을 정렬
	}
}

void Display(int arr[], int start, int count)
{
	int i;

	for (i = start; i < count; i++)
	{
		if (i == count - 1)
			printf("%d", arr[i]);

		else
			printf("%d > ", arr[i]);
	}
}

int Partition(int arr[], int left, int right)
{
	int pivot;
	int low = left, high = right + 1;
	int now = 0;
	pivot = arr[left];

	do
	{
		do
			low++;
		while (low <= right && arr[low] < pivot);

		do
			high--;
		while (high >= left && arr[high] > pivot);

		if (pivot != arr[high])
		{
			if (now != pivot)
			{
				printf("- Pivot : %d -\n", pivot);
				now = pivot;
			}

			printf("low : %d high : %d  [", arr[low], arr[high]);
			Display(arr, left, right + 1);
			printf("]\n\n");
		}

		if (low < high)
			Swap(&arr[low], &arr[high]);

	} while (low < high);

	Swap(&arr[left], &arr[high]);

	return high;
}
