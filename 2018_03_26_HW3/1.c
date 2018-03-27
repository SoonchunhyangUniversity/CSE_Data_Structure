/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 03 과제
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 26
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수를 사용하기 위한 헤더파일 선언

/* 행렬 A와 행렬 B를 곱해서 행렬 C를 만드는 함수 */
void matrix_mul(int **matrix1, int **matrix2, int **matrix3, int ROWS, int COLS);
/* 행렬 A와 행렬 B를 더해서 행렬 C를 만드는 함수 */
void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS);
/* 행렬 A와 행렬 B를 빼서 행렬 C를 만드는 함수 */
void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS);
/* 행렬을 출력하는 함수 */
void print_matrix(int **matrix, int COLS, int ROWS);

int main() // 메인함수 시작
{
	int **Matrix_A, **Matrix_B, **Matrix_C; // 2차원 배열 동적할당할 이중 포인터 선언
	int COLS_A, ROWS_A; // A행렬의 행과 열의 개수를 담을 정수형 변수 선언
	int COLS_B, ROWS_B; // B행렬의 행과 열의 개수를 담을 정수형 변수 선언

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
		fscanf(fp, "%d %d", &COLS_A, &ROWS_A); // A행렬의 행과 열의 개수를 저장
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

		fscanf(fp, "%d %d", &COLS_B, &ROWS_B); // B행렬의 행과 열의 개수를 저장
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
	}
	/* 행렬 연산을 진행하기전의 행렬 데이터 출력 */
	printf("-------A 행렬-------\n\n");
	print_matrix(Matrix_A, COLS_A, ROWS_A);
	// print_matrix함수에 Matrix_A, COLS_A, ROWS_A를 파라미터로 전달
	printf("\n");
	printf("-------B 행렬-------\n\n");
	print_matrix(Matrix_B, COLS_B, ROWS_B);
	// print_matrix함수에 Matrix_B, COLS_B, ROWS_B를 파라미터로 전달
	printf("\n");

	/* 주어진 행렬을 연산해 저장할 배열 동적할당 */
	Matrix_C = (int **)malloc(sizeof(int *) * COLS_A);
	for (int i = 0; i < ROWS_A; i++)
		Matrix_C[i] = (int *)malloc(sizeof(int) * ROWS_B);
	// 곱연산을 기준으로  A의 행 B의 열으로 동적할당 진행

	/* 행열의 곱 연산의 조건 */
	if (ROWS_A == COLS_B)	// 5 by 4, 4 by 5일경우 5 by 5 행렬
	{						// A의 열과 B의 행이 같아야 연산 진행
		matrix_mul(Matrix_A, Matrix_B, Matrix_C, COLS_A, ROWS_B);
		// matrix_mul 함수에 Matrix_A, Matrix_B, Matrix_C, COLS_A, ROWS_B를 파라미터로 전달
		printf("A 행렬과 B 행렬의 곱\n\n");
		print_matrix(Matrix_C, COLS_A, ROWS_B);
		// print_matrix함수에 Matrix_C, COLS_A, ROWS_B를 파라미터로 전달해 곱연산 결과 출력
		printf("\n");
	}
	else // 곱연산의 조건에 맞지 않으면
		printf("MATRIX SIZE ERROR!\n"); // 에러메세지 출력

	/* 행열의 덧셈 연산의 조건 */
	if (COLS_A == COLS_B && ROWS_A == ROWS_B) // 두 행열의 크기가 같아야함
	{
		matrix_sum(Matrix_A, Matrix_B, Matrix_C, COLS_A);
		// matrix_sum 함수에 Matrix_A, Matrix_B, Matrix_C, COLS를 파라미터로 전달
		printf("A 행렬과 B 행렬의 합\n\n");
		print_matrix(Matrix_C, ROWS_A, COLS_A);
		// print_matrix함수에 Matrix_C, ROWS_A, COLS_A를 파라미터로 전달해 곱연산 결과 출력
		printf("\n");
	}
	else // 합 연산의 조건에 맞지 않으면
		printf("MATRIX SIZE ERROR!\n"); // 에러메세지 출력

	/* 행열의 뺄셈 연산의 조건 */
	if (COLS_A == COLS_B && ROWS_A == ROWS_B)
	{
		matrix_sub(Matrix_A, Matrix_B, Matrix_C, COLS_A); // 두 행열의 크기가 같아야함
		// matrix_suㅠ 함수에 Matrix_A, Matrix_B, Matrix_C, COLS_A를 파라미터로 전달
		printf("A 행렬과 B 행렬의 차\n\n");
		print_matrix(Matrix_C, ROWS_A, COLS_A);
		// print_matrix함수에 Matrix_C, ROWS_A, COLS_A를 파라미터로 전달해 곱연산 결과 출력
		printf("\n");
	}
	else // 차 연산의 조건에 맞지 않으면
		printf("MATRIX SIZE ERROR!\n"); // 에러메세지 출력

	/* 동적할당한 배열들의 메모리 해제 */
	for(int i = 0; i < ROWS_A; i++)
		free(Matrix_A[i]);
	free(Matrix_A);
	for (int i = 0; i < ROWS_B; i++)
		free(Matrix_B[i]);
	free(Matrix_B);
	for (int i = 0; i < ROWS_B; i++)
		free(Matrix_C[i]);
	free(Matrix_C);

	fclose(fp); // 파일 포인터를 닫아줌

	return 0; // 메인함수 종료
}
/* 행렬 A와 행렬 B를 곱해서 행렬 C를 만드는 함수 */
void matrix_mul(int **matrix1, int **matrix2, int **matrix3, int ROWS, int COLS)
{	// 매개변수로 2차원 배열 3개, 행과 열의 값을 받는다.
	for (int i = 0; i < ROWS; i++) // ROWS번 반복한다.
	{
		for (int j = 0; j < COLS; j++) // COLS번 반복한다.
		{
			for (int k = 0; k < ROWS; k++) // ROWS번 반복한다.
				matrix3[i][j] = matrix1[i][k] * matrix2[k][j]; // 행렬의 값을 곱한다.
		}
	}
}
/* 행렬 A와 행렬 B를 더해서 행렬 C를 만드는 함수 */
void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{	// 매개변수로 2차원 배열 3개, 열의 값을 받는다.
	for (int i = 0; i < ROWS; i++) // ROWS번 반복한다.
	{
		for (int j = 0; j < ROWS; j++) // ROWS번 반복한다.
		{
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j]; // 행렬의 값을 더해준다.
		}
	}
}
/* 행렬 A와 행렬 B를 빼서 행렬 C를 만드는 함수 */
void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{	// 매개변수로 2차원 배열 3개, 열의 값을 받는다.
	for (int i = 0; i < ROWS; i++) // ROWS번 반복한다.
	{
		for (int j = 0; j < ROWS; j++) // ROWS번 반복한다.
		{
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j]; // 행렬의 값을 뺀다.
		}
	}
}
/* 행렬을 출력하는 함수 */
void print_matrix(int **matrix, int ROWS, int COLS)
{	// 매개변수로 2차원 배열 1개, 행과 열의 값을 받는다.
	for (int i = 0; i < ROWS; i++) // ROWS번 반복
	{
		for (int j = 0; j < COLS; j++) // COL번 반복
		{
			if (j == COLS - 1) // 줄의 마지막 원소일때
				printf("│ %3d │", matrix[i][j]); // 뒤에 │를 붙여 출력
			else // 마지막이 아닌 모든 원소
				printf("│ %3d ", matrix[i][j]); // 행렬의 값 출력
		}

		printf("\n");
	}
}
