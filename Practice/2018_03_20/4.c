/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 카드 게임
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc함수와 free함수 사용을 위해 선언
#include <string.h> // strlen 함수 사용을 위해 선언
#define MAX 10000 // MAX를 1000으로 정의 문자 상수

/* 문자열로 받은 데이터안의 정수의 개수를 세기 위한 함수 */
int count_number(char arr[]);
/* 카드를 가진 사람 이름과 카드의 종류를 출력하기 위한 함수 */
void print_card(int card[], char name[], int card_count);
/* A가 이기는 경우를 출력할 함수 */
void Win_A(int arr1[], int arr2[], int arr1_count, int arr2_count);

int main() // 메인함수 시작
{
	int *A_card, *B_card;
	// 동적할당 하여 A의 카드와 B의 카드를 저장할 배열역할을 할 포인터 변수
	int card_count_A = 0, card_count_B = 0;
	// A의 카드 개수와 B의 카드 개수를 저장할 변수, 0으로 초기화
	char A_name[MAX], B_name[MAX];
	// A의 이름과 B의 이름을 저장할 배열
	char card_temp_A[MAX], card_temp_B[MAX];
	// 파일 안의 데이터 한줄을 문자열로 읽어올 배열

	/* 파일 포인터 변수 fp 선언 및 초기화 */
	FILE *fp = fopen("data.txt", "r"); // data.txt를 읽기모드로 연다.

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일 오픈에 실패했으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러 메세지 출력
		return 0; // 메인함수 종료
	}

	int check = 0; // A에 넣을지 B에 넣을지 체크할 변수, 0으로 초기화

	/* 파일 안의 데이터를 문자열로 저장하는 반복문*/
	while (!feof(fp)) // 파일의 끝까지 반복
	{
		/* A에 값을 저장 할 조건문 */
		if (check == 0) // check가 0이면 실행
		{
			fgets(&A_name, MAX, fp);
			// A_name에 MAX길이까지 fp의 데이터를 한 줄 저장
			fgets(&card_temp_A, MAX, fp);
			// card_temp_A에 MAX길이 까지 fp의 데이터를 한 줄 저장
		}
		/* B에 값을 저장 */
		else // check != 0
		{
			fgets(&B_name, MAX, fp);
			// B_name에 MAX길이까지 fp의 데이터 한 줄 저장
			fgets(&card_temp_B, MAX, fp);
			// card_temp_B에 MAX길이 까지 fp의 데이터를 한 줄 저장
		}
		check++; // check = check + 1; A에 값이 들어가면 B에 저장하기 위해
	}

	/* 받아온 문자열로 데이터의 수를 판별 */
	card_count_A = count_number(card_temp_A);
	// 함수 count_number에 card_temp_A를 인자로 전달하여 개수를 card_count_A에 저장
	card_count_B = count_number(card_temp_B);
	// 함수 count_number에 card_temp_B를 인자로 전달하여 개수를 card_count_B에 저장

	/* 앞에서 선언한 카드 데이터를 담을 포인터 변수를 동적 할당*/
	A_card = (int *)malloc(sizeof(int) * (card_count_A));
	B_card = (int *)malloc(sizeof(int) * (card_count_B));

	rewind(fp); // 파일포인터의 위치를 파일 처음으로 옮긴다

	check = 0; // check 변수를 0으로 저장

	/* 동적할당한 배열에 정수 값을 집어 넣기 위한 반복문 */
	while (!feof(fp)) // 파일이 끝날때 까지 반복
	{
		/* A에 해당하는 데이터 저장 */
		if (check == 0) // check 가 0이라면
		{
			fgets(&A_name, MAX, fp);
			// A_name에 MAX길이까지 fp의 데이터를 한 줄 저장

			/* 둘째 줄의 데이터를 동적할당한 배열에 저장할 반복문 */
			for (int i = 0; i < card_count_A; i++) // card_count_A번 반복
				fscanf(fp, "%d", &A_card[i]); // fp에서 정수형 데이터를 A_card[i]에 저장
		}
		/* B에 해당하는 데이터 저장 */
		else // check != 0
		{
			fgets(&B_name, MAX, fp);
			// B_name에 MAX길이까지 fp의 데이터를 한 줄 저장

			/* 둘째 줄의 데이터를 동적할당한 배열에 저장할 반복문 */
			for (int i = 0; i < card_count_B; i++) // card_count_B번 반복
				fscanf(fp, "%d", &B_card[i]); // fp에서 정수형 데이터를 B_card[i]에 저장
		}
		check++; // check = check + 1; A에 값이 저장되면 B에 저장하기 위해서
	}

	/* 저장된 카드의 데이터를 print_card 함수로 출력 */
	print_card(A_card, A_name, card_count_A);
	// print_card함수 인자로 카드 데이터 A_card, 사람 이름 A_name, 카드의 개수 card_count_A 전달
	print_card(B_card, B_name, card_count_B);
	// print_card함수 인자로 카드 데이터 B_card, 사람 이름 B_name, 카드의 개수 card_count_B 전달

	printf("\n< A가 이기는 경우의 수 >\n");
	/* A가 이기는 경우의 수를 출력하는 함수 Win_A */
	Win_A(A_card, B_card, card_count_A, card_count_B);
	// 인자로 배열 A_card, B_card와 카드의 개수 card_count_A, card_count_B 전달

	fclose(fp); // 열어준 파일포인터 fp를 닫아줌
	free(A_card); // 동적할당한 배열 A_card 메모리 할당 해제
	free(B_card); // 동적할당한 배열 B_card 메모리 할당 해제

	return 0; // 메인함수 종료
}

/* 문자열로 받은 데이터안의 정수의 개수를 세기 위한 함수 */
int count_number(char arr[]) // 매개변수 문자열 char arr[]
{
	int i = 0; // 배열의 인덱스 값을 가리킬 변수 선인 및 0으로 초기화
	int number = 0; // 공백의 개수를 담을 변수 선언 0으로 초기화

	/* 정수 데이터 개수를 판별할 반복문 */
	while (arr[i] != '\0') // 문자열의 끝까지 반복
	{
		if (arr[i] == ' ') // 문자열의 값이 공백이면
			number++; // 정수의 개수를 하나 더해준다.

		i++; // 다음 인덱스를 가리킴
	}
	return number + 1; // 공백의 개수 + 1의 값을 반환 -> 정수의 개수
}

/* 카드를 가진 사람 이름과 카드의 종류를 출력하기 위한 함수 */
void print_card(int card[], char name[], int card_count)
{ // 매개변수 배열 card[], name[], 정수형 데이터 card_count
	name[strlen(name) - 1] = '\0';
	// fgets로 데이터를 받으면 데이터의 끝에 개행문자 저장, 개행문자를 제거

	/* 저장된 데이터를 출력 한다 */
	printf("%s의 카드 { ", name);
	for (int i = 0; i < card_count; i++) // card_count번 반복
	{
		if (i == (card_count - 1)) // 마지막 값이면
			printf("%d ", card[i]); // card[i]의 값 출력, 정수 뒤에 ,를 출력하지 않음
		else // 마지막 값이 아니면
			printf("%d, ", card[i]); // card[i]의 값 뒤에 ,를 붙여서 출력
	}
	printf("}\n");
}

/* A가 이기는 경우를 출력할 함수 */
void Win_A(int arr1[], int arr2[], int arr1_count, int arr2_count)
{ // 매개변수 배열 arr1[], arr2[], 정수형 데이터 arr1_count, arr2_count
	/* 중첩 반복문을 사용하여 모든 인덱스 값을 비교 */
	for (int i = 0; i < arr1_count; i++) // arr1_count번 반복
	{
		for (int j = 0; j < arr2_count; j++) // arr2_count번 반복
		{
			if (arr1[i] > arr2[j]) // arr1[i]의 값이 arr2[j]의 값보다 크다면
				printf("= A - %d , B - %d =\n", arr1[i], arr2[j]); // 데이터를 출력
		}
	}
}
