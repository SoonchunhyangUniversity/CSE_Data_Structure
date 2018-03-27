#include <stdio.h>
#include <stdlib.h>

void matrix_mul(int **matrix1, int **matrix2, int **matrix3, int ROWS, int COLS);
void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS);
void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS);
void print_matrix(int **matrix, int COLS, int ROWS);

int main()
{
	int **Matrix_A, **Matrix_B, **Matrix_C;
	int COLS_A, ROWS_A;
	int COLS_B, ROWS_B;
	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		fprintf(stderr, " FILE OPEN ERROR!\n");
		exit(-1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %d", &COLS_A, &ROWS_A);

		Matrix_A = (int **)malloc(sizeof(int *) * COLS_A);
		for (int i = 0; i < COLS_A; i++)
			Matrix_A[i] = (int *)malloc(sizeof(int) * ROWS_A);

		for (int i = 0; i < COLS_A; i++)
		{
			for (int j = 0; j < ROWS_A; j++)
				fscanf(fp, "%d", &Matrix_A[i][j]);
		}

		fscanf(fp, "%d %d", &COLS_B, &ROWS_B);

		Matrix_B = (int **)malloc(sizeof(int *) * COLS_B);
		for (int i = 0; i < COLS_B; i++)
			Matrix_B[i] = (int *)malloc(sizeof(int) * ROWS_B);

		for (int i = 0; i < COLS_B; i++)
		{
			for (int j = 0; j < ROWS_B; j++)
				fscanf(fp, "%d", &Matrix_B[i][j]);
		}
	}

	printf("-------A 행렬-------\n\n");
	print_matrix(Matrix_A, COLS_A, ROWS_A);
	printf("\n");
	printf("-------B 행렬-------\n\n");
	print_matrix(Matrix_B, COLS_B, ROWS_B);
	printf("\n");


	Matrix_C = (int **)malloc(sizeof(int *) * ROWS_A);
	for (int i = 0; i < ROWS_A; i++)
		Matrix_C[i] = (int *)malloc(sizeof(int) * COLS_B);

	if (ROWS_A == COLS_B)
	{
		matrix_mul(Matrix_A, Matrix_B, Matrix_C, COLS_A, ROWS_B);
		printf("A 행렬과 B 행렬의 곱\n\n");
		print_matrix(Matrix_C, COLS_A, ROWS_B);
		printf("\n");
	}
	else
		printf("MATRIX SIZE ERROR!\n");

	if (COLS_A == COLS_B && ROWS_A == ROWS_B)
	{
		matrix_sum(Matrix_A, Matrix_B, Matrix_C, COLS_A, COLS_B);
		printf("A 행렬과 B 행렬의 합\n\n");
		print_matrix(Matrix_C, ROWS_A, COLS_A);
		printf("\n");
	}
	else
		printf("MATRIX SIZE ERROR!\n");

	if (COLS_A == COLS_B && ROWS_A == ROWS_B)
	{
		matrix_sub(Matrix_A, Matrix_B, Matrix_C, COLS_A, COLS_B);
		printf("A 행렬과 B 행렬의 차\n\n");
		print_matrix(Matrix_C, ROWS_A, COLS_A);
		printf("\n");
	}
	else
		printf("MATRIX SIZE ERROR!\n");

	for(int i = 0; i < ROWS_A; i++)
		free(Matrix_A[i]);

	for (int i = 0; i < ROWS_B; i++)
		free(Matrix_B[i]);

	for (int i = 0; i < ROWS_B; i++)
		free(Matrix_C[i]);

	return 0;
}

void matrix_mul(int **matrix1, int **matrix2, int **matrix3, int ROWS, int COLS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			for (int k = 0; k < ROWS; k++)
				matrix3[i][j] = matrix1[i][k] * matrix2[k][j];
		}
	}
}

void matrix_sum(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			matrix3[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
}

void matrix_sub(int **matrix1, int **matrix2, int **matrix3, int ROWS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < ROWS; j++)
		{
			matrix3[i][j] = matrix1[i][j] - matrix2[i][j];
		}
	}
}

void print_matrix(int **matrix, int ROWS, int COLS)
{
	for (int i = 0; i < ROWS; i++)
	{
		for (int j = 0; j < COLS; j++)
		{
			if (j == COLS - 1)
				printf("│ %3d │", matrix[i][j]);
			else
				printf("│ %3d ", matrix[i][j]);
		}

		printf("\n");
	}
}
