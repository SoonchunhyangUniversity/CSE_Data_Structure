/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연결 리스트
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct _std
{
	char name[10];
	int std_num;
	int kor;
	int eng;
	int mat;
	int sum;
	double avg;
} Student;

typedef struct ListNode
{
	Student data;
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
	int i;
	int max_sum = 0, max_kor = 0, max_eng = 0, max_mat = 0;

	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");;
	printf("│========│========│====│====│====│====│======│\n");
	while (p != NULL)
	{
		printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);

		if (max_sum < p->data.sum)
			max_sum = p->data.sum;

		if (max_kor < p->data.kor)
			max_kor = p->data.kor;

		if (max_eng < p->data.eng)
			max_eng = p->data.eng;

		if (max_mat < p->data.mat)
			max_mat = p->data.mat;

		p = p->link;
	}
	printf("│========│========│====│====│====│====│======│\n\n");

	p = head;

	printf("< 총점 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");
	while (p != NULL)
	{
		if (max_sum == p->data.sum)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		}
		p = p->link;
	}
	printf("│========│========│====│====│====│====│======│\n\n");

	p = head;

	printf("< 국어 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");
	while (p != NULL)
	{
		if (max_kor == p->data.kor)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		}
		p = p->link;
	}
	printf("│========│========│====│====│====│====│======│\n\n");

	p = head;

	printf("< 영어 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");
	while (p != NULL)
	{
		if (max_eng == p->data.eng)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		}
		p = p->link;
	}
	printf("│========│========│====│====│====│====│======│\n\n");

	p = head;

	printf("< 수학 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");
	while (p != NULL)
	{
		if (max_mat == p->data.mat)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name, p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
		}
		p = p->link;
	}
	printf("│========│========│====│====│====│====│======│\n\n");
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(Student data, ListNode *link)
{
	ListNode *new_node;
	new_node = (ListNode *)malloc(sizeof(ListNode));

	if (new_node == NULL)
		error("메모리 할당 에러");

	new_node->data = data;
	new_node->link = link;

	return (new_node);
}

int main()
{
	ListNode *list = NULL;
	int std_num = 0, i;
	char line_temp[100];
	Student temp;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while(!feof(fp))
	{
		fgets(line_temp, 100, fp);
		std_num++;
	}

	rewind(fp);

	for (i = 0; i < std_num; i++)
	{
		fscanf(fp, "%d %s %d %d %d", &temp.std_num, temp.name, &temp.kor, &temp.eng, &temp.mat);
		temp.sum = (temp.kor + temp.eng + temp.mat);
		temp.avg = (double)temp.sum / 3;
		insert_node(&list, NULL, create_node(temp, NULL));
	}

	display(list);

	return 0;
}
