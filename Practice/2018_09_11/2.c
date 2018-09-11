/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 파일에서 자료 읽어오기
 * 작성일 : 2018-09-11
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp, strcpy 함수 사용을 위한 헤더파일 선언

#define LEN 20 // 기호 상수 LEN 을 20으로 정의
#define TRUE 1 // 기호상수 TRUE를 1로 정의
#define FALSE 0 // 기호상수 FALSE를 0으로 정의

enum subject { KOR = 1, ENG, MATH }; // 과목명을 열거형으로 정의

/**
 * Name : Data
 * type : struct
 * Dscription
 * [학생의 정보를 저장]
 */
typedef struct _data
{
	char name[LEN];
	int math;
	int eng;
	int kor;
	int sum;
	double avg;
} Data;

/**
 * Name : Node
 * type : struct
 * Dscription
 * [단일 연결리스트의 노드 구조체]
 */
typedef struct _node
{
	Data data;
	struct _node *next;
} Node;

/* 연결리스트의 노드 삽입 함수 정의*/
void insert(Node **phead, Node *new_node);
/* 연결리스트의 데이터를 출력하는 함수 정의 */
void display(Node *head);
/* 연결리스트의 노드에 데이터를 삽입하는 함수 정의 */
void insert_score(Node *head, int data, char *sub, char *name);
/* 학생의 이름을 비교하는 함수 정의 */
int compare_std_name(Node *head, char *name);
/* 과목 이름을 비교하는 함수 정의 */
int compare_sub(char *sub);
/* 노드를 생성하는 함수 정의*/
Node *create_node(Data data, Node *next);

int main()
{
	Node *list = NULL;
	// 연결리스트 헤드 노드의 선언 및 초기화
	Data temp;
	// 데이터를 임시로 저장할 변수 선언
	char name[LEN] = { NULL };
	// 학생의 이름을 임시로 저장할 변수 선언
	char sub[LEN] = { NULL };
	// 과목명을 임시로 저장할 변수 선언
	int score;
	// 점수를 임시로 저장할 변수 선언

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일 오픈에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", name, sub, &score);
		// 파일의 데이터를 읽어온다.

		/* compare_std_name함수로 학생 이름 비교 */
		if (!compare_std_name(list, name)) // 리스트에 학생이 없다면
		{
			strcpy(temp.name, name);
			// strcpy함수로 temp변수에 이름 복사

			/* *
			 * compare_sub 함수로 과목명 비교
			 * 해당 과목 점수 대입 및 나머지 과목 0으로 초기화
			 * */
			if (compare_sub(sub) == KOR) // sub가  KOR일 경우
			{
				temp.kor = score;
				temp.eng = 0;
				temp.math = 0;
			}

			else if (compare_sub(sub) == ENG) // sub가 ENG일 경우
			{
				temp.kor = 0;
				temp.eng = score;
				temp.math = 0;
			}

			else if (compare_sub(sub) == MATH) // sub가 MATH일 경우
			{
				temp.kor = 0;
				temp.eng = 0;
				temp.math = score;
			}

			insert(&list, create_node(temp, NULL));
			// create_node함수로 노드를 생성한 후 insert함수로 리스트에 삽입

		}

		/* 리스트의 학생 데이터가 존재할 경우 */
		else
			insert_score(list, score, sub, name);
			// insert_score함수로 데이터 삽입
		}

		display(list); // display 함수로 리스트의 데이터 출력

		fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

		return 0; // 메인 함수 종료
	}

/**
 * [insert 함수]
 * @param phead    [연결리스트의 헤드 포인터]
 * @param new_node [연결리스트에 삽일될 노드]
 */
void insert(Node **phead, Node *new_node)
{
	Node *cur = *phead;
	// 헤드 포인터 대신에 사용할 노드 선언 및 초기화

	/* 헤드 포인터가 NULL일 경우 */
	if ((*phead) == NULL)
		(*phead) = new_node;

	/* 리스트에 노드가 존재할 경우 */
	else
	{
		/* 리스트의 끝까지 이동 */
		while (cur->next != NULL)
			cur = cur->next;

		cur->next = new_node; // cur의 next에 new_node 연결
	}
}

/**
 * [display 함수]
 * @param head [연결리스트의 헤드 노드]
 */
void display(Node *head)
{
	Node *p = head;
	// 헤드 노드 대신 사용할 노드 선언 및 초기화

	/* 연결리스트의 끝까지 반복하는 반복문 */
	while (p != NULL)
	{
		/* 리스트의 데이터 출력 */
		printf("< %s 학생의 점수 >\n", p->data.name);
		printf("- 국어 : %6d점\n", p->data.kor);
		printf("- 영어 : %6d점\n", p->data.eng);
		printf("- 수학 : %6d점\n", p->data.math);
		printf("- 평균 : %6.2f점\n\n", p->data.avg);

		p = p->next; // 다음 노드로 이동
	}
}

/**
 * [insert_score 함수]
 * @param head  [연결리스트의 헤드 노드]
 * @param score ["sub" 과목의 점수]
 * @param sub   [과목의 이름]
 * @param name  [학생의 이름]
 */
void insert_score(Node *head, int score, char *sub, char *name)
{
	Node *p = head;
	// 헤드 노드 대신에 사용할 변수 선언 및 초기화

	/* 연결리스트의 끝까지 반복하는 반복문 */
	while (p != NULL)
	{
		/* 매개변수 "name"과 같은 이름 데이터를 가진 노드일 경우 */
		if (!strcmp(p->data.name, name))
		{
			/* compare_sub함수로 과목명을 비교하여 데이터 삽입 */
			if (compare_sub(sub) == KOR)
				p->data.kor = score;

			else if (compare_sub(sub) == ENG)
				p->data.eng = score;

			else if (compare_sub(sub) == MATH)
				p->data.math = score;

			/* 과목 점수가 업데이트 될 때 마다 총점, 평균 갱신 */
			p->data.sum = p->data.kor + p->data.eng + p->data.math;
			p->data.avg = p->data.sum / 3.0;
		}
		p = p->next; // 다음 노드로 이동
	}
}

/**
 * [compare_std_name 함수]
 * @param  head [연결리스트의 헤드 노드]
 * @param  name [학생의 이름]
 * @return      [학생 데이터의 존재 유무]
 */
int compare_std_name(Node *head, char *name)
{
	Node *p = head;
	// 헤드 노드 대신에 사용할 변수 선언 및 초기화

	/* 연결리스트의 끝까지 반복하는 반복문 */
	while (p != NULL)
	{
		/* 학생의 이름이 존재할 경우 */
		if (!strcmp(p->data.name, name))
			return TRUE; // TRUE 반환

		p = p->next; // 다음 노드로 이동
	}

	return FALSE; // FALSE 반환
}

/**
 * [compare_sub 함수]
 * @param  sub [과목의 이름]
 * @return     [과목의 번호]
 */
int compare_sub(char *sub)
{
	/* sub가 "국어"일 경우 */
	if (!strcmp(sub, "국어"))
		return KOR; // enum -> KOR 반환

	/* sub가 "영어"일 경우 */
	else if (!strcmp(sub, "영어"))
		return ENG; // enum -> ENG 반환

	/* sub가 "수학"일 경우 */
	else if (!strcmp(sub, "수학"))
		return MATH; // enum -> MATH 반환

	/* 올바르지 않은 과목명이 들어왔을 경우 */
	else
		return FALSE; // FALSE 반환
}

/**
 * [create_node 함수]
 * @param  data [생성된 노드에 들어갈 데이터]
 * @param  next [생성된 노드에 연결될 노드]
 * @return      [데이터가 저장된 노드]
 */
Node *create_node(Data data, Node *next)
{
	Node *new_node;
	// 새로운 노드 선언
	new_node = (Node *)malloc(sizeof(Node));
	// 노드의 크기만큼 동적 할당

	/* 동적 할당에 실패할 경우 */
	if (new_node == NULL)
		printf("메모리 할당 에러");

	/* 매개변수로 받은 데이터 삽입 */
	new_node->data = data;
	new_node->next = next;

	return new_node; // 노드를 반환
}
