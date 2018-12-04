/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 반복을 이용한 이진 탐색
 * 작성일 : 2018-12-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <time.h> // 탐색 시간을 측정하기 위한 헤더파일 선언

/* 이진 탐색 함수 */
int search_binary(int *list, int key, int low, int high);

int main()
{
	int *arr = NULL;
    // 데이터를 동적 할당할 포인터 변수 선언 및 초기화
	int i, input;
    // 반복문에서 사용할 변수와 사용자에게 입력을 받을 변수 선언
	int count = 0;
    // 데이터의 개수를 저장할 변수 선언 및 초기화
	int result = 0;
    // 탐색 결과 인덱스를 저장할 변수 선언 및 초기화

	double bs_result = 0;
    // 이진 탐색 시간 결과를 저장할 변수 선언 및 초기화

	clock_t start, end;
    // 시작 시간과 종료 시간을 저장할 clock_t 구조체 선언

    /* 파일포인터 fp선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

    /* 파일을 여는데 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		puts("File Open Error!");
        exit(1); // 예외 출력 후 종료
	}

    /* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
        // 파일에서 정수형 데이터 하나를 읽어와 임시로 저장
		count++;
        // 데이터의 개수 1 증가
	}

	rewind(fp);
    // 파일 포인터의 위치를 처음으로 돌린다.

	arr = (int *)malloc(sizeof(int) * count);
    // 데이터의 개수의 배열 동적 할당 진행

    /* 데이터의 개수만큼 반복 */
	for (i = 0; i < count; i++)
	{
		fscanf(fp, " %d", &arr[i]);
		// 파일에서 데이터를 읽어와 배열에 저장
	}

    /* 사용자에게 탐색할 데이터를 입력받는다. */
	printf("찾고자 하는 정수를 입력하세요 : ");
	scanf(" %d", &input);

    /* 이진 탐색 알고리즘 실행 및 시간 계산 */
	start = clock();
    // 시작 시간 저장
	result = search_binary(arr, input, 0, count - 1);
    // 이진 탐색 알고리즘 실행 및 결과 저장
	end = clock();
    // 종료 시간 저장

	bs_result = (end - start) / CLOCKS_PER_SEC;
    // (종료 시간 - 시작 시간) / CLOCKS_PER_SEC 실행 시간 계산 후 저장

    /* 탐색에 실패했을 경우 */
	if (result == -1)
		puts("\n<탐색 실패>");

    /* 탐색에 성공했을 경우 */
	else
	{
		puts("\n<탐색 성공>");
		printf("%d 번째에 저장되어 있음\n", result);
	}

	printf("이진 탐색 실행 속도 : %lf\n", bs_result);

	free(arr);
    // 배열의 메모리 할당 해제
	fclose(fp);
    // 열어준 파일포인터 fp를 닫아준다.

	return 0;
    // 메인 함수 종료
}

/**
 * [search_binary 이진 탐색 함수]
 * @param  list [탐색할 배열]
 * @param  key  [탐색할 값]
 * @param  low  [제일 작은 인덱스]
 * @param  high [제일 큰 인덱스]
 * @return      [탐색 결과]
 */
int search_binary(int *list, int key, int low, int high)
{
	int middle;
    // 중간 인덱스를 저장할 변수 선언

    /* low에서 high까지 반복 */
	while (low <= high)
	{
		middle = (low + high) / 2;
        // 탐색할 배열의 중간 인덱스 계산 후 대입

        /* 값을 찾았을 경우 */
		if (key == list[middle])
			return middle;
            // 해당 인덱스 반환

        /* 찾으려는 값이 더 큰 경우 */
		else if (key > list[middle])
			low = middle + 1;
            // 반으로 나눈 배열의 오른쪽을 탐색하도록 low 변경

        /* 찾으려는 값이 더 작은 경우 */
		else
			high = middle - 1;
            // 반으로 나는 배열의 왼쪽을 탐색하도록 high 변경
	}

	return -1;
    // 탐색이 실패했을 경우 -1 반환
}
