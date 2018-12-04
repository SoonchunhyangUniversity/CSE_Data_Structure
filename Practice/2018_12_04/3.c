/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : AVL 트리
 * 작성일 : 2018-12-04
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언
#include <string.h> // strcmp 함수 사용을 위한 헤더파일 선언

#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define WORD_LEN 20 // 기호 상수 WORD_LEN을 20으로 정의

/* Avl트리의 데이터 구조체 */
typedef struct _data
{
	char word[WORD_LEN]; // 단어 필드
	char mean[WORD_LEN]; // 뜻 필드
} Data; // Data 키워드로 선언 가능

/* Avl트리의 노드 구조체 */
typedef struct AvlNode
{
	struct AvlNode *left_child; // 왼쪽 자식 노드 필드
	struct AvlNode *right_child; // 오른쪽 자식 노드 필드
	Data data; // 데이터 필드
} AvlNode; // AvlNode 키워드로 선언 가능

/* AVL트리의 오른쪽 회전 함수 */
AvlNode *rotate_LL(AvlNode *parent);
/* AVL트리의 왼쪽 회전 함수 */
AvlNode *rotate_RR(AvlNode *parent);
/* AVL트리의 오른쪽-왼쪽 회전 함수 */
AvlNode *rotate_RL(AvlNode *parent);
/* AVL트리의 왼쪽-오른쪽 회전 함수 */
AvlNode *rotate_LR(AvlNode *parent);
/* AVL트리의 균형을 맞추는 함수 */
AvlNode *rebalance(AvlNode **node);
/* AVL트리의 데이터 삽입 함수 */
AvlNode *avl_add(AvlNode **root, Data new_key);
/* AVL트리의 데이터 탐색 함수 */
AvlNode *avl_search(AvlNode *node, Data key);
/* AVL트리의 높이 반환 함수 */
int get_height(AvlNode *node);
/* AVL트리노드의 균형 인수 반환 함수 */
int get_height_diff(AvlNode *node);
/* Avl트리의 출력 함수 */
void display(AvlNode *root, AvlNode *check, int space, int count);

int main()
{
	char oper;
	// 연산자를 저장할 변수 선언
	int count = 0;
	// 노드의 개수를 저장할 변수 선언 및 초기화
	Data temp;
	// 파일에서 가져온 데이터를 임시로 저장할 변수 선언

	AvlNode *root = NULL;
	// Avl트리의 루트 노드 선언 및 초기화
	AvlNode *result;
	// Avl트리의 탐색 결과를 저장할 노드 선언

	/* 파일포인터 fp 선언 및 data3.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외 처리 */
	if (fp == NULL)
	{
		puts("File Open Error!");
        exit(1); // 예외 출력 후 종료
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c %s", &oper, temp.word);
		// 파일에서 문자하나 문자열 하나를 읽어 각 변수에 저장

		/* 연산자가 'i'일 경우 */
		if (oper == 'i')
		{
			fscanf(fp, " %s", temp.mean);
			// 문자열을 하나 더 읽어와 저장

			avl_add(&root, temp);
			// avl_add 함수 호출로 AVL트리에 삽입
			count++;
			// 노드의 개수 1 증가
		}

		/* 연산자가 's'일 경우 */
		else if (oper == 's')
		{
			result = avl_search(root, temp);
			// avl_search 함수 호출로 값 탐색 후 result에 저장

			/* 찾는 데이터가 있는 경우 */
			if (result != NULL)
			{
				/* 탐색 성공한 데이터 출력 */
				printf("< %s의 의미 탐색 >\n", result->data.word);
				printf("%s - %s\n\n", result->data.word, result->data.mean);
			}

			/* 찾는 데이터가 없는 경우 */
			else
			{
				printf("< %s는 존재하지 않는 데이터 입니다 >\n", result->data.word);
			}
		}

		/* 잘못된 연산자가 들어온 경우 */
		else
		{
			puts("Operation Error!");
			exit(1); // 예외 출력후 종료
		}
	}

	puts("< AVL 트리 출력 >");
	display(root, root, 0, count);
	// display 함수 호출로 AVL트리 출력

	fclose(fp);
	// 열어준 파일포인터 fp를 닫아준다.

	return 0;
	// 메인 함수 종료
}

/**
 * [rotate_LL 오른쪽 회전 함수]
 * @param  parent [회전할 서브 트리의 부모 노드]
 * @return        [회전된 서브 트리의 루트 노드]
 */
AvlNode *rotate_LL(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	// 자식 노드를 저장할 변수 선언 및 부모노드의 왼쪽 자식 노드 저장
	parent->left_child = child->right_child;
	// 부모 노드의 왼쪽 노드에 자식 노드의 오른쪽 노드 저장
	child->right_child = parent;
	// 자식 노드의 오른쪽 노드에 부모 노드 저장

	return child;
	// 회전된 서브 트리의 루트 노드 반환
}

/**
 * [rotate_RR 왼쪽 회전 함수]
 * @param  parent [회전할 서브 트리의 부모 노드]
 * @return        [회전된 서브 트리의 루트 노드]
 */
AvlNode *rotate_RR(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	// 자식 노드를 저장할 변수 선언 및 부모노드의 오른쪽 자식 노드 저장
	parent->right_child = child->left_child;
	// 부모 노드의 오른쪽 노드에 자식 노드의 왼쪽 노드 저장
	child->left_child = parent;
	// 자식 노드의 왼쪽 노드에 부모 노드 저장

	return child;
	// 회전된 서브 트리의 루트 노드 반환
}

/**
 * [rotate_RL 오른쪽-왼쪽 회전 함수]
 * @param  parent [회전할 서브 트리의 부모 노드]
 * @return        [회전된 서브 트리의 루트 노드]
 */
AvlNode *rotate_RL(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	// 자식 노드를 저장핣 변수 선언 및 부모노드의 오른쪽 자식 노드 저장
	parent->right_child = rotate_LL(child);
	// 부모 노드의 오른쪽 노드에 자식 노드를 오른쪽으로 회전 시킨 노드 저장

	return rotate_RR(parent);
	// rotate_RR 함수 호출로 왼쪽으로 회전한 노드 반환
}

/**
 * [rotate_LR 왼쪽-오른쪽 회전 함수]
 * @param  parent [회전할 서브 트리의 부모 노드]
 * @return        [회전된 서브 트리의 루트 노드]
 */
AvlNode *rotate_LR(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	// 자식 노드를 저장핣 변수 선언 및 부모노드의 왼쪽 자식 노드 저장
	parent->left_child = rotate_RR(child);
	// 부모 노드의 왼쪽 노드에 자식 노드를 왼쪽으로 회전 시킨 노드 저장

	return rotate_LL(parent);
	// rotate_LL 함수 호출로 오른쪽으로 회전한 노드 반환
}

/**
 * [rebalance 트리의 균형을 맞추는 함수]
 * @param  node [균형울 맞출 트리의 루트 노드]
 * @return      [균형 잡힌 트리]
 */
AvlNode *rebalance(AvlNode **node)
{
	int height_diff = get_height_diff(*node);
	// 균형 인수를 저장할 변수 선언 및 get_height_diff 함수 호출로 인수 저장

	/* 균형 인수가 1보다 클 경우 */
	if (height_diff > 1)
	{
		/* 현재 루트의 왼쪽 노드의 균형 인수가 0보다 클 경우 */
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);
			// rotate_LL 함수 호출로 오른쪽으로 회전

		/* 0보다 작을 경우 */
		else
			*node = rotate_LR(*node);
			// rotate_LR 함수 호출로 왼쪽 오른쪽 회전
	}

	/* 균형 인수가 -1보다 작은 경우 */
	else if (height_diff < -1)
	{
		/* 현재 루트의 오른쪽 노드의 균형 인수가 0보다 작을 경우 */
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);
			// rotate_RR 함수 호출로 왼쪽으로 회전

		/* 0보다 클 경우 */
		else
			*node = rotate_RL(*node);
			// rotate_RL 함수 호출로 오른쪽 왼쪽 회전
	}

	return *node;
	// 균형을 맞춘 트리 반환
}

/**
 * [avl_add AVL트리 삽입 함수]
 * @param  root    [AVL트리의 루트 노드]
 * @param  new_key [삽입할 데이터]
 * @return         [데이터가 삽입된 루트 노드]
 */
AvlNode *avl_add(AvlNode **root, Data new_key)
{
	/* 현재 노드가 NULL인 경우 */
	if (*root == NULL)
	{
		*root = (AvlNode *)malloc(sizeof(AvlNode));
		// 노드의 동적 할당 진행

		/* 동적 할당에 실패할 경우 */
		if (*root == NULL)
		{
			puts("Memory Allocation Error!");
			exit(1); // 예외 출력 후 종료
		}

		(*root)->data = new_key;
		// 새로운 노드에 데이터 삽입
		(*root)->left_child = (*root)->right_child = NULL;
		// 노드의 링크 필드 초기화
	}

	/* 기존의 문자열의 비교값이 0보다 작은 경우 */
	else if (strcmp(new_key.word, (*root)->data.word) < 0)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		// 현재 노드의 왼쪽 자식 노드에 avl_add 함수 호출로 데이터 삽입
		*root = rebalance(root);
		// rebalance 함수 호출로 균형을 맞춘다.
	}

	/* 기존의 문자열의 비교값이 0보다 큰 경우 */
	else if (strcmp(new_key.word, (*root)->data.word) > 0)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		// 현재 노드의 오른쪽 자식 ㄴ드에 avl_add 함수 호출로 데이터 삽입
		(*root) = rebalance(root);
		// rebalance 함수 호출로 균형을 맞춘다.
	}

	/* 비교값이 0인 경우 (중복된 키 존재) */
	else
	{
		puts("Key Duplication Error!");
		exit(1); // 예외 출력 후 종료
	}

	return *root;
	// 데이터가 삽입된 루트 노드 반환
}

/**
 * [avl_search AVL트리 탐색 함수]
 * @param  node [트리의 루트 노드]
 * @param  key  [탐색할 데이터]
 * @return      [탐색 결과 노드]
 */
AvlNode *avl_search(AvlNode *node, Data key)
{
	/* 비어있는 노드일 경우 */
	if (node == NULL)
		return NULL;
		// NULL 반환

	/* 탐색할 값을 찾았을 경우 */
	if (!strcmp(key.word, node->data.word))
		return node;
		// 탐색 결과 반환

	/* 두 문자열의 비교값이 0보다 작을 경우 */
	else if (strcmp(key.word, node->data.word) < 0)
		return avl_search(node->left_child, key);
		// 왼쪽 자식노드로 avl_search 함수 재귀 호출

	/* 두 문자열의 비교열이 0보다 클 경우 */
	else
		return avl_search(node->right_child, key);
		// 오른쪽 자식노드로 avl_search 함수 재귀 호출
}

/**
 * [get_height 트리 높이 반환 함수]
 * @param  node [트리의 루트 노드]
 * @return      [트리의 높이]
 */
int get_height(AvlNode *node)
{
	int height = 0;
	// 트리의 높이를 저장할 변수 선언 및 초기화

	/* 비어있는 노드가 아닐 경우 */
	if (node != NULL)
	{
		height = 1 + max(get_height(node->left_child),
			get_height(node->right_child));
		// 왼쪽 서브트리와 오른쪽 서브트리의 높이 중 최댓값 + 1 저장
	}

	return height;
	// 트리의 높이 반환
}

/**
 * [get_height_diff 노드의 균형 인수 반환 함수]
 * @param  node [균형 인수를 계산할 노드]
 * @return      [계산된 균형 인수]
 */
int get_height_diff(AvlNode *node)
{
	/* 노드가 비어있는 경우 */
	if (node == NULL)
		return 0;
		// 0 반환

	return get_height(node->left_child) - get_height(node->right_child);
	// 왼쪽 노드의 높이 - 오른쪽 노드의 높이 반환
}

/**
 * [display 이진 트리 출력 함수]
 * @param root  [트리의 순회할 노드]
 * @param check [루트 노드 확인 노드]
 * @param space [출력할 공백의 개수]
 * @param count [트리의 노드 개수]
 */
void display(AvlNode *root, AvlNode *check, int space, int count)
{
	int i;
	// 반목문에서 사용할 변수 선언

	/* 노드가 비어있을 경우 */
	if (root == NULL)
		return;
		// 재귀 탈출

	space += count;
	// 출력할 공백 노드의 개수만큼 추가

	display(root->right_child, root, space, count);
	// 오른쪽 자식노드로 재귀 호출

	printf("\n");

	/* 현재 노드가 루트노드일 경우 */
	if (!strcmp(root->data.word, check->data.word))
	{
		printf("Root  ->  ");
		// 루트 노드 확인 출력

		/* 공백 * 2 만큼 공백 출력 */
		for (i = count; i < space * 2; i++)
			printf(" ");

		printf("%7s - %-7s|\n", root->data.word, root->data.mean);
		// 노드의 데이터 정보 출력
	}

	/* 루트노드가 아닐 경우 */
	else
	{
		/* 공백 * 3 만큼 공백 출력 */
		for (i = count; i < space * 3; i++)
			printf(" ");

		printf("%7s - %-7s|\n", root->data.word, root->data.mean);
		// 노드의 데이터 정보 출력
	}

	display(root->left_child, root, space, count);
	// 왼쪽 자식노드로 재귀 호출
}
