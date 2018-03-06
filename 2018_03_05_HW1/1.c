/*
	* * * * * * * * * * * * * * * * * * *
	* 작성자 : 김민수										*
	* 학번 : 20174444										*
	* 학과 : 컴퓨터소프트웨어공학과		 *
	* 프로그램명 : 최댓값,최솟값 찾기	 *
	* 개발환경 : Visual Studio 2010			*
	* 컴파일러 표준 : C99								*
	* 작성일 : 2018 - 03 - 05					 *
	* * * * * * * * * * * * * * * * * * *
*/

#include <stdio.h>

int main()
{
	int arr[10000] = { 0 }; // data.txt에서 가져온 값을 저장할 정수형 배열 선언
	int i = 0;	// while문에서 사용할 변수 i 선언
	int num_count = 0;; // 파일 안에 있는 숫자 갯수 확인을 위한 변수 선언
	int max_idx, min_idx;	// 최댓값과 최솟값이 배열의 몇번째 인덱스에 있는지 저장해줄 변수 선언

							/* 파일포인터 data.txt를 읽기모드로 열기 */
	FILE *fp = fopen("data.txt", "r");

	/* 파일이 없으면 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		exit(-1);
	}

	/* fscanf로 arr에 값 삽입 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &arr[i]);	// 파일에서 정수를 입력받아 배열에 하나씩 넣는다
		i++;
		num_count++;
	}

	/* 최댓값, 최솟값 인덱스 값 초기화 */
	max_idx = 0;
	min_idx = 0;

	/* 현재 최댓값과 최솟값을 저장하기 위한 변수 선언 및 초기화 */
	int max_temp = arr[0], min_temp = arr[0];

	/* 최댓값과 최솟값을 찾는 중첩 반복문 */
	for (int i = 0; i < num_count; i++)
	{
		if (arr[i] > max_temp)	// arr[i]의 값이 현재 최댓값 보다 크다면
		{
			max_temp = arr[i];	// max_temp 값을 arr[i]값으로 저장
			max_idx = i;		// max_idx가 가리키는 값을 i로 저장
		}
		if (arr[i] < min_temp)	// arr[i]의 값이 현재 최소값 보다 작다면
		{
			min_temp = arr[i];	// min_temp 값을 arr[i]값으로 저장
			min_idx = i;		// min_idx가 가리키는 값을 i로 저장
		}
	}

	int check;	// 5개씩 출력을 위한 변수 선언

	/* 배열 안에 있는 모든 값, 최댓값 최솟값 출력 */
	for (int i = 0; i < num_count; i++)
	{
		printf("%4d\t", arr[i]);   // 배열안의 정수를 4자리씩 차지하게 출력

		if (min_idx == i)	// i의 값이 최솟값 idx와 같으면
			check = 1;		// check = 1

		if (max_idx == i)	// i의 값이 최댓값 idx와 같으면
			check = 2;		// check = 2

		if ((i + 1) % 5 == 0 && i != 0)	// 한 줄에 5개씩 출력
		{
			printf("\n");

			/* 최솟값 숫자 아래에 문자열 "최솟값" 출력 */
			if (check == 1)
			{
				for (int l = 0; l < min_idx % 5; l++)
				{
					printf("\t");	// tab 이용
				}
				printf("최솟값");
				for (int k = 0; k < 5 - (min_idx % 5); k++)
				{
					printf("\t");
				}
				printf("\n");
				check = 0;	// 변수 check 초기화
			}
			/* 최댓값 숫자 아래에 문자열 "최댓값" 출력 */
			else if (check == 2)
			{
				for (int l = 0; l < max_idx % 5; l++)
				{
					printf("\t"); // tab 이용
				}
				printf("최댓값");
				for (int k = 0; k < 5 - (max_idx % 5); k++)
				{
					printf("\t");
				}
				printf("\n");
				check = 0;	// 변수 check 초기화
			}
			/* 최댓값과 최솟값이 아닌 원소 아래 공백 출력 */
			else
			{
				for (int k = 0; k < 5; k++)
				{
					printf("\t");
				}
				printf("\n");
			}
		}
	}

	printf("  min idx   = %d max idx   = %d\n  min value = %d max value = %d\n", min_idx, max_idx, arr[min_idx], arr[max_idx]);

	/* 한 줄씩 두 줄  출력 하기
	for (int m = 0; m < num_count; m++)
	{
		printf(" %4d ", arr[m]);
	}
		printf("\n");

	for (int l = 0; l < num_count; l++)
	{
		if (l == max_idx)
		printf(" 최댓값 ");
		else if (l == min_idx)
		printf("최솟값 ");
		else
		printf("      ");
	}
	printf("\n  min idx   = %d max idx   = %d\n  min value = %d max value = %d\n", min_idx, max_idx, arr[min_idx], arr[max_idx]);
	*/

	fclose(fp);

	return 0;		// O(n)
}
