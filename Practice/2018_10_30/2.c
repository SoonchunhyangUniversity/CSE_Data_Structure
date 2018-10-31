/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 합병 정렬 프로그램
 * 작성일 : 2018-10-30
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언

/* 합병 정렬에 사용 할 배열을 합병하는 함수 */
void merge(int arr[], int left, int mid, int right);
/* 배열을 합병 정렬하는 함수 */
void merge_sort(int arr[], int left, int right);
/* 배열의 데이터를 출력하는 함수 */
void display(int arr[], int count);

int main()
{
	int *arr = NULL;
	// 배열을 동적 할당 할 포인터 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언
	int count = 0;
	// 데이터의 개수를 저장 할 변수 선언

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기 모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!"); // 에러 메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		// fp에서 정수형 데이터를 하나 읽어온 후 임시로 i에 저장
		count++;
		// 데이터의 개수 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 확인 한 데이터의 개수를 토대로 배열 동적 할당 */
	arr = (int *)malloc(sizeof(int) * count);

	/* 데이터의 개수만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &arr[i]);
		// fp에서 데이터를 읽어와 배열의 i번째 인덱스에 저장

	/* display 함수를 호출하여 배열의 데이터 출력 */
	puts("<< 정렬되지 않은 리스트 >>");
	display(arr, count);
	puts("");

	/* merge_sort 함수를 호출하여 정렬 진행 및 과정 출력 */
	puts("<< 정렬 과정>>");
	puts("------------------------------------");
	merge_sort(arr, 0, count - 1);
	puts("------------------------------------\n");

	/* display 함수를 호출하여 배열의 데이터 출력 */
	puts("<< 정렬된 리스트 >>");
	display(arr, count);

	free(arr); // 동적 할당 한 배열의 메모리 할당 해제
	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/**
 * [merge 함수]
 * @param arr   [합병 할 배열]
 * @param left  [배열의 맨 왼쪽 인덱스]
 * @param mid   [배열의 가운데 인덱스]
 * @param right [배열의 맨 오른쪽 인덱스]
 */
void merge(int arr[], int left, int mid, int right)
{
	int fIdx = left;
	// 왼쪽 첫번째 인덱스를 저장할 변수 선언 및 초기화
	int rIdx = mid + 1;
	// 오른쪽 첫번째 인덱스를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	int *sortArr = (int *)malloc(sizeof(int) * (right + 1));
	// 정렬된 데이터를 저장할 결과 배열 선언 및 동적 할당
	int sIdx = left;
	// 결과 배열의 인덱스를 저장 할 변수 선언 및 초기화

	/* 반으로 분할 한 배열의 크기를 비교하는 반복문 */
	while (fIdx <= mid && rIdx <= right)
	{
		/* 절반 중 왼쪽의 첫번째 값 보다 오른쪽의 첫번째 값이
		   클때 결과 배열에 왼쪽 데이터 대입 및 왼쪽 인덱스 증가 */
		if (arr[fIdx] <= arr[rIdx])
			sortArr[sIdx] = arr[fIdx++];

		/* 절반 중 오른쪽의 첫번째 값이 왼쪽의 첫번째 값이
		   클때 결과 배열에 오른쪽 데이터 대입 및 오른쪽 인덱스 증가 */
		else
			sortArr[sIdx] = arr[rIdx++];

		sIdx++; // 결과 배열의 인덱스 1 증가
	}

	/* 왼쪽 배열의 값들이 모두 결과 배열에 저장되었을 경우 */
	if (fIdx > mid)
	{
		/* 남아있는 오른쪽 배열의 데이터의 개수만큼 반복 */
		for (i = rIdx; i <= right; i++, sIdx++)
			sortArr[sIdx] = arr[i];
			// 결과 배열에 남은 오른쪽 데이터 대입
	}

	/* 오른쪽 배열의 값들이 모두 결과 배열에 저장되었을 경우 */
	else
	{
		/* 남아있는 왼쪽 배열의 데이터의 개수만큼 반복 */
		for (i = fIdx; i <= mid; i++, sIdx++)
			sortArr[sIdx] = arr[i];
			// 결과 배열에 남은 왼쪽 데이터 대입
	}

	/* 정렬된 왼쪽 배열의 데이터 출력 */
	printf("Left list : ");

	for (i = left; i <= mid; i++)
		printf(" %d", arr[i]);

	printf("\n");

	/* 정렬된 오른쪽 배열의 데이터 출력 */
	printf("Right list : ");

	for (i = mid + 1; i <= right; i++)
		printf(" %d", arr[i]);

	printf("\n");


	/* 결과 배열의 데이터 개수만큼 반복 */
	for (i = left; i <= right; i++)
		arr[i] = sortArr[i]; // 기존 배열에 대입

	free(sortArr); // 결과 배열 메모리 할당 해제
}

/**
 * [merge_sort 함수]
 * @param arr   [정렬 할 배열]
 * @param left  [배열의 맨 왼쪽 인덱스]
 * @param right [배열의 맨 오른쪽 인덱스]
 */
void merge_sort(int arr[], int left, int right)
{
	int mid;
	// 중간 지점을 저장할 변수 선언
	int i;
	// 반복문에서 사용할 변수 선언

	/* left가 right보다 크거나 같아지면 탈출 */
	if (left < right)
	{
		/* 중간 지점을 계산한다 */
		mid = (left + right) / 2;

		/* 둘로 나눠서 각각을 정렬한다 */
		merge_sort(arr, left, mid);
		merge_sort(arr, mid + 1, right);

		/* 정렬된 두 배열을 합병한다 */
		merge(arr, left, mid, right);

		/* 합병 후 정렬 된 배열의 데이터 출력 */
		printf("Sorted list : ");
		for (i = left; i <= right; i++)
			printf(" %d", arr[i]);

		printf("\n\n");
	}
}

/**
 * [display 함수]
 * @param arr   [배열]
 * @param count [배열의 데이터 개수]
 */
void display(int arr[], int count)
{
	int i;
	// 반복문에서 사용 할 변수 선언

	/* 데이터의 개수만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
	{
		printf("<%d> ", arr[i]);
		// 배열의 데이터 출력
	}

	printf("\n");
}
