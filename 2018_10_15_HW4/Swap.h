#ifndef __SWAP__
#define __SWAP__

/**
* [Swap �Լ�]
* @param a [�迭�� ������ �ּҰ�]
* @param b [�迭�� ������ �ּҰ�]
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif
