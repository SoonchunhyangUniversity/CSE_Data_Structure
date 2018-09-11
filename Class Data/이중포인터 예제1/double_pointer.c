#include <stdio.h>
 
int global_val = 30;
 
void call_by_value(int *val)
{
    val = &global_val;
	printf("calling : *val1 = %d ", *val);
}
 
void call_by_reference(int **ref)
{
    *ref = &global_val;
	printf("*val2 = %d\n", **ref);
}
 
int main()
{
    int local_val = 10;
    int *val1 = &local_val;
    int *val2 = &local_val;
 
    printf("before : *val1 = %d, *val2 = %d\n", *val1, *val2);
    call_by_value(val1);
    call_by_reference(&val2);
    printf("after  : *val1 = %d, *val2 = %d\n", *val1, *val2);
}
 