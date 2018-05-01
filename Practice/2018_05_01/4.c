#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct _std
{
	element std_num;
	element kor;
	element eng;
	element mat;
	element sum;
	double avg;
} Student;

typedef struct ListNode
{
	Student std;
	struct ListNode *link;
} ListNode;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

/*
phead : 리스트의 헤드 포인터의 포인터
p : 선행 노트
new_node : 삽입될 노드
*/
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead;
		*phead = new_node;
	}
	else
	{
		new_node->link = p->link;
		p->link = new_node;
	}
}

void display(ListNode *head)
{
	ListNode *p = head;

	printf("학번\t 국어\t 영어\t 수학\t 총점\t 평균\n");
	while (p != NULL)
	{
		printf("%8d %6d %6d %6d %6d %8.2lf\n", p->std.std_num, p->std.kor, p->std.eng, p->std.mat, p->std.sum, p->std.avg);
		p = p->link;
	}
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element std_num, element kor, element eng, element mat, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));

	if (new_node == NULL)
		error("메모리 할당 에러");

	new_node->std.std_num = std_num;
	new_node->std.kor = kor;
	new_node->std.eng = eng;
	new_node->std.mat = mat;
	new_node->std.sum = kor + eng + mat;
	new_node->std.avg = new_node->std.sum / 3.0;
	new_node->link = link;

	return (new_node);
}

void swap(ListNode *a, ListNode *b)
{
	Student temp = a->std;
	a->std = b->std;
	b->std = temp;
}

void sort(ListNode *phead)
{
	int check = 1;
	ListNode *node;
	ListNode *next = NULL;

	if (phead == NULL)
		return;

	while (check)
	{
		check = 0;
		node = phead;

		while (node->link != next)
		{
			if (node->std.sum < node->link->std.sum)
			{
				swap(node, node->link);
				check = 1;
			}

			node = node->link;
		}

		next = node;
	}
}

int main()
{
	ListNode *list = NULL;
	char temp[100];
	int std_count = 0, i;
	int std_num_temp, kor_temp, eng_temp, mat_temp;

	FILE *fp = fopen("data4.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fgets(temp, 100, fp);
		std_count++;
	}

	rewind(fp);

	for (i = 0; i < std_count; i++)
	{
		fscanf(fp, "%d %d %d %d", &std_num_temp, &kor_temp, &eng_temp, &mat_temp);
		insert_node(&list, NULL, create_node(std_num_temp, kor_temp, eng_temp, mat_temp, NULL));
	}

	printf("Before Sorting!!\n");
	display(list);

	printf("\n\n");

	sort(list);

	printf("After Sorting!!\n");
	display(list);

	fclose(fp);

	return 0;
}
