/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 이진 트리 연습
 * 작성일 : 2018-09-18
 */

#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp함수 사용을 위한 헤더파일 선언

#define MAX_WORD_SIZE 100 // 기호상수 MAX_WORD_SIZE를 100으로 정의
#define MAX_MEANING_SIZE 200 // 기호상수 MAX_MEANING_SIZE를 200으로 정의

/* 이진 트리의 데이터 구조체 */
typedef struct
{
	char word[MAX_WORD_SIZE]; // 단어를 저장하는 문자열
	char meaning[MAX_MEANING_SIZE]; // 뜻을 저장하는 문자열
} element; // typedef선언으로 element키워드로 사용 가능

/* 이진 트리의 노드 구조체 */
typedef struct TreeNode
{
	element key; // 데이터 필드
	struct TreeNode *left, *right;
	// 왼쪽 자식노드와 오른쪽 자식노드를 가리키는 자체참조 구조체
} TreeNode; // typedef선언으로 TreeNode키워드로 사용 가능

/* 두 단어의 우선순의를 비교하는 함수 */
int compare(element e1, element e2)
{
	return strcmp(e1.word, e2.word);
}

/* 이진 트리의 데이터를 출력하는 함수 */
void display(TreeNode *p)
{
	/* 현재 노드가 NULL일 경우 재귀 탈출 */
	if (p != NULL)
	{
		printf("(");
		display(p->left);
		printf("%s", p->key.word);
		display(p->right);
		printf(")");
	}
}

/* 이진 트리의 데이터를 검색하는 함수 */
TreeNode *search(TreeNode *root, element key)
{
	TreeNode *p = root; // 루트 노드대신 사용할 노드 선언 및 초기화

	/* 현재 노드가 NULL일 경우 반복 탈출 */
	while (p != NULL)
	{
		/* 단어의 사전적 우선순위에 따른 조건문 */
		switch (compare(key, p->key))
		{
		case -1:
			p = p->left;
			break;

		case 0:
			return p;

		case 1:
			p = p->right;
			break;
		}
	}

	return p; // 노드 p를 반환
}

/* 이진 트리에 노드를 삽입하는 함수 */
void insert_node(TreeNode **root, element key)
{
	TreeNode *p, *t, *n; // 함수에서 사용할 노드 선언

	t = *root; // t를 루트 노드로 초기화
	p = NULL; // p를 NULL로 초기화

	/* t가 NULL이 되면 반복 탈출 */
	while (t != NULL)
	{
		/* 이미 데이터가 존재하는 경우 */
		if (compare(key, t->key) == 0)
			return;

		p = t; // p노드가 t노드를 따라간다.

		/* compare함수의 반환이 -1인 경우 */
		if (compare(key, t->key) < 0)
			t = t->left; // 왼쪽 자식노드로 이동

		/* compare함수의 반환이 1인 경우 */
		else
			t = t->right; // 오른쪽 자식노드로 이동
	}

	n = (TreeNode *)malloc(sizeof(TreeNode)); // 새로운 노드 동적 할당

	if (n == NULL) // 동적 할당에 실패했을 경우
		return;

	n->key = key; // 데이터 삽입
	n->left = n->right = NULL; // 링크 초기화

	/* p가 NULL이 아닐 경우 */
	if (p != NULL)
	{
		/* compare함수의 반환이 -1인 경우 */
		if (compare(key, p->key) < 0)
			p->left = n; // p의 왼쪽에 새 노드 삽입

		/* compare함수의 반환이 1인 경우 */
		else
			p->right = n; // p의 오른쪽에 새 노드 삽입
	}

	/* p가 NULL인 경우 */
	else
		*root = n; // 루트 노드에 새 노드 대입
}

/* 이진 트리의 노드를 삭제하는 함수 */
void delete_node(TreeNode **root, element key)
{
	TreeNode *p, *child, *succ, *succ_p, *t;
	// 함수에서 사용할 노드 선언
	// p는 t의 부모노드

	p = NULL; // p를 NULL로 초기화
	t = *root; // t를 루트노드로 초기화

	/* 최하단 노드까지 탐색하거나 데이터를 찾으면 반복 종료 */
	while (t != NULL && compare(t->key, key) != 0)
	{
		p = t;
		t = (compare(key, t->key) < 0) ? t->left : t->right;
		// compare함수의 반환값에 따라 왼쪽, 오른쪽노드 이동 결정
	}

	/* t가 NULL인 경우 */
	if (t == NULL)
	{
		printf("Key is not in the tree");
		return; // 삭제할 데이터가 존재하지 않는 경우
	}

	/* 단말 노드인 경우 */
	if ((t->left == NULL) && (t->right == NULL))
	{
		/* 부모 노드가 있는 경우 */
		if (p != NULL)
		{
			if (p->left == t)
				p->left = NULL;

			else
				p->right = NULL;
		}

		/* 부모 노드가 없는 경우 */
		else
			*root = NULL;
	}

	/* 하나의 자식 노드를 가지는 경우 */
	else if ((t->left == NULL) || (t->right == NULL))
	{
		child = (t->left != NULL) ? t->left : t->right;
		// 존재하는 자식 노드를 대입

		/* 부모 노드를 자식 노드와 연결 */
		if (p != NULL)
		{
			if (p->left == t)
				p->left = child;

			else
				p->right = child;
		}

		else
			*root = child;
	}

	/* 두 개의 자식 노드를 가지는 경우 */
	else
	{
		succ_p = t;
		succ = t->right; // 오른쪽 서브트리에서 후속자 탐색

		/* 단말 노드가 일떄까지 왼쪽으로 이동 */
		while (succ->left != NULL)
		{
			succ_p = succ;
			succ = succ->left;
		}

		/* 후속자의 부모와 자식을 연결 */
		if (succ_p->left == succ)
			succ_p->left = succ->right;

		else
			succ_p->right = succ->right;

		t->key = succ->key; // 후속자를 현재 노드로 이동
		t = succ;
	}

	free(t); // 삭제될 노드의 메모리 할당 해제
}

/* 명령어들을 보여주는 함수 */
void help()
{
	printf("\n┌─────────────┐\n");
	printf("│ i : 입력    │\n");
	printf("│ d : 삭제    │\n");
	printf("│ s : 탐색    │\n");
	printf("│ p : 출력    │\n");
	printf("│ q : 종료    │\n");
	printf("└─────────────┘\n\n");
}

int main()
{
	char command;
	// 명령어를 저장할 문자형 변수 선언
	element temp;
	// 데이터를 임시로 저장할 element형 변수 선언
	TreeNode *root = NULL;
	// 이진 트리의 루트 노드 선언 및 초기화
	TreeNode *tmp;
	// 노드를 탐색할 때 사용할 노드 선언

	/* data3.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* command에 q가 들어올 때까지 반복하는 반복문 */
	do
	{
		help();
		// help함수로 사용 가능한 명령어 출력

		fscanf(fp, " %c", &command);
		// 파일에서 명령어를 입력받는다.

		printf("입력된 명령어 : %c\n", command);
		// 입력된 명령어 출력

		/* 입력받은 명령어에 따라 실행되는 조건문 */
		switch (command)
		{
		case 'i' : // i -> insert인 경우
			printf("단어 : ");
			fscanf(fp, "%s", &temp.word); // 파일에서 단어 입력
			printf("%s\n", temp.word);

			printf("의미 : ");
			fscanf(fp, "%s", &temp.meaning); // 파일에서 뜻 입력
			printf("%s\n", temp.meaning);

			insert_node(&root, temp); // 입력받은 데이터로 이진 트리에 삽입
			break;

		case 'd' : // d -> delete인 경우
			printf("단어 : ");
			fscanf(fp, "%s", &temp.word); // 파일에서 단어 입력
			printf("%s\n", temp.word);

			delete_node(&root, temp); // 입력받은 단어 삭제
			break;

		case 'p' : // p -> print인 경우
			display(root); // 이진 트리의 데이터 출력
			printf("\n");

			break;

		case 's' : // s -> search인 경우
			printf("단어 : ");
			fscanf(fp, "%s", &temp.word); // 파일에서 단어 입력
			printf("%s\n", temp.word);

			tmp = search(root, temp); // 노드를 탐색해 대입

			/* 데이터를 찾은 경우 */
			if (tmp != NULL)
				printf("의미 : %s\n", temp.meaning);

			break;
		}

	} while (command != 'q');

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
