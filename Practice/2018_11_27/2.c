#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MOD 7
#define TABLESIZE 7
#define KEYSIZE 20
#define VALSIZE 20

#define empty(e) (strlen(e.key) == 0)
#define equal(e1, e2) (!strcmp(e1.key, e2.key))

typedef struct
{
	char key[KEYSIZE];
	char val[VALSIZE];
} element;

element hash_table[TABLESIZE];
int size;

void init_table(element ht[]);
void hash_qp_add(element item, element ht[]);
void print_table(element ht[]);
int transform(char *key);
int hash_function(char *key);

int main()
{
	char oper;
	int check = FALSE;
	element tmp;
	FILE *fp;

	fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0;
	}

	init_table(hash_table);

	printf("< HashTable Size = [%d] >\n\n", TABLESIZE);

	puts("< Data Insert Finish >");

	while (!feof(fp))
	{
		fscanf(fp, " %s %s", tmp.key, tmp.val);

		hash_qp_add(tmp, hash_table);
	}

	printf("\n< Table >\n");
	print_table(hash_table);

	puts("< Finish >\n");

	fclose(fp);

	return 0;
}

void init_table(element ht[])
{
	int i;

	for (i = 0; i < TABLESIZE; i++)
		ht[i].key[0] = NULL;
}

void hash_qp_add(element item, element ht[])
{
	int i, hash_value, inc = 0;
	int size = sizeof(ht) / sizeof(element);
	int *check = (int *)malloc(sizeof(int) * size);

	hash_value = i = hash_function(item.key);

	while (!empty(ht[i]))
	{
		if (equal(item, ht[i]))
		{
			printf("탐색 키가 중복되었습니다.\n");
			return;
		}

		if (size == TABLESIZE)
		{
			printf("테이블이 포화상태 입니다.\n");
			return;
		}

		printf("Data = %s 저장 도중 HashTable : %d 에서 ", item.key, i);

		inc = inc + 1;
		i = (i + inc * inc) % TABLESIZE;

		printf("충돌 감지 - index = %d로 증가하였습니다.\n", i);
	}

	ht[i] = item;
	size++;
}

void print_table(element ht[])
{
	int i;

	for (i = 0; i < TABLESIZE; i++)
	{
		printf("HashTable[%d] -", i);

		if (empty(ht[i]))
			puts("");

		else
			printf(" %s > %s\n", ht[i].key, ht[i].val);
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
