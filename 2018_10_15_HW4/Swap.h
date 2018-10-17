#ifndef __SWAP__
#define __SWAP__

/**
* [Swap 함수]
* @param a [배열의 데이터 주소값]
* @param b [배열의 데이터 주소값]
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

#endif
