#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MOD 7
#define TABLESIZE 10

typedef struct
{
	int key;
} element;

element hash_table[TABLESIZE];

void init_table(element ht[]);
void hash_lp_add(element item, element ht[]);
void hash_lp_search(element item, element ht[]);
int hash_function(int key);

int main()
{
	char oper;
	int check = FALSE;
	element tmp;
	FILE *fp;

	fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0;
	}

	init_table(hash_table);

	printf("< HashTable Size = [%d] >\n\n", TABLESIZE);

	puts("< Data Insert Finish >");
	while(!feof(fp))
	{
		fscanf(fp, " %c %d", &oper, &tmp.key);

		if (oper == 'i')
		{
			hash_lp_add(tmp, hash_table);
		}

		else if (oper == 's')
		{
			if (check == FALSE)
			{
				puts("\n< Find Data Location >");
				check = TRUE;
			}

			hash_lp_search(tmp, hash_table);
		}

		else
		{
			puts("OPERATION ERROR!");
			return 0;
		}
	}

	puts("< Finish >\n");

	fclose(fp);

	return 0;
}

void init_table(element ht[])
{
	int i;

	for (i = 0; i < TABLESIZE; i++)
		ht[i].key = INT_MIN;
}

void hash_lp_add(element item, element ht[])
{
	int i, hash_value;

	hash_value = i = hash_function(item.key);

	while (ht[i].key != INT_MIN)
	{
		printf("data = %3d 저장 도중 Hashtable : %d 에서 충돌 감지 - index = %d로 증가하였습니다.\n",
					item.key, i, (i + 1) % MOD);

		if (ht[i].key == item.key)
		{
			printf("입력하신 %3d는 중복된 키 값입니다.\n", item.key);
			return;
		}

		i = (i + 1) % MOD;

		if (i == hash_value)
		{
			printf("테이블이 가득 찼습니다.\n");
			return;
		}

	}
	ht[i] = item;
}

void hash_lp_search(element item, element ht[])
{
	int i, hash_value;

	hash_value = i = hash_function(item.key);

	while(ht[i].key != INT_MIN)
	{
		if (ht[i].key == item.key)
		{
			printf("%3d 는 HashTable : %d에서 검색되었습니다.\n", ht[i].key, i);
			return;
		}

		i = (i + 1) % MOD;

		if (i == hash_value)
		{
			printf("입력하신 값 %3d 은 HashTable에서 검색되지 않았습니다.\n", item.key);
			return;
		}
	}
	printf("입력하신 값 %3d 은 HashTable에서 검색되지 않았습니다.\n", item.key);
}

int hash_function(int key)
{
	return key % MOD;
}
