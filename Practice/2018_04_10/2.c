/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 구조체 배열
	* 작성일 : 2018 - 04 - 10
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <string.h> // strcmp 함수 사용을 위한 헤더파일 선언
#define MAX 100 // 기호상수 MAX를 100으로 정의

/* 동물의 정보를 담는 구조체를 typedef로 선언 */
typedef struct _animal
{
	char type[MAX]; // 동물의 종을 담을 문자 배열
	char inherent_num[MAX]; // 고유 번호를 담을 문자 배열
	char loc[MAX]; // 위치를 담을 문자 배열
	char population[MAX]; // 개체 수를 담을 문자 배열
} Animal; // struct를 선언하지 않고 Animal로 선언 가능

enum
{
	type = 1, inherent_num, loc, population
}; // switch문에서 사용할 열거형 데이터, type부터 1, 2, 3, 4

int main() // 메인함수 시작
{
	int i, input, idx = -1;
	// 반복문에서 사용할 변수, 검색할 조건을 담을 변수, 인덱스 값을 저장할 변수 선언
	char temp[MAX], input_info[MAX];
	// 임시로 값을 저장할 문자열, 검색할 정보를 저장할 문자열 배열 선언
	Animal *struct_arr;
	// 구조체 포인터 struct_arr 선언 -> 동적할당 후 구조체 배열 사용
	int line_count = 0;
	// 파일 안의 데이터의 줄 수를 저장할 변수 선언 및 초기화

	/* 파일포인터 fp 선언 및 data.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data.txt", "r");

	/* 파일 오픈에 실패했을 때 예외처리 */
	if (fp == NULL) // 파일을 열 수 없으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp)) // 파일의 끝이 아니면 반복 진행
	{
		fgets(temp, MAX, fp); // 한 줄을 통째로 임시로 받는다.
		line_count++; // 줄의 개수를 1개씩 더해준다.
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌린다.

	/* 구조체 배열을 동적할당 진행, 파일 안의 줄 만큼 구조체 배열 생성 */
	struct_arr = (Animal *)malloc(sizeof(Animal) * line_count);

	/* 파일안의 데이터를 구조체 배열에 저장 */
	for (i = 0; i < line_count; i++) // line_count번 반복
	{
		fscanf(fp, "%s %s %s %s", struct_arr[i].type, struct_arr[i].inherent_num, struct_arr[i].loc, struct_arr[i].population);
		// 구조체 배열의 i번째 인덱스에 데이터 저장
	}

	/* 검색할 데이터를 입력 받는다 */
	printf("검색하실 조건을 선택하여 주십시오.\n");
	printf("< 1.종 2.고유번호 3.위치 4.개채수>\n");
	scanf("%d", &input);
	printf("검색하실 정보를 입력하여 주십시오 : ");
	scanf("%s", &input_info);

	/* 입력받은 데이터를 기반으로 찾아야할 값을 판별할 조건문 */
	switch (input)
	{
	case type: // input == 1
		for (i = 0; i < line_count; i++) // line_count번 반복
		{
			/* input_info와 구조체의 type을 비교 */
			if (!strcmp(input_info, struct_arr[i].type))
				idx = i; // 같으면 idx에 i값 저장
		}
		break; // 조건문 종료
	case inherent_num: // input == 2
		for (i = 0; i < line_count; i++) // line_count번 반복
		{
			/* input_info와 구조체의 inherent_num을 비교 */
			if (!strcmp(input_info, struct_arr[i].inherent_num))
				idx = i; // 같으면 idx에 i값 저장
		}
		break; // 조건문 종료
	case loc: // input == 3
		for (i = 0; i < line_count; i++) // line_count번 반복
		{
			/* input_info와 구조체의 loc을 비교 */
			if (!strcmp(input_info, struct_arr[i].loc))
				idx = i; // 같으면 idx에 i값 저장
		}
		break; // 조건문 종료
	case population: // input == 4
		for (i = 0; i < line_count; i++) // line_count번 반복
		{
			/* input_info와 구조체의 population을 비교 */
			if (!strcmp(input_info, struct_arr[i].population))
				idx = i; // 같으면 idx에 i값 저장
		}
		break; // 조건문 종료
	default: // input != 1 && input != 2 input != 3 input != 4
		printf("조건 입력 오류!\n"); // 예외 메세지 출력
		break; // 조건문 종료
	}

	/* 데이터가 존재하는지 존재하지 않는지 판단하는 조건문 */
	if (idx == -1) // idx의 값이 초기값과 같으면
	{
		printf("존재하지 않는 데이터 입니다.\n"); // 데이터가 존재하지 않음을 출력
	}
	else
	{
		/* 조건문에서 판단한 데이터로 구조체 배열의 idx번째 데이터를 출력 */
		printf("종 : %s\n", struct_arr[idx].type);
		printf("고유번호 : %s\n", struct_arr[idx].inherent_num);
		printf("위치 : %s\n", struct_arr[idx].loc);
		printf("개체 수 : %s\n", struct_arr[idx].population);
	}

	free(struct_arr); // 동적할당한 메모리의 해제
	fclose(fp); // 열어준 파일포인터 fp를 닫아줌

	return 0; // 메인함수 종료
}
