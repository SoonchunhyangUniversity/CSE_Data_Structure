#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int search_binary(int *list, int key, int low, int high);

int main()
{
	int *arr = NULL;
	int i, input;
	int count = 0;
	int result = 0;

	double bs_result = 0;

	clock_t start, end;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		puts("File Open Error!");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		count++;
	}

	rewind(fp);

	arr = (int *)malloc(sizeof(int) * count);

	for (i = 0; i < count; i++)
	{
		fscanf(fp, " %d", &arr[i]);
	}

	printf("찾고자 하는 정수를 입력하세요 : ");
	scanf(" %d", &input);

	start = clock();
	result = search_binary(arr, input, 0, count - 1);
	end = clock();

	bs_result = (end - start) / CLOCKS_PER_SEC;

	if (result == -1)
		puts("\n<탐색 실패>");

	else
	{
		puts("\n<탐색 성공>");
		printf("%d 번째에 저장되어 있음\n", result);
	}

	printf("이진 탐색 실행 속도 : %lf\n", bs_result);

	free(arr);
	fclose(fp);

	return 0;
}

int search_binary(int *list, int key, int low, int high)
{
	int middle;

	while (low <= high)
	{
		middle = (low + high) / 2;

		if (key == list[middle])
			return middle;

		else if (key > list[middle])
			low = middle + 1;

		else
			high = middle - 1;
	}

	return -1;
}
