/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 이차조사법을 이용한 HashTable 사전
 * 작성일 : 2018-11-27
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 표준 라이브러리 헤더파일 선언
#include <string.h> // 문자열 처리 라이브러리 헤더파일 선언

#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define MOD 7 // 기호 상수 MOD를 7로 정의
#define TABLE_SIZE 10 // 기호 상수 TABLE_SIZE를 10으로 정의
#define KEY_SIZE 20 // 기호 상수 KEY_SIZE를 20으로 정의
#define VAL_SIZE 20 // 기호 상수 VAL_SIZE를 20으로 정의

#define empty(e) (strlen(e.key) == 0) // 공백 확인 매크로 함수 정의
#define equal(e1, e2) (!strcmp(e1.key, e2.key)) // 동일 값 확인 매크로 함수 정의

/* 해시 데이터 구조체 */
typedef struct
{
	char key[KEY_SIZE]; // 키 필드
	char val[VAL_SIZE]; // 값 필드
} element; // element 키워드로 선언

/* 해시 구조체 */
typedef struct
{
	element hash_table[TABLE_SIZE]; // 해시 테이블 필드
	int size; // 해시 사이즈 필드
} Hash; // Hash 키워드로 선언

/* 해시 테이블 초기화 함수 */
void init_table(Hash *hash);
/* 해시 테이블에 데이터를 삽입하는 함수 */
void hash_qp_add(element item, Hash *hash);
/* 해시 테이블의 데이터를 출력하는 함수 */
void print_table(Hash *hash);
/* 해시 테이블의 키값을 숫자로 변환하는 함수 */
int transform(char *key);
/* 해시 값을 계산하는 함수 */
int hash_function(char *key);

int main()
{
	element tmp;
	// 파일에서 가져온 해시 데이터를 저장할 변수 선언
	Hash hash;
	// 해시 구조체 선언

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기 모드로 오픈 */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0; // 예외 출력 후 메인 함수 종료
	}

	init_table(&hash);
	// init_table 함수 호출로 해시 구조체 초기화

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);
	// 해시 테이블 크기 출력

	puts("< Data Insert Finish >");

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %s %s", tmp.key, tmp.val);
		// 파일에서 문자열 두개를 읽어와 변수에 저장

		hash_qp_add(tmp, &hash);
		// hash_qp_add 함수 호출로 해시 테이블에 데이터 삽입
	}

	printf("\n< Table >\n");
	print_table(&hash);
	// print_table 함수 호출로 해시 테이블 데이터 출력

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
void init_table(Hash *hash)
{
	int i;
	// 반복문에서 사용할 변수 선언

	/* 테이블 크기만큼 반복하는 반복문 */
	for (i = 0; i < TABLE_SIZE; i++)
		hash->hash_table[i].key[0] = NULL;
		// 각 테이블의 기값의 0번째 문자를 NULL로 초기화

	hash->size = 0;
	// 해시의 현재 사이즈 0으로 초기화
}

/**
 * [hash_qp_add 함수]
 * @param item [삽입될 데이터]
 * @param hash [해시 구조체]
 */
void hash_qp_add(element item, Hash *hash)
{
	int i, hash_value;
	// 처음 해시 값과 변경되는 해시 값을 저장할 변수 선언
	int inc = 0;
	// 차수를 저장할 변수 선언 및 초기화

	hash_value = i = hash_function(item.key);
	// hash_function 함수 호출로 초기 해시 값 계산 후 대입

	/* 해시 테이블에서 충돌이 생길 경우 반복하는 반복문 */
	while (!empty(hash->hash_table[i]))
	{
		/* 해시 테이블에 이미 값이 존재할 경우 예외 처리 */
		if (equal(item, hash->hash_table[i]))
		{
			printf("탐색 키가 중복되었습니다.\n");
			return; // 예외 출력 후 함수 종료
		}

		/* 해시 테이블이 포화상태일 경우 */
		if (hash->size == TABLE_SIZE)
		{
			printf("테이블이 포화상태 입니다.\n");
			return; // 예외 출력 후 함수 종료
		}

		printf("Data = %s 저장 도중 HashTable : %d 에서 ", item.key, i);
		// 충돌 전 해시 값 및  뎅터 출력

		inc = inc + 1;
		// 차수 1 증가
		i = (i + inc * inc) % TABLE_SIZE;
		// 변경된 차수로 해시 값 계산

		printf("충돌 감지 - index = %d로 증가하였습니다.\n", i);
		// 변경된 해시 값 출력
	}

	hash->hash_table[i] = item;
	// 해시 테이블에 데이터 삽입
	hash->size++;
	// 해시 테이블의 현재 크기 1증가
}

/**
 * [print_table 함수]
 * @param hash [해시 구조체]
 */
void print_table(Hash *hash)
{
	int i;
	// 반복문에서 사용할 변수 선언

	/* 해시 테이블의 크기만큼 반복하는 반복문 */
	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("HashTable[%d] -", i);
		// 테이블 번호 출력

		/* 테이블이 비어있을 경우 */
		if (empty(hash->hash_table[i]))
			puts(""); // 개행

		/* 테이블이 비어있지 않을 경우 */
		else
			printf(" %s > %s\n", hash->hash_table[i].key, hash->hash_table[i].val);
			// 해시 테이블의 키 값, 데이터 출력
	}
}

/**
 * [transform 함수]
 * @param  key [문자열 키 값]
 * @return     [정수로 변환된 키 값]
 */
int transform(char *key)
{
	int number = 0, i = 0;
	// 키 값을 저장할 변수와, 자릿수로 사용할 변수 선언 및 초기화
	int result, tmp;
	// 경계 폴딩에 사용할 변수 선언

	/* 문자열의 끝까지 반복하는 반복문 */
	while (key[i] != NULL)
	{
		result = 0;
		// 경계 폴딩한 결과를 저장할 변수 초기화

		/* 문자열의 짝수 번째 문자일 경우 */
		if ((i + 1) % 2 == 0)
		{
			tmp = key[i];
			// 문자의 아스키 코드값 저장

			/* tmp가 0보다 클 경우 반복하는 반복문 */
			while (tmp > 0)
			{
				result *= 10;
				// result에 10을 곱한후 result에 대입
				result += (tmp % 10);
				// result에 tmp를 10으로 나는 나머지 덧셈 후 result에 대입
				tmp /= 10;
				// tmp를 10으로 나누어 대입
			}
			// ex) <'a' = 97> <result = 0> <tmp = 97>
			// <result = 0 * 10> <result = 0 + 97 % 10 = 7> <tmp = 9>
			// <result = 7 * 10 = 70> <result = 70 + 9 % 10 = 79> <tmp = 0>

			number += result;
			// 경계 폴딩 진행한 값 증가
		}

		else
			number += key[i];
			// 문자의 아스키 코드값 증가

		i++;
		// 다음 문자로 이동
	}

	return number;
	// 정수값으로 변환된 키 값 반환
}

/**
 * [hash_function 함수]
 * @param  key [키 문자열]
 * @return     [해시 값]
 */
int hash_function(char *key)
{
	return transform(key) % MOD;
	// transform 함수 호출로 정수로 변환 후
	// 제산 함수를 사용해 해시 값 계산 후 반환
}
