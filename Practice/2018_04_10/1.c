#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#define MAX 100 // 기호상수 MAx를 100으로 정의

/* 학생들의 정보를 담는 구조체를 typedef 선언 */
typedef struct _people
{
	char name[MAX]; // 학생의 이름을 담을 배열
	char people_num[MAX]; // 주민등록번호를 담을 배열
	char birth_info[MAX]; // 생년월일을 담을 배열
	char phone_num[MAX]; // 전화번호를 담을 배열
	char address[MAX]; // 주소를 담을 배열
} People; // struct를 선언하지 않고 People로 선언 가능

int main() // 메인함수 시작
{
	People people;
	// People형 구조체 변수 people 선언
	int i;
	// 반복문에서 사용할 변수 선언
	int line_count = 0;
	// 파일 안의 줄 개수를 저장할 변수 선언 및 0 으로 초기화
	char temp[MAX];
	// 임시로 값을 저장할 문자 배열 선언

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

	/* 파일안의 줄의 개수만큼 반복 */
	for (i = 0; i < line_count; i++) // line_count번 반복
	{
		/* 파일안의 데이터들을 people 구조체에 저장 */
		fscanf(fp, "%s %s %s %s %s", people.people_num, people.name, people.birth_info, people.phone_num, people.address);

		/* 저장한 데이터들을 출력한다. */
		printf("이름 : %s\n", people.name);
		printf("주민번호 : %s\n", people.people_num);
		printf("생년월일 : %s\n", people.birth_info);
		printf("전화번호 : %s\n", people.phone_num);
		printf("주소 : %s\n", people.address);
		printf("\n");
	}

	fclose(fp); // 열어준 파일포인터 fp를 닫아줌

	return 0; // 메인함수 종료
}
