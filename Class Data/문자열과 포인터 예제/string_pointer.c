#include <stdio.h>	// 입출력을 위한 전처리명령문

void main()
{
	char str1[9] ="Computer";
	char *str2 ="Computer";

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n\n", str2);

	str2 = "Science";
	// str1 = "Science";  // 변경 불가능
	
	printf("str1 = %s\n", str1);
	printf("str2 = %s\n\n", str2);

	str1[0] = 'c';
	// str2[0] = 'c';  // 변경 불가능

	printf("str1 = %s\n", str1);
	printf("str2 = %s\n\n", str2);

}
