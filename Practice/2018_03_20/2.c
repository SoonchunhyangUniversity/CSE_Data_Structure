/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 문자 배열의 데이터 처리
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <string.h> // strlen함수를 사용하기 위한 헤더파일
#include <conio.h> // isupper와 tolower를 사용하기 위한 헤더파일

int main() // 메인함수 시작
{
	int str_len; // 문자열의 길이를 저장할 정수형 변수 str_len
	char temp[100]; // 문자열을 저장할 배열 temp, 99개의 문자 + NULL

	/* 파일포인터 변수 fp 선언 및 초기화 */
	FILE *fp = fopen("data.txt", "r"); // data.txt를 읽기모드로 연다

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일 오픈에 실패했으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러 메세지 출력
		return 0; // 메인함수 종료
	}

	/* 파일안의 데이터를 문자열에 넣는 반복문 */
	while (!feof(fp)) // 파일이 끝날때 까지 반복
		fscanf(fp, "%s", temp); // fp에 있는 문자열을 temp에 저장

	/* strlen함수 이용 temp의 길이를 str_len에 저장 */
	str_len = strlen(temp);

	printf("문자열의 길이 : ");
	printf("%d\n", str_len); // 저장한 문자열의 길이 출력

	/* 대문자를 소문자로 바꿔주기위한 반복문*/
	for (int i = 0; i < str_len; i++) // str_len번 반복
	{
		if (isupper(temp[i])) // temp[i]의 값이 대문자면
			temp[i] = tolower(temp[i]); // temp[i]의 값을 소문자로 바꾸어준다.
	}

	printf("%s\n", temp); // 바뀐 문자열을 출력

    fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인함수 종료
}
