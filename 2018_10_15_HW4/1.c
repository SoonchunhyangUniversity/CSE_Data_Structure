/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 04 HW
 * 작성일 : 2018-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SortingFunction.h"

int main()
{
	int *a;
	int count = 0;
	int i;
	clock_t start, finish;
	double time;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	printf("-----------------------------------\n");
	printf("|                                 |\n");
	printf("|      ENTERING DATA IN FILE      |\n");
	printf("|                                 |\n");
	printf("-----------------------------------\n\n\n");

	while (!feof(fp))
	{
		fscanf(fp, " %d", &i);
		count++;
	}

	a = (int *)malloc(sizeof(int) * count);

	rewind(fp);

	for (i = 0; i < count; i++)
		fscanf(fp, " %d", &a[i]);

	printf("-----------------------------------------\n");
	printf("|                                       |\n");
	printf("|          DATA ENTRY COMPLETE          |\n");
	printf("|        NUMBER OF DATA : %-8d      |\n", count);
	printf("|                                       |\n");
	printf("-----------------------------------------\n\n\n");

	printf("-----------------------------------\n");
	printf("|                                 |\n");
	printf("|   START SORTING %8d DATA   |\n", count);
	printf("|                                 |\n");
	printf("-----------------------------------\n\n\n");

	start = clock();	// 알고리즘을 시작하기 전에 start에 시작 시간 저장

	// radix_sort(a, count, 5);
	// merge_sort(a, 0, count - 1);
	heap_sort(a, count);
	// quick_sort(a, 0, count - 1);
	// bubble_sort(a, count);
	// insertion_sort(a, count);
	// selection_sort(a, count);
	// shell_sort(a, count);

	finish = clock();	// 계산이 끝난후 finish에 종료 시간 저장

	time = (double)(finish - start) / CLOCKS_PER_SEC;
	// 저장된 값을 이용하여 걸린 시간 계산

	printf("---------------------------------------\n");
	printf("|                                     |\n");
	printf("|    FINISHED SORTING %8d DATA   |\n", count);
	printf("|         TIME TAKEN : %6.2f s       |\n", time);
	printf("|                                     |\n");
	printf("---------------------------------------\n\n\n");

	free(a);
	fclose(fp);

	return 0;
}
