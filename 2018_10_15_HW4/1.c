/**
 * ??깆 : 源誘쇱
 * ?踰 : 20174444
 * ?怨?: 而댄⑦곗??몄⑥닿났?怨?
 * ?濡洹몃⑤? : 04 HW
 * ??깆?: 2018-10-15
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SortingFunction.h"

int main()
{
    int *a;
    int count = 0;
    int i, temp;
    clock_t start, finish;
    double time;

    FILE fp = fopen("data.txt", "r");

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

    while(!foef(fp))
    {
        fscanf(fp, " %d", &temp);
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

    start = clock();	// ?怨由ъ?? ???湲??? start? ?? ?媛 ???

	// radix_sort(a, count, 5);
	// merge_sort(a, 0, count - 1);
	// heap_sort(a, count);
	// quick_sort(a, 0, count - 1);
	// bubble_sort(a, count);
	// insertion_sort(a, count);
	// selection_sort(a, count);
	// shell_sort(a, count);

    finish = clock();	// 怨?곗???? finish? 醫猷 ?媛 ???

    time = (double)(finish - start) / CLOCKS_PER_SEC;
    // ??λ 媛? ?댁⑺??嫄몃┛ ?媛 怨??

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
