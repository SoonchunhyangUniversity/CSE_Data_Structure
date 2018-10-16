/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 선택 정렬 프로그램
 * 작성일 : 2018-10-16
 */

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#define LEN 30 // 기호 상수 LEN을 30으로 정의

/* 학생의 정보를 저장하는 구조체 */
typedef struct _std
{
	char name[LEN]; // 학생 이름 필드
	int std_num; // 학번 필드
	int record; // 순위 필드
} STD; // typedef 선언으로 STD 키워드로 선언 가능

/* 순위로 배열을 정렬하는 함수 */
void selection_sort_by_record(STD *std, int count);
/* 학번로 배열을 정렬하는 함수 */
void selection_sort_by_std_num(STD *std, int count);
/* 배열의 데이터를 출력하는 함수 */
void display(STD *std, int count);

int main()
{
	STD *std = NULL;
	// 학생 구조체 배열을 동적 할당할 포인터 구조체 선언
	STD temp;
	// 데이터를 임시로 저장할 구조체 선언
	int count = 0;
	// 학생의 수를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	/* 파일 포인터 fp선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 예외처리
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %d %d", temp.name, &temp.std_num, &temp.record);
		// 파일의 데이터를 temp에 저장
		count++;
		// 학생의 수를 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 학생의 수인 count만큼 std를 동적 할당 */
	std = (STD *)malloc(sizeof(STD) * count);

	/* 학생의 수 만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
		fscanf(fp, "%s %d %d", std[i].name, &std[i].std_num, &std[i].record);
		// 파일에서 데이터를 읽어와 동적 할당한 배열에 대입

	printf("< 정렬전 데이터 >\n");
	display(std, count); // display 함수를 사용해 데이터 출력

	/* selection_sort_by_std_num 함수 호출로 배열을 학번으로 정렬 */
	selection_sort_by_std_num(std, count);

	printf("< 학번 정렬후 데이터 >\n");
	display(std, count); // display 함수를 사용해 데이터 출력

	/* selection_sort_by_record 함수 호출로 배열을 학번으로 정렬 */
	selection_sort_by_record(std, count);

	printf("< 등수 정렬후 데이터 >\n");
	display(std, count); // display 함수를 사용해 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.
	free(std); // 동적 할당한 구조체 배열의 메모리 할당 해제

	return 0; // 메인 함수 종료
}

/**
 * [selection_sort_by_record 함수]
 * @param std   [학생 구조체 배열]
 * @param count [학생의 수]
 */
void selection_sort_by_record(STD *std, int count)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int minIdx;
	// 최솟값을 저장할 변수 선언
	STD temp;
	// 학생 구조체를 임시로 저장할 변수 선언

	/* 배열의 크기 - 2번 반복하는 반복문 */
	for (i = 0; i < count - 1; i++)
	{
		minIdx = i; // minIdx에 i값 대입

		/* 배열이 안된 부분 부터 끝까지 반복하는 반복문 */
		for (j = i + 1; j < count; j++)
		{
			/* 순위 값을 비교하는 조건문 */
			if (std[j].record < std[minIdx].record)
				minIdx = j; // j의 순위가 minIdx보다 작으면 값 대입
		}

		/* 구조체 교환 */
		temp = std[i];
		std[i] = std[minIdx];
		std[minIdx] = temp;
	}
}

/**
 * [selection_sort_by_std_num 함수]
 * @param std   [학생 구조체 배열]
 * @param count [학생의 수]
 */
void selection_sort_by_std_num(STD *std, int count)
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int minIdx;
	// 최솟값을 저장할 변수 선언
	STD temp;
	// 학생 구조체를 임시로 저장할 변수 선언

	/* 배열의 크기 - 2번 반복하는 반복문 */
	for (i = 0; i < count - 1; i++)
	{
		minIdx = i; // minIdx에 i값 대입

		/* 배열이 안된 부분 부터 끝까지 반복하는 반복문 */
		for (j = i + 1; j < count; j++)
		{
			/* 학번 값을 비교하는 조건문 */
			if (std[j].std_num < std[minIdx].std_num)
				minIdx = j; // j의 학번이 minIdx보다 작으면 값 대입
		}

		/* 구조체 교환 */
		temp = std[i];
		std[i] = std[minIdx];
		std[minIdx] = temp;
	}
}

/**
 * [display 함수]
 * @param std   [학생 구조체 배열]
 * @param count [학생의 수]
 */
void display(STD *std, int count)
{
	int i; // 반복문에서 사용할 변수

	printf("---------------------------\n");
	printf("│ 이름   │   학 번  │ 등수│\n");
	printf("---------------------------\n");

	/* 학송의 수만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
	{
		printf("│ %s │ %8d │ %3d │\n", // 데이터 출력
			std[i].name, std[i].std_num, std[i].record);
	}

	printf("---------------------------\n\n\n");
}
