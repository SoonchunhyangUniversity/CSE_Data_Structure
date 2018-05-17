/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 배열의 데이터 처리
	* 작성일 : 2018 - 03 - 20
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc함수와 free함수 사용을 위해 선언

int main() // 메인함수 시작
{
	int *temp; // 동적할당할 정수형 포인터 변수 선언, 배열의 역할
	int num; // 파일 안의 개수를 체크하기 위하여 정수 값을 받을 변수

	/* 파일 포인터 변수 fp 선언 및 초기화 */
	FILE *fp = fopen("data.txt", "r"); // data.txt를 읽기모드로 연다.

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일 오픈에 실패했으면
	{
		printf("FILE OPEN ERROR!\n"); // 에러 메세지 출력
		return 0; // 메인함수 종료
	}

	int count = 0; // 파일안의 데이터 개수를 저장할 변수, 0으로 초기화

	/* 파일안의 데이터 개수를 체크할 반복문 */
	while (!feof(fp)) // 파일이 끝날 때까지 반복
	{
		fscanf(fp, "%d", &num); // fp에 있는 정수형 데이터를 num에 저장
		count++; // count = count + 1; 데이터의 개수를 체크
	}

	/* 포인터 변수 temp를 동적할당 */
	temp = (int *)malloc(sizeof(int) * count); // malloc함수를 이용하여 4 * count 만큼의 공간 할당

	rewind(fp); // 파일 포인터 fp의 위치를 파일 처음으로 돌림

	int count2 = 0; // 동적할당 된 배열에 값을 저장할 때 사용할 변수 선언 및 초기화

	/* 파일 안의 데이터를 동적할당한 배열에 저장 */
	while (count != count2) // count와 count2가 같아질 때까지 반복
	{
		fscanf(fp, "%d", &temp[count2]); // fp의 정수형 데이터를 temp의 count2번째 배열에 저장
		count2++; // count2 = count2 + 1; 다음 배열을 가리키기 위함
	}

	/* 배열 안의 데이터를 바꾸기 전에 데이터를 출력 */
	printf("변경 전 : \n");
	for (int i = 0; i < count; i++) // count번 반복
	{
		printf("%d ", temp[i]); // temp[i]에 저장된 데이터 출력
	}
	printf("\n");

	int temp_num; // 임시로 데이터를 담을 정수형 변수 선언

	count2 -= 1; // count2 = count2 - 1;, 값을 바꾸기 위하여

	/* 데이터의 교환을 위한 반복문 */
	for (int i = 0; i < count2 / 2; i++) // count2 /2 번 반복
	{
		temp_num = temp[i]; // temp_num에 temp[i]의 값을 임시 대입
		temp[i] = temp[count2]; // temp[i]의 값을 temp[count2]; 에 대입
		temp[count2] = temp_num; // temp[count2]의 값을 temp_num에 저장된 temp[i]로 대입
		count2--; // count2 = count2 - 1; 0번 19번 교환 > 1번 18번 교환 > 2번 17번 교환
	}

	/* 배열 안의 변경된 데이터를 출력 */
	printf("변경 후 : \n");
	for (int i = 0; i < count; i++) // count번 반복
	{
		printf("%d ", temp[i]); // temp[i]에 저장된 데이터 출력
	}
	printf("\n");

	free(temp); // 동적할당한 temp 메모리 할당 해제
    fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인함수 종료
}
