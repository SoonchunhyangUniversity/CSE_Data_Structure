/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 셸 정렬 프로그램
 * 작성일 : 2018-10-16
 */

#include <stdio.h> // 표준 입출력 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#define LEN 30 // 기호 상수 LEN을 30으로 정의

/* 학생의 정보를 저장하는 구조체 */
typedef struct _std
{
	char name[LEN]; // 학생 이름 필드
	char phone_num[LEN]; // 전화번호 필드
	int std_num; // 학번 필드
} STD; // typedef 선언으로 STD 키워드로 선언 가능

/* 셸 정렬에서 사용할 삽입 정렬 함수 */
void InsertionSort(STD *std, int first, int last, int gap);
/* 셸 정렬 함수 */
void ShellSort(STD *std, int n);
/* 학생 구조체 배열의 데이터를 출력하는 함수 */
void Display(STD *std, int n);

int main()
{
	STD *std = NULL;
	// 학생 구조체 배열을 동적 할당할 포인터 구조체 선언
	STD temp
	// 데이터를 임시로 저장할 구조체 선언
	int count = 0;
	// 학생의 수를 저장할 변수 선언 및 초기화
	int i;
	// 반복문에서 사용할 변수 선언

	/* 파일 포인터 fp선언 및 data4.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data4.txt", "r");

	/* 파일을 여는데에 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 예외처리
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %d %s", temp.name, &temp.std_num, temp.phone_num);
		// 파일의 데이터를 temp에 저장
		count++;
		// 학생의 수를 1 증가
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 학생의 수인 count만큼 std를 동적 할당 */
	std = (STD *)malloc(sizeof(STD) * count);

	/* 학생의 수 만큼 반복하는 반복문 */
	for (i = 0; i < count; i++)
		fscanf(fp, "%s %d %s", std[i].name, &std[i].std_num, std[i].phone_num);
		// 파일에서 데이터를 읽어와 동적 할당한 배열에 대입

	printf("< 정렬 전 >\n");
	Display(std, count); // Display 함수를 사용해 데이터 출력

	/* ShellSort 함수 호출로 배열을 정렬 */
	ShellSort(std, count);

	printf("< 정렬 후 >\n");
	Display(std, count); // display 함수를 사용해 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.
	free(std);  // 동적 할당한 구조체 배열의 메모리 할당 해제

	return 0; // 메인 함수 종료
}

/**
 * [InsertionSort 함수]
 * @param std   [학생 구조체 배열]
 * @param first [정렬 시작 인덱스]
 * @param last  [정렬 끝 인덱스]
 * @param gap   [두 요소의 인덱스 차이]
 */
void InsertionSort(STD *std, int first, int last, int gap)
{
	int i, j;
	// 반복문에서 사용할 변수 설명
	STD temp;
	// 학생 구조체를 임시로 저장할 변수 선언
	int key;
	// 학번을 임시로 저장할 변수 선언

	for (i = first + gap; i <= last; i = i + gap)
	{
		temp = std[i]; // temp에 구조체의 i번째 데이터 대입
		key = temp.std_num; // key에 temp의 학번 대입

		/* i - gap부터 역순으로 작아지는 반복문  j 값은 first보다
		   크거나 같고 key 값보다 정렬된 배열에 있는 값이 크면
		   j번째를 j+gap번쨰로 이동*/
		for (j = i - gap; j >= first&& key > std[j].std_num; j = j - gap)
			std[j + gap] = std[j]; // gap만큼 오른쪽으로 이동

		std[j + gap] = temp; // j + gap번째 배열에 temp 저장
	}
}

/**
 * [ShellSort 함수]
 * @param std [학생 배열 구조체]
 * @param n   [데이터의 개수]
 */
void ShellSort(STD *std, int n)
{
	int i, gap;
	// 반복문에서 사용할 변수 선언

	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		/* gap이 짝수인 경우 */
		if (gap % 2 == 0)
			gap++; // gap을 홀수로 만든다.

		/* gap만큼 반복하는 반복문 */
		for (i = 0; i < gap; i++)
			InsertionSort(std, i, n - 1, gap);
			// 부분 리스트에 대한 삽입 정렬 진행
	}
}

/**
 * [Display 함수]
 * @param std [학생 구조체 배열]
 * @param n   [데이터의 개수]
 */
void Display(STD *std, int n)
{
	int i; // 반복문에서 사용할 변수 선언

	/* 데이터의 개수만큼 반복하는 반복문 */
	for (i = 0; i < n; i++)
	{
		printf("%s %d %s\n", // 데이터 출력
			std[i].name, std[i].std_num, std[i].phone_num);
	}

	printf("\n");
}
