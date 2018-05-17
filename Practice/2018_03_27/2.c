/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 난수의 생성 및 검색
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <time.h> // srand, rand함수 사용을위한 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을위한 헤더파일 선언

int main() // 메인함수 시작
{
	int **matrix; // 2차원 배열로 사용할 이중포인터 변수 선언
	int ROWS, COLS; // 행과 열의 데이터를 저장할 정수형 변수 선언
	int input; // 찾을 숫자를 받을 정수형 변수 선언
	int COLS_temp = -1, ROWS_temp = -1; // 몇번째 행, 열에 값이 저장되어 있는지 저장할 변수
	int i, j; // 반복문에서 사용할 변수 선언

	printf("행과 열의 크기를 입력하시오 : ");
	scanf("%d %d", &ROWS, &COLS); // 행과 열의 크기를 입력 받음

	/* 입력받은 행과 열의 크기로 동적 할당을 진행 */
	matrix = (int **)malloc(sizeof(int *) * COLS);
	for (i = 0; i < COLS; i++)
		matrix[i] = (int *)malloc(sizeof(int) * ROWS);

	srand((unsigned)time(NULL)); // srand함수 사용으로 임의의 난수 생성

	for (i = 0; i < COLS; i++) // COLS번 반복
	{
		for (j = 0; j < ROWS; j++) // ROWS번 반복
		{
			matrix[i][j] = (rand() % 100) + 1; // 배열에 1 ~ 100 사이의 난수 저장
		}
	}

	printf("난수 생성 완료!\n");

	printf("검색할 숫자를 입력하시오 : ");
	scanf("%d", &input); // 2차원 배열에서 검색할 숫자를 입력 받음

	/* 2차원 배열에서 값을 찾는 반복문 */
	for (i = 0; i < COLS; i++) // COLS번 반복
	{
		for (j = 0; j < ROWS; j++) // ROWS번 반복
		{
			if (matrix[i][j] == input) // 배열의 값이 찾는 값과 같으면
			{
				COLS_temp = i; // 열의 값 저장
				ROWS_temp = j; // 행의 값 저장
				break; // 반복문 종료
			}
		}
	}

	/* 값의 위치를 출력하는 조건문 */
	if (COLS_temp == -1 && ROWS_temp == -1) // 행과 열의 temp값이 초기 값과 같으면
		printf("검색하신 숫자는 존재하지 않습니다.\n"); // 존재하지 않는 숫자임을 출력
	else // 배열에 숫자가 존재하면
		printf("검색하신 숫자 %d는 %d행 %d열에 있습니다.\n", input, COLS_temp + 1, ROWS_temp + 1); // 데이터 출력

	/* 저장된 행렬을 출력 하기 위한 반복문 */
	printf("저장된 행렬-----\n");
	for (i = 0; i < COLS; i++) // COLS번 반복
	{
		for (j = 0; j < ROWS; j++) // ROWS번 반복
			printf("%3d ", matrix[i][j]); // 행렬의 값 출력

		printf("\n");
	}

	/* 동적 할당한 메모리의 해제 */
	for (i = 0; i < COLS; i++)
		free(matrix[i]);

	free(matrix);

	return 0; // 메인 함수 종료
}
