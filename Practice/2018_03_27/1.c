/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 성적 관리 프로그램
	* 작성일 : 2018 - 03 - 27
	*
*/

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언

int main() // 메인함수 시작
{
	int **arr2; // 2차원 배열 동적할당에 사용할 이중 포인터 변수 선언
	int temp; // 값을 임시로 담을 정수형 변수 선언
	int sum = 0, kor_sum = 0, eng_sum = 0, mat_sum = 0, total_sum = 0;
	// 문제에 필요한 변수 선언 및 0으로 초기화, 합, 국어, 영어, 수학, 전체 합
	double total_avg = 0; // 평균의 평균을 구하기 위한 변수 선언 및 초기화
	double avg; // 평균을 저장할 실수형 변수 선언

	/* 파일포인터 fp를 선언 및 data.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL) // 파일이 존재하지 않으면
	{
		fprintf(stderr, "FILE OPEN ERROR!\n"); // 에러메세지 출력
		exit(-1); // 종료
	}

	int count = 0; // 학생의 수를 저장할 변수 선언 및 초기화

	/* 학생의 수를 알기 위한 반복문 */
	while (!feof(fp)) // 파일이 끝날 때 까지 반복
	{
		fscanf(fp, "%d %d %d %d", &temp, &temp, &temp, &temp);
		// 학번, 국어, 영어, 수학 점수를 일단 받음
		count++; // 학생의수++;
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌림

	/* 받은 데이터를 토대로 2차원 배열 동적 할당 진행 */
	arr2 = (int**)malloc(sizeof(int *) * count);
	for (int i = 0; i < count; i++)
		arr2[i] = (int *)malloc(sizeof(int) * 4);

	/* 동적 할당한 배열에 값을 넣기 위한 반복문 */
	while (!feof(fp)) // 파일의 끝까지  반복
	{
		for (int i = 0; i < count; i++) // count번 반복
		{
			for (int j = 0; j < 4; j++) // 4번 반복
				fscanf(fp, "%d", &arr2[i][j]); // 배열에 데이터를 저장
		}
	}

	printf("===========================================================\n");
	printf("│    학번    │  국어  │  영어  │  수학  │  총점  │  평균  │\n");

	/* 한 줄 씩 데이터를 출력한다 */
	for (int i = 0; i < count; i++) // count번 반복한다.
	{
		int j = 0; // 2차원 배열의 값을 출력하기 위한 변수

		sum = arr2[i][j + 1] + arr2[i][j + 2] + arr2[i][j + 3];
		// 배열안 한 줄의 값을 모두 더함 (총점)
		avg = (double)sum / 3; // 총점을 토대로 평균 계산
		kor_sum += arr2[i][j + 1]; // 모든 학생의 국어 점수의 합 저장
		eng_sum += arr2[i][j + 2]; // 모든 학생의 영어 점수의 합 저장
		mat_sum += arr2[i][j + 3]; // 모든 학생의 수학 점수의 합 저장
		total_sum += sum; // 모든 학생의 총점의 합 저장
		total_avg += avg; // 모든 학생의 평균의 합 저장
		/* 데이터를 줄 맞춰 출력*/
		printf("│  %8d  │  %4d  │  %4d  │  %4d  │  %4d  │  %4.2f │\n", arr2[i][j], arr2[i][j + 1], arr2[i][j + 2], arr2[i][j + 3], sum, avg);
	}
	/* 데이터를 출력*/
	printf("===========================================================\n");
	printf("│   평 균    │  %4.2f │  %4.2f │  %4.2f │  %4.2f │ %4.2f │\n", (double)kor_sum / count, (double)eng_sum / count,
	(double) mat_sum / count, (double)total_sum / count, (double)total_avg / count);
	printf("===========================================================\n");

	/* 동적 할당한 배열의 할당 해제*/
	for(int i = 0; i < count; i++)
		free(arr2[i]);
	free(arr2);

	fclose(fp); // 파일 포인터를 닫음

	return 0; // 메인함수 종료
}
