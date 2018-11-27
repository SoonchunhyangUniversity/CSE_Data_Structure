/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 선형조사법을 이용한 HashTable
 * 작성일 : 2018-11-27
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 표준 라이브러리 헤더파일 선언

#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define MOD 7 // 기호 상수 MOD를 7로 정의
#define TABLE_SIZE 10 // 기호 상수 TABLE_SIZE를 10으로 정의

/* 해시의 데이터 구조체 */
typedef struct
{
	int key; // 키 값 필드
} element; // element 키워드로 선언

/* TABLE_SIZE 크기의 해시 테이블 전역 변수 선언 */
element hash_table[TABLE_SIZE];

/* 해시 테이블을 초기화 하는 함수 */
void init_table(element ht[]);
/* 해시 테이블에 데이터를 삽입하는 함수 */
void hash_lp_add(element item, element ht[]);
/* 해시 테이블에서 데이터를 탐색하는 함수 */
void hash_lp_search(element item, element ht[]);
/* 해시 값을 계산하는 함수 */
int hash_function(int key);

int main()
{
	char oper;
	// 연산자를 저장할 변수 선언
	int check = FALSE;
	// 처음 탐색을 시작하는지 확인할 변수 선언 및 초기화
	element tmp;
	// 파일에서 가져온 해시 데이터를 저장할 변수 선언

	/* 파일 포인터 fp 선언 및 data1.txt를 읽기 모드로 오픈 */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0; // 예외 출력 후 메인 함수 종료
	}

	init_table(hash_table);
	// init_table 함수 호출로 해시 테이블 초기화

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);
	// 해시 테이블 크기 출력

	puts("< Data Insert Finish >");

	/* 파일의 끝까지 반복하는 반복문 */
	while(!feof(fp))
	{
		fscanf(fp, " %c %d", &oper, &tmp.key);
		// 파일에서 문자 정수 하나를 읽어와 각 변수에 저장

		/* 연산자가 i일 경우 삽입(insert) */
		if (oper == 'i')
		{
			hash_lp_add(tmp, hash_table);
			// hash_lp_add 함수 호출로 해시 테이블에 데이터 삽입
		}

		/* 연산자가 s일 경우 탐색(search) */
		else if (oper == 's')
		{
			/* 첫 데이터 탐색일 경우 */
			if (check == FALSE)
			{
				puts("\n< Find Data Location >");
				// 데이터 탐색 시작 표시
				check = TRUE;
				// 초기 탐색이 아닌 것으로 check 변수 변경
			}

			hash_lp_search(tmp, hash_table);
			// hash_lp_search 함수 호출로 해시 테이블 데이터 탐색
		}

		/* 잘못된 연산자가 들어왔을 경우 예외 처리 */
		else
		{
			puts("OPERATION ERROR!");
			return 0; // 예외 출력 후 메인 함수 종료
		}
	}

	puts("< Finish >\n");
	// 프로그램이 끝났음을 출력

	fclose(fp);
	// 파일 포인터 fp를 닫아준다.

	return 0;
	// 메인 함수 종료
}

/**
 * [init_table 함수]
 * @param ht [해시 테이블]
 */
void init_table(element ht[])
{
	int i;
	// 반복문에서 사용할 변수 선언

	/* 테이블 크기만큼 반복하는 반복문 */
	for (i = 0; i < TABLE_SIZE; i++)
		ht[i].key = INT_MIN;
		// 각 테이블의 키 값을 INT_MIN으로 초기화
}

/**
 * [hash_lp_add 함수]
 * @param item [삽입될 데이터]
 * @param ht   [해시 테이블]
 */
void hash_lp_add(element item, element ht[])
{
	int i, hash_value;
	// 처음 해시 값과 변경되는 해시 값을 저장할 변수 선언

	hash_value = i = hash_function(item.key);
	// hash_function 함수 호출로 초기 해시 값 계산 후 대입

	/* 해시 테이블에서 충돌이 생길 경우 반복하는 반복문 */
	while (ht[i].key != INT_MIN)
	{
		/* 해시 테이블에 이미 값이 존재할 경우 예외 처리 */
		if (ht[i].key == item.key)
		{
			printf("입력하신 %3d는 중복된 키 값입니다.\n", item.key);
			return; // 예외 출력 후 함수 종료
		}

		printf("data = %3d 저장 도중 Hashtable : %d 에서", item.key, i);
		// 충돌 전 해시 값 및 데이터 출력

		i = (i + 1) % TABLE_SIZE;
		// 해시 값 변경

		printf(" 충돌 감지 - index = %d로 증가하였습니다.\n", i);
		// 변경 된 해시 값 출력

		/* i의 값이 초기 해시 값과 같아질 경우 포화상태 */
		if (i == hash_value)
		{
			printf("테이블이 가득 찼습니다.\n");
			return; // 예외 출력 후 함수 종료
		}
	}

	ht[i] = item;
	// 해시 테이블에 데이터 삽입
}

/**
 * [hash_lp_search 함수]
 * @param item [탐색할 데이터]
 * @param ht   [해시 테이블]
 */
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	// 처음 해시 값과 변경되는 해시 값을 저장할 변수 선언

	hash_value = i = hash_function(item.key);
	// hash_function 함수 호출로 초기 해시 값 계산 후 대입

	/* 해시 테이블에 데이터가 존재할 경우 반복하는 반복문 */
	while(ht[i].key != INT_MIN)
	{
		/* 해시 테이블에 찾는 데이터가 있을 경우 */
		if (ht[i].key == item.key)
		{
			printf("%3d 는 HashTable : %d 에서 검색되었습니다.\n", ht[i].key, i);
			return; // 탐색 성공 후 함수 종료
		}

		i = (i + 1) % TABLE_SIZE;
		// 해시 값 변경

		/* i의 값이 초기 해시 값과 같아질 경우 값 탐색 실패 */
		if (i == hash_value)
		{
			printf("입력하신 값 %3d 은 HashTable에서 검색되지 않았습니다.\n", item.key);
			return; // 탐색 실패 출력 후 함수 종료
		}
	}

	printf("입력하신 값 %3d 은 HashTable에서 검색되지 않았습니다.\n", item.key);
	// 해당 데이터가 존재하지 않음을 출력
}

/**
 * [hash_function 함수]
 * @param  key [키 값]
 * @return     [해시 값]
 */
int hash_function(int key)
{
	return key % MOD;
	// 제산 함수를 사용 하여 해시 값 계산 후 반환
}
