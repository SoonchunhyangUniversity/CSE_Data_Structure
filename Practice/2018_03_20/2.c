/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 문자 배열의 데이터 처리
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h>
#include <string.h>
#include <conio.h>

int main()
{
	int str_len;
	char temp[100];

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
		fscanf(fp, "%s", temp);

	str_len = strlen(temp);

	printf("문자열의 길이 : ");
	printf("%d\n", str_len);

	for (int i = 0; i < str_len; i++)
	{
		if (isupper(temp[i]))
			temp[i] = tolower(temp[i]);
	}

	printf("%s\n", temp);

    fclose(fp);

	return 0;
}
