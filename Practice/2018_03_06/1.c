/*
	* * * * * * * * * * * * * * * * * *
	* 작성자 : 김민수									*
	* 학번 : 20174444									*
	* 학과 : 컴퓨터소프트웨어공학과	 *
	* 프로그램명 : 피라미드 만들기		*
	* 개발환경 : Visual Studio 2010		*
	* 컴파일러 표준 : C99							*
	* 작성일 : 2018 - 03 - 06				 *
	* * * * * * * * * * * * * * * * * *
*/

#include <stdio.h.>

int main()
{
	char arr[27] = { NULL }; // 문자를 담을 배열 생성 NULL포함 27개

	FILE *fp = fopen("data.txt", "w");	// 파일 포인터 생성 data.txt를 쓰기모드로 오픈

	/* 파일 오픈이 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!");
		exit(-1);
	}

	/* 배열에 알파벳을 집어넣기 위한 반복문 */
	for (int i = 0; i < 26; i++)	// 알파벳의 개수 26번 반복
	{
		arr[i] = 'A' + i;	// 'A'에서 i씩 더해주면서 배열을 채워나감
		fputs(arr, fp);	//data.txt에 한줄씩 출력
		fputs("\n", fp);	// 줄바꿈을 위한 개행
	}

	fclose(fp);	// 열린 파일 닫기

	return 0;
}
