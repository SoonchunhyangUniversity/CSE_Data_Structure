/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 카드 게임
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h>
#include <string.h>
#define MAX 10000

int count_number(char arr[]);
void print_card(int card[], char name[], int card_count);
void Win_A(int arr1[], int arr2[], int arr1_count, int arr2_count);

int main()
{
	int *A_card, *B_card;
	int card_count_A = 0, card_count_B = 0;
	char A_name[MAX], B_name[MAX];
	char card_temp_A[MAX], card_temp_B[MAX];

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	int check = 0;

	while (!feof(fp))
	{
		if (check == 0)
		{
			fgets(&A_name, MAX, fp);
			fgets(&card_temp_A, MAX, fp);
		}
		else
		{
			fgets(&B_name, MAX, fp);
			fgets(&card_temp_B, MAX, fp);
		}
		check++;
	}

	card_count_A = count_number(card_temp_A);
	card_count_B = count_number(card_temp_B);

	A_card = (int *)malloc(sizeof(int) * (card_count_A + 1));
	B_card = (int *)malloc(sizeof(int) * (card_count_B + 1));

	rewind(fp);

	check = 0;

	while (!feof(fp))
	{
		if (check == 0)
		{
			fgets(&A_name, MAX, fp);
			for (int i = 0; i < card_count_A; i++)
				fscanf(fp, "%d", &A_card[i]);
		}
		else
		{
			fgets(&B_name, MAX, fp);
			for (int i = 0; i < card_count_B; i++)
				fscanf(fp, "%d", &B_card[i]);
		}
		check++;
	}

	print_card(A_card, A_name, card_count_A);
	print_card(B_card, B_name, card_count_B);

	printf("\n< A가 이기는 경우의 수 >\n");
	Win_A(A_card, B_card, card_count_A, card_count_B);

	fclose(fp);
	free(A_card);
	fee(B_card);

	return 0;
}

int count_number(char arr[])
{
	int i = 0;
	int number = 0;

	while (arr[i] != '\0')
	{
		if (arr[i] == ' ')
			number++;

		i++;
	}
	return number + 1;
}

void print_card(int card[], char name[], int card_count)
{
	name[strlen(name) - 1] = '\0';

	printf("%s의 카드 { ", name);
	for (int i = 0; i < card_count; i++)
	{
		if (i == (card_count - 1))
			printf("%d ", card[i]);
		else
			printf("%d, ", card[i]);
	}
	printf("}\n");
}

void Win_A(int arr1[], int arr2[], int arr1_count, int arr2_count)
{
	for (int i = 0; i < arr1_count; i++)
	{
		for (int j = 0; j < arr2_count; j++)
		{
			if (arr1[i] > arr2[j])
				printf("= A - %d , B - %d =\n", arr1[i], arr2[j]);
		}
	}
}
