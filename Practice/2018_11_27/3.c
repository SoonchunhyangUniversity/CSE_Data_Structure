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

typedef struct _node
{
	element item;
	struct _node *link;
} ListNode;

ListNode *hash_table[TABLESIZE];

void hash_chain_add(element item, ListNode *ht[]);
void hash_chain_find(element item, ListNode *ht[]);
int hash_function(int key);

int main()
{
	char oper;
	int check = FALSE;
	element tmp;
	FILE *fp;

	fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
		return 0;
	}

	printf("< HashTable Size = [%d] >\n\n", TABLESIZE);

	puts("< Data Insert Finish >");
	while (!feof(fp))
	{
		fscanf(fp, " %c %d", &oper, &tmp.key);

		if (oper == 'i')
		{
			hash_chain_add(tmp, hash_table);
		}

		else if (oper == 's')
		{
			if (check == FALSE)
			{
				puts("\n< Find Data Location >");
				check = TRUE;
			}

			hash_chain_find(tmp, hash_table);
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

void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);

	ListNode *ptr;
	ListNode *node_before = NULL;
	ListNode *node = ht[hash_value];

	for (; node; node_before = node, node = node->link)
	{
		if (node->item.key == item.key)
		{
			puts("중복된 탐색 키 입니다.\n");
			return;
		}
	}

	ptr = (ListNode *)malloc(sizeof(ListNode));

	ptr->item = item;
	ptr->link = NULL;

	if (node_before)
		node_before->link = ptr;

	else
		ht[hash_value] = ptr;
}

void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;

	int check = FALSE;
	int hash_value = hash_function(item.key);

	for (node = ht[hash_value]; node; node = node->link)
	{
		if (node->item.key == item.key)
		{
			check = TRUE;
			break;
		}
	}

	node = ht[hash_value];

	if (check)
	{
		while (node)
		{
			if (check)
			{
				printf("%3d 의 검색 결과 - HashTable[%d] :", item.key, hash_value);
				check = FALSE;
			}

			if (node->item.key == item.key)
			{
				printf(" (%d) ->\n", node->item.key);
				break;
			}

			else
				printf(" (%d) ->", node->item.key);

			node = node->link;
		}
	}

	else
		printf("입력하신 값 %3d 은 HashTable에서 검색되지않았습니다.\n", item.key);
}

int hash_function(int key)
{
	return key % MOD;
}
