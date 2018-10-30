#include <stdio.h>
#include <stdlib.h>

void merge(int arr[], int left, int mid, int right);
void merge_sort(int arr[], int left, int right);
void display(int arr[], int count);

int main()
{
	int *arr = NULL;
	int i;
	int count = 0;

	FILE *fp = fopen("data2.txt", "r");

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

	puts("<< 정렬되지 않은 리스트 >>");
	display(arr, count);
	puts("");

	puts("<< 정렬 과정>>");
	puts("------------------------------------");
	merge_sort(arr, 0, count - 1);
	puts("------------------------------------\n");

	puts("<< 정렬된 리스트 >>");
	display(arr, count);

	free(arr);
	fclose(fp);

	return 0;
}

void merge(int arr[], int left, int mid, int right)
{
	int fIdx = left;
	int rIdx = mid + 1;
	int i;

	int *sortArr = (int*)malloc(sizeof(int) * (right + 1));
	int sIdx = left;

	while (fIdx <= mid && rIdx <= right)
	{
		if (arr[fIdx] <= arr[rIdx])
		{
			sortArr[sIdx] = arr[fIdx++];
		}

		else
		{
			sortArr[sIdx] = arr[rIdx++];
		}

		sIdx++;
	}

	if (fIdx > mid)
	{
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}
	else
	{
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
	}

	printf("Left list : ");

	for (i = left; i <= mid; i++)
		printf(" %d", arr[i]);

	printf("\n");

	printf("Right list : ");

	for (i = mid + 1; i <= right; i++)
		printf(" %d", arr[i]);

	printf("\n");


	for (i = left; i <= right; i++)
		arr[i] = sortArr[i];

	free(sortArr);
}

void merge_sort(int arr[], int left, int right)
{
	int mid;
	int i;

	if (left < right)
	{
		/* 중간 지점을 계산한다 */
		mid = (left + right) / 2;

		/* 둘로 나눠서 각각을 정렬한다 */
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		/* 정렬된 두 배열을 병합한다 */
		merge(arr, left, mid, right);

		printf("Sorted list : ");
		for (i = left; i <= right; i++)
			printf(" %d", arr[i]);

		printf("\n\n");
	}
}

void display(int arr[], int count)
{
	int i;

	for (i = 0; i < count; i++)
	{
		printf("<%d> ", arr[i]);
	}

	printf("\n");
}
