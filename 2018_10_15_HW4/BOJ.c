#include <stdio.h>
#include <stdlib.h>

#include "SortingFunction.h"

int main()
{
	int a[10] = { 1, 3, 5, 6, 2, 8, 9, 10, 4, 7 };

	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);

	printf("\n");

	// radix_sort(a, 10, 2);
	// merge_sort(a, 0, 9);
	// heap_sort(a, 10);
	// quick_sort(a, 0, 9);
	// bubble_sort(a, 10);
	// insertion_sort(a, 10);
	// selection_sort(a, 10);
	// shell_sort(a, 10);

	for (int i = 0; i < 10; i++)
		printf("%d ", a[i]);

	return 0;
}
