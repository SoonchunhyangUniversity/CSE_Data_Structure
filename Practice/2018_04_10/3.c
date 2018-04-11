/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 성적 관리 프로그램
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 10
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <string.h> // strcmp 함수를 사용하기위한 헤더파일 선언
#define MAX 100 // 기호상수 MAX를 100으로 정의

/* 학생의 정보를 담는 _std 구조체를 typedef로 선언 */
typedef struct _std
{
	char std_num[MAX]; // 학번을 저장할 문자 배열
	char name[MAX]; // 이름을 저장할 문자 배열
	int kor; // 국어 점수를 저장할 정수형 변수
	int eng; // 영어 점수를 저장할 정수형 변수
	int mat; // 수학 점수를 저장할 정수형 변수
	int sum; // 점수의 합을 저장할 정수형 변수
	double avg; // 평균을 저장할 실수형 변수
	int rank; // 순의를 저장할 정수형 변수
} STUDENT; // struct를 선언하지 않고 STUDENT로 선언 가능

int main() // 메인함수 시작
{
	int i, j;
	// 반복문에서 사용할 변수 선언
	int line_count = 0, idx = -1;
	// 파일 안의 줄 수를 저장할 변수, 인덱스 값을 저장할 변수 선언 및 초기화
	char temp[MAX], input[MAX];
	// 임시로 값을 저장할 tmep, 찾을 데이터를 입력받을 input 문자 배열 선언

	STUDENT *std; // STUDENT 구조체 포인터 std 선언

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
	std = (STUDENT *)malloc(sizeof(STUDENT) * line_count);

	/* 파일안의 데이터를 구조체 배열에 저장 */
	for (i = 0; i < line_count; i++) // line_count번 반복
	{
		fscanf(fp, "%s %s %d %d %d", std[i].std_num, std[i].name, &std[i].kor, &std[i].eng, &std[i].mat);
		// 파일 안의 데이터를 구조체 배열에 저장
		std[i].sum = std[i].kor + std[i].eng + std[i].mat;
		// 저장한 데이터로 총점을 계산 후 저장
		std[i].avg = (double)std[i].sum / 3;
		// 계산한 총점으로 평균을 계산 후 저장
		std[i].rank = 1;
		// rank를 1로 저장 -> 추후 계산
	}

	/* 학생의 등수를 계산하는 중첩 반복문 */
	for (i = 0; i < line_count; i++) // line_count번 반복
	{
		for (j = 0; j < line_count; j++) // line_count번 반복
		{
			// std[i]의 평균이 std[j]의 평균보다 크다면
			if (std[i].avg < std[j].avg)
				std[i].rank++; // rank를 1씩 더해준다.
		}
	}

	/* 검색할 데이터를 입력받는다 */
	printf("학생의 이름 또는 학번을 입력하세요 : ");
	scanf("%s", &input);

	/* 몇 번째 인덱스 값이 찾을 데이터인지 검사한다 */
	for (i = 0; i < line_count; i++) // line_count번 반복
	{
		/* 이름과, 학번 모두 입력받은 데이터와 비교한다 */
		if (!strcmp(input, std[i].name) || !strcmp(input, std[i].std_num))
			idx = i; // idx에 i값 저장
	}

	/* idx에 저장된 값을 기반으로 데이터를 출력하는 조건문 */
	if (idx == -1) // 초기 설정값과 같으면
	{
		printf("찾으려는 학생은 존재하지 않습니다.\n");
		// 데이터가 존재하지 않음, 예외메세지 출력
	}
	else // 데이터가 존재한다면
	{
		/* 데이터를 형식에 맞게 출력한다 */
		printf("입력하신 학생 \"%s\"학생의 정보는 아래와 같습니다.\n", std[idx].name);
		printf("│ 학   번 │ 국어 │ 영어 │ 수학 │ 총 점 │ 평 균 │ 석 차 │\n");
		printf("│======================================================│\n");
		printf("│ %s│ %4d │ %4d │ %4d │ %4d │  %4.2lf │  %d/%d  │\n", std[idx].std_num, std[idx].kor, std[idx].eng, std[idx].mat, std[idx].sum, std[idx].avg, std[idx].rank, line_count);
	}

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.
	free(std); // 동적할당한 std의 메모리 해제

	return 0; // 메인함수 종료
}
