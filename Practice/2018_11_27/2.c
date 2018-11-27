/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 이차조사법을 이용한 HashTable 사전
 * 작성일 : 2018-11-27
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MOD 7
#define TABLE_SIZE 7
#define KEY_SIZE 20
#define VAL_SIZE 20

#define empty(e) (strlen(e.key) == 0)
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

typedef struct
{
	char key[KEY_SIZE];
	char val[VAL_SIZE];
} element;

typedef struct
{
	element hash_table[TABLE_SIZE];
	int size;
} Hash;

void init_table(Hash *hash);
void hash_qp_add(element item, Hash *hash);
void print_table(Hash *hash);
int transform(char *key);
int hash_function(char *key);

int main()
{
	char oper;
	int check = FALSE;

	element tmp;
	Hash hash;

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기 모드로 오픈 */
	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0;
	}

	init_table(&hash);

	printf("< HashTable Size = [%d] >\n\n", TABLE_SIZE);

	puts("< Data Insert Finish >");

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", tmp.key, tmp.val);

		hash_qp_add(tmp, &hash);
	}

	printf("\n< Table >\n");
	print_table(&hash);

	puts("< Finish >\n");

	fclose(fp);

	return 0;
}

void init_table(Hash *hash)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
		hash->hash_table[i].key[0] = NULL;

	hash->size = 0;
}

void hash_qp_add(element item, Hash *hash)
{
	int i, hash_value, inc = 0;

	hash_value = i = hash_function(item.key);

	while (!empty(hash->hash_table[i]))
	{
		if (equal(item, hash->hash_table[i]))
		{
			printf("탐색 키가 중복되었습니다.\n");
			return;
		}

		if (hash->size == TABLE_SIZE)
		{
			printf("테이블이 포화상태 입니다.\n");
			return;
		}

		printf("Data = %s 저장 도중 HashTable : %d 에서 ", item.key, i);

		inc = inc + 1;
		i = (i + inc * inc) % TABLE_SIZE;

		printf("충돌 감지 - index = %d로 증가하였습니다.\n", i);
	}

	hash->hash_table[i] = item;
	hash->size++;
}

void print_table(Hash *hash)
{
	int i;

	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("HashTable[%d] -", i);

		if (empty(hash->hash_table[i]))
			puts("");

		else
			printf(" %s > %s\n", hash->hash_table[i].key, hash->hash_table[i].val);
	}
}

int transform(char *key)
{
	int number = 0, i = 0;
	int result, tmp;

	while (key[i] != NULL)
	{
		result = 0;

		if ((i + 1) % 2 == 0)
		{
			tmp = key[i];

			while (tmp > 0)
			{
				result *= 10;
				result += (tmp % 10);
				tmp /= 10;
			}

			number += result;
		}

		else
			number += key[i];

		i++;
	}

	return number;
}

int hash_function(char *key)
{
	return transform(key) % MOD;
}
