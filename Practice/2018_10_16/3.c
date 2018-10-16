#include <stdio.h>
#include <stdlib.h>

void Swap(int arr[], int idx1, int idx2);
void QuickSort(int arr[], int left, int right);
void Display(int arr[], int count);
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
	Display(arr, count);
	printf("\n");

	printf("\n< 정렬 과정 >\n");
	QuickSort(arr, 0, count - 1);

	printf("\n< 정렬된 리스트 >\n");
	Display(arr, count);
	printf("\n");

	fclose(fp);

	return 0;
}

void Swap(int arr[], int idx1, int idx2)
{
	int temp = arr[idx1];
	arr[idx1] = arr[idx2];
	arr[idx2] = temp;
}

void QuickSort(int arr[], int left, int right)
{
	if (left <= right)
	{
		int pivot = Partition(arr, left, right); // 둘로 나눠서
		QuickSort(arr, left, pivot - 1); // 왼쪽 영역을 정렬
		QuickSort(arr, pivot + 1, right); // 오른쪽 영역을 정렬
	}
}

void Display(int arr[], int count)
{
	int i;

	for (i = 0; i < count; i++)
		printf("%d > ", arr[i]);
}

int Partition(int arr[], int left, int right)
{
	int pivot = arr[left];	// 피벗의 위치는 가장 왼쪽
	int low = left + 1;
	int high = right;
	int check = 0;

	while (low <= high)	// 교차되지 않을 때 까지 반복
	{
		if (check == 0)
		{
			printf("- Pivot : %d -\n", pivot);
			check = pivot;
		}

		printf("low : %d high : %d [", arr[low], arr[high]);
		Display(arr, (low + high) / 2);
		printf("]\n\n");

		/* 피벗보다 큰 값을 찾는 과정 */
		while (pivot >= arr[low] && low <= right)
			low++;	// low를 오른쪽으로 이동

		/* 피벗보다 작은 값을 찾는 과정 */
		while (pivot <= arr[high] && high >= (left + 1))
			high--;	// high를 왼쪽으로 이동

		/* 교차되지 않은 상태라면 Swap 실행 */
		if (low <= high)
			Swap(arr, low, high);
	}

	Swap(arr, left, high); // 피벗과 high가 가리키는 대상 교환
	return high; // 옮겨진 피벗의 위치정보 반환
}
