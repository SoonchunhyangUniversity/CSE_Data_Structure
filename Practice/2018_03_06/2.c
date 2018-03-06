/*
	* * * * * * * * * * * * * * * * * *
	* 작성자 : 김민수				          *
	* 학번 : 20174444				          *
	* 학과 : 컴퓨터소프트웨어공학과	 *
	* 프로그램명 : 요금 지불 프로그램 *
	* 개발환경 : Visual Studio 2010	  *
	* 컴파일러 표준 : C99	   		      *
	* 작성일 : 2018 - 03 - 06	       *
	* * * * * * * * * * * * * * * * * *
*/

#include <stdio.h>

/* tax를 계산하기 위한 함수 */
int cal_tax(int n);
/* 지폐, 동전의 개수를 확인하기 위한 함수 */
int cal_won(int n, int arr[]);

int main()
{
	int sum_won[5] = { 0 };	// 금액의 합을 저장하기 위한 배열
	int tax[5] = { 0 };		// 세금을 저장하기 위한 배열
	int won[5] = { 0 };		// 10000원 5000원 1000원 500원 100원의 개수를 저장하기 위한 배열
	int num_count = 0;		// while문 안에서 사용할 변수

	/* 파일포인터 fp 선언 data.txt파일을 읽기모드로 오픈 */
	FILE *fp = fopen("data.txt", "r");

	/* data.txt에 있는 금액을 배열에 저장하기 위한 반복문 */
	while(!feof(fp))	// 파일이 끝날때 까지 반복
	{
		fscanf(fp, "%d", &sum_won[num_count]);
		// 파일포인터 fp에서 정수형 데이터 하나를 sum_won[num_count]에 저장
		num_count++;
		// 다음 자리를 가리키기 위하여 더해줌
	}

	/* 세금을 계산하기 위한 반복문 */
	for (int i = 0; i < 5; i++)
	{
		tax[i] = cal_tax(sum_won[i]);
	}

	/* 출력을 위한 반복문 */
	for (int i = 0; i < 5; i++)
	{
		printf("사용금액(%d) + 세금(%d) = %d\n", sum_won[i], tax[i], tax[i] + sum_won[i]);
		cal_won(tax[i] + sum_won[i], &won);
		// 지폐, 동전의 개수를 세기위한 함수 매개변수로 세금 + 금액의합, 지폐 동전의 개수를 저장할 배열을 전달
		printf("1만원 %d개\n", won[0]);
		printf("5천원 %d개\n", won[1]);
		printf("1천원 %d개\n", won[2]);
		printf("5백원 %d개\n", won[3]);
		printf("1백원 %d개\n", won[4]);
		printf("===================\n\n");


	}

	fclose(fp);	// 오픈한 파일일 닫음

	return 0;	// 메인함수 종료
}

int cal_tax(int n)
{
	if (n < 1000)			// 금액이 1000원 미만일경우
		return 0;			// 세금 0
	else if (n < 3000)		// 금액이 1000원 이상 3000원 미만일 경우
		return n * 0.15;	// 세금 15 퍼센트
	else if (n < 7000)		// 금액이 3000원 이상 7000원 미만일 경우
		return n * 0.20;	// 세금 20 퍼센트
	else if (n < 10000)		// 금액이 7000원 이상 10000원 미만일 경우
		return n * 0.27;	// 세금 27 퍼센트
	else					// 금액이 만원 이상일경우
		return n * 0.35;	// 세금 35 퍼센트
}

int cal_won(int n, int arr[])
{
	arr[0] = n / 10000;	// 10000원짜리 지폐의 수 세기
	n %= 10000;			// 10000원짜리 사용한 후 잔돈
	arr[1] = n / 5000;	// 5000원짜리 지폐의 수 세기
	n %= 5000;			// 5000원짜리 사용한 후 잔돈
	arr[2] = n / 1000;	// 1000원짜리 지폐의 수 세기
	n %= 1000;			// 1000원짜리 사용한 후 잔돈
	arr[3] = n / 500;	// 500원짜리 동전의 수 세기
	n %= 500;			// 500원짜리 사용한 후 잔돈
	arr[4] = n / 100;	// 100원짜리 동전의 수 세기
	n %= 100;			// 100원짜리 사용한 후 잔돈

	return arr;	// 지폐, 동전의 개수를 담은 배열을 return
}
