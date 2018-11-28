/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 체이닝을 이용한 HashTable
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

/* 체이닝을 이용한 해시의 노드 구조체 */
typedef struct _node
{
	element item; // 데이터 필드
	struct _node *link; // 링크 필드
} ListNode; // ListNode 키워드로 선언

/* TABLE_SIZE 크기의 해시 테이블 전역 변수 선언 */
ListNode *hash_table[TABLE_SIZE];

/* 해시 테이블에 데이터를 삽입하는 함수 */
void hash_chain_add(element item, ListNode *ht[]);
/* 해시 테이블에서 데이터를 탐색하는 함수 */
void hash_chain_find(element item, ListNode *ht[]);
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

    /* 파일 포인터 fp 선언 및 data3.txt를 읽기 모드로 오픈 */
	FILE *fp = fopen("data3.txt", "r");

    /* 파일을 여는데 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0; // 예외 출력 후 메인 함수 종료
	}

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);
    // 해시 테이블 크기 출력

	puts("< Data Insert Finish >");

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c %d", &oper, &tmp.key);
        // 파일에서 문자 정수 하나를 읽어와 각 변수에 저장

        /* 연산자가 i일 경우 삽입(insert) */
		if (oper == 'i')
		{
			hash_chain_add(tmp, hash_table);
            // hash_chain_add 함수 호출로 해시 테이블에 데이터 삽입
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

			hash_chain_find(tmp, hash_table);
            // hash_chain_find 함수 호출로 해시 테이블 데이터 탐색
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
 * [hash_chain_add 함수]
 * @param item [삽입될 데이터]
 * @param ht   [해시 테이블]
 */
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
    // 해시 값을 저장할 변수 선언 및 hash_function 함수 호출로 값 초기화

	ListNode *ptr;
    // 새로운 노드를 저장할 변수 선언
	ListNode *node_before = NULL;
    // 이전 노드를 저장할 변수 선언 및 초기화
	ListNode *node = ht[hash_value];
    // 현재 노드를 저장할 변수 선언 및 초기화

    /* 이전 노드를 저장 하며 노드의 끝까지 반복하는 반복문 */
	for (; node; node_before = node, node = node->link)
	{
        /* 삽입할 데이터가 노드에 이미 있는 경우 */
		if (node->item.key == item.key)
		{
			puts("중복된 탐색 키 입니다.\n");
			return; // 예외 출력 후 함수 종료
		}
	}

	ptr = (ListNode *)malloc(sizeof(ListNode));
    // 삽입할 노드 메모리 동적 할당

	ptr->item = item;
    // 노드의 데이터 필드에 데이터 삽입
	ptr->link = NULL;
    // 노드의 링크에 NULL 저장

    /* 해시 테이블에 데이터가 있는 경우 */
	if (node_before)
		node_before->link = ptr;
        // 이전 노드의 링크에 새로운 노드 연결

    /* 해시 테이블에 데이터가 없는 경우 */
	else
		ht[hash_value] = ptr;
        // 처음 노드에 새로운 노드 대입
}

/**
 * [hash_chain_find 함수]
 * @param item [탐색할 데이터]
 * @param ht   [해시 테이블]
 */
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;
    // 원본 리스트의 값 변경을 막기위해 사용할 변수 선언

	int check = FALSE;
    // 테이블에 데이터 존재 확인, 테이블 정보 중복 출력 방지에 사용할 변수 선언 및 초기화
	int hash_value = hash_function(item.key);
    // 해시 값을 저장할 변수 선언 및 hash_function 함수 호출로 해시 값 계산 후 대입

    /* 노드의 끝까지 반복하는 반복문 */
	for (node = ht[hash_value]; node; node = node->link)
	{
        /* 테이블에 데이터가 있을 경우 */
		if (node->item.key == item.key)
		{
			check = TRUE;
            // check변수를 TRUE로 변경
			break;
            // 반복문 탈출
		}
	}

    /* 해시 테이블에 데이터가 존재할 경우 */
	if (check)
	{
        node = ht[hash_value];
        // node의 해시 테이블의 해시 값의 리스트 대입

        /* 노드의 끝까지 반복하는 반복문 */
		while (node)
		{
            /* 첫 데이터가 출력되는 경우 */
			if (check)
			{
				printf("%3d 의 검색 결과 - HashTable[%d] :", item.key, hash_value);
                // 데이터와 해시 테이블 정보 출력
				check = FALSE;
                // check변수 FALSE로 변경
			}

            /* 현재 노드의 데이터가 탐색 중인 데이터인 경우 */
			if (node->item.key == item.key)
			{
				printf(" (%d) ->\n", node->item.key);
                // 현재 노드의 데이터 출력
				break;
                // 반복문 탈출
			}

            /* 현재 노드의 데이터가 탐색 중인 데이터가 아닌 경우 */
			else
				printf(" (%d) ->", node->item.key);
                // 현재 노드의 데이터 출력

			node = node->link;
            // 다음 노드로 이동
		}
	}

    /* 탐색 중인 데이터가 해시 테이블에 없는 경우 */
	else
		printf("입력하신 값 %3d 은 HashTable에서 검색되지않았습니다.\n", item.key);
        // 탐색 중인 데이터가 존재하지 않음을 출력
}

/**
 * [hash_function 함수]
 * @param  key [키 값]
 * @return     [해시 값]
 */
int hash_function(int key)
{
	return key % MOD;
	// 제산 함수를 사용하여 해시 값 계산 후 반환
}
