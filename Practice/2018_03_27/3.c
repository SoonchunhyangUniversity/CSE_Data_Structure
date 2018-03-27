/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 난수의 생성 및 검색
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수를 사용하기 위한 헤더파일 선언

/* 행렬 A와 행렬 B를 더해서 행렬 C를 만드는 함수 */
void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS);
/* 행렬 A와 행렬 B를 빼서 행렬 C를 만드는 함수 */
void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS);
/* 행렬을 출력하는 함수 */
void print_matrix(int **matrix, int COLS, int ROWS);

int main() // 메인함수 시작
{
	int **Matrix_A, **Matrix_B, **Matrix_C, **Matrix_Result1, **Matrix_Result2; // 2차원 배열 동적할당할 이중 포인터 선언
	char c;
	char oper1[10] = { 0 }, oper2[10] = { 0 };
	int COLS_A, ROWS_A; // A행렬의 행과 열의 개수를 담을 정수형 변수 선언
	int COLS_B, ROWS_B; // B행렬의 행과 열의 개수를 담을 정수형 변수 선언
	int COLS_C, ROWS_C; // B행렬의 행과 열의 개수를 담을 정수형 변수 선언

	/* 파일 포인터 fp선언 및 data.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data.txt", "r");

	/* 파일 열기에 실패했을 경우 예외처리 */
	if (fp == NULL)	// 파일이 없다면
	{
		fprintf(stderr, " FILE OPEN ERROR!\n"); // 에러메세지 출력
		exit(-1); // 종료
	}

	/* 파일의 끝까지 반복되는 반복문 */
	while (!feof(fp)) // 파일의 끝까지 반복
	{
		fscanf(fp, "%c %d %d", &c, &COLS_A, &ROWS_A); // A행렬의 행과 열의 개수를 저장
		/* 받아온 데이터로 2차원 배열 동적할당 진행 */
		Matrix_A = (int **)malloc(sizeof(int *) * COLS_A);
		for (int i = 0; i < COLS_A; i++)
			Matrix_A[i] = (int *)malloc(sizeof(int) * ROWS_A);
		/* 동적할당한 배열에 파일에서 데이터를 받아 저장 */
		for (int i = 0; i < COLS_A; i++)
		{
			for (int j = 0; j < ROWS_A; j++)
				fscanf(fp, "%d", &Matrix_A[i][j]);
		}

		fscanf(fp, "%c %c %d %d", &c, &c, &COLS_B, &ROWS_B); // B행렬의 행과 열의 개수를 저장
		/* 받아온 데이터로 2차원 배열 동적할당 진행 */
		Matrix_B = (int **)malloc(sizeof(int *) * COLS_B);
		for (int i = 0; i < COLS_B; i++)
			Matrix_B[i] = (int *)malloc(sizeof(int) * ROWS_B);
		/* 동적할당한 배열에 파일에서 데이터를 받아 저장 */
		for (int i = 0; i < COLS_B; i++)
		{
			for (int j = 0; j < ROWS_B; j++)
				fscanf(fp, "%d", &Matrix_B[i][j]);
		}

		fscanf(fp, "%c %c %d %d", &c, &c, &COLS_C, &ROWS_C); // C행렬의 행과 열의 개수를 저장
		/* 받아온 데이터로 2차원 배열 동적할당 진행 */
		Matrix_C = (int **)malloc(sizeof(int *) * COLS_C);
		for (int i = 0; i < COLS_C; i++)
			Matrix_C[i] = (int *)malloc(sizeof(int) * ROWS_C);
		/* 동적할당한 배열에 파일에서 데이터를 받아 저장 */
		for (int i = 0; i < COLS_C; i++)
		{
			for (int j = 0; j < ROWS_C; j++)
				fscanf(fp, "%d", &Matrix_C[i][j]);
		}

		fscanf(fp, "%s", oper1); // 연산1을 oper1에 저장한다.
		fscanf(fp, "%s", oper2); // 연산2를 oper2에 저장한다.
	}

	/* 행렬 연산을 진행하기전의 행렬 데이터 출력 */
	printf("A 행렬 =======================\n");
	print_matrix(Matrix_A, COLS_A, ROWS_A);
	// print_matrix함수에 Matrix_A, COLS_A, ROWS_A를 파라미터로 전달
	printf("\n");
	printf("B 행렬 =======================\n");
	print_matrix(Matrix_B, COLS_B, ROWS_B);
	// print_matrix함수에 Matrix_B, COLS_B, ROWS_B를 파라미터로 전달
	printf("\n");
	printf("C 행렬 =======================\n");
	print_matrix(Matrix_C, COLS_C, ROWS_C);
	// print_matrix함수에 Matrix_C, COLS_C, ROWS_C를 파라미터로 전달
	printf("\n");

	int check = 0;
	/* 행렬 계산 조건 판단 모든 행렬의 크기가 같으면 연산 진행 */
	if (COLS_C == COLS_A && COLS_A == COLS_B && ROWS_C == ROWS_A && ROWS_A == ROWS_B)
	{
		Matrix_Result1 = (int **)malloc(sizeof(int *) * COLS_A);
		for (int i = 0; i < COLS_A; i++)
			Matrix_Result1[i] = (int *)malloc(sizeof(int) * ROWS_A);

		Matrix_Result2 = (int **)malloc(sizeof(int *) * COLS_A);
		for (int i = 0; i < COLS_A; i++)
			Matrix_Result2[i] = (int *)malloc(sizeof(int) * ROWS_A);

		check = 1;

		printf("%s 행렬 ===================\n", oper1);
		matrix_sub(Matrix_C, Matrix_A, Matrix_Result1, COLS_A);
		matrix_sum(Matrix_Result1, Matrix_B, Matrix_Result2, COLS_A);
		print_matrix(Matrix_Result2, COLS_A, ROWS_A);
		printf("\n");

		printf("%s 행렬 ===================\n", oper2);
		matrix_sum(Matrix_B, Matrix_C, Matrix_Result1, COLS_A);
		matrix_sub(Matrix_Result1, Matrix_A, Matrix_Result2, COLS_A);
		print_matrix(Matrix_Result2, COLS_A, ROWS_A);
		printf("\n");
	}
	else // 행렬의 크기가 하나라도 다르면 에러메세지 출력
		printf("행렬의 크기가 맞지 않습니다.\n"); // 에러메세지 출력

	/* 동적할당한 배열들의 메모리 할당 해제 */
	for (int i = 0; i < ROWS_A; i++)
		free(Matrix_A[i]);
	free(Matrix_A);
	for (int i = 0; i < ROWS_B; i++)
		free(Matrix_B[i]);
	free(Matrix_B);
	for (int i = 0; i < ROWS_A; i++)
		free(Matrix_C[i]);
	free(Matrix_C);
	if (check == 1)
	{
		for (int i = 0; i < ROWS_A; i++)
			free(Matrix_Result1[i]);
		free(Matrix_Result1);
		for (int i = 0; i < ROWS_B; i++)
			free(Matrix_Result2[i]);
		free(Matrix_Result2);
	}

	return 0;
}

void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
	}
}

void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
	}
}

void print_matrix(int **matrix, int ROWS, int COLS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
			printf("%4d", matrix[i][j]);

		printf("\n");
	}
}
