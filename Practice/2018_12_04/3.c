#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define WORD_LEN 20

typedef struct _data
{
	char word[WORD_LEN];
	char mean[WORD_LEN];
} Data;

typedef struct AvlNode
{
	struct AvlNode *left_child;
	struct AvlNode *right_child;
	Data data;
} AvlNode;

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
/* 트리의 높이 반환 함수 */
int get_height(AvlNode *node);
/* AVL트리노드의 균형 인수 반환 함수 */
int get_height_diff(AvlNode *node);
void display(AvlNode *root, AvlNode *check, int space, int count);

int main()
{
	char oper;
	int count = 0;
	Data temp;

	AvlNode *root = NULL;
	AvlNode *result;

	FILE *fp = fopen("data3.txt", "r");

	if (fp == NULL)
	{
		puts("File Open Error!");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, " %c %s", &oper, temp.word);

		if (oper == 'i')
		{
			fscanf(fp, " %s", temp.mean);

			avl_add(&root, temp);
			count++;
		}

		else if (oper == 's')
		{
			result = avl_search(root, temp);
			printf("< %s의 의미 탐색 >\n", result->data.word);
			printf("%s - %s\n\n", result->data.word, result->data.mean);
		}

		else
		{
			puts("Operation Error!");
			exit(1);
		}
	}

	puts("< AVL 트리 출력 >");
	display(root, root, 0, count);

	fclose(fp);

	return 0;
}

// 오른쪽 회전 함수
AvlNode *rotate_LL(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;

	return child;
}

// 왼쪽 회전 함수
AvlNode *rotate_RR(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;

	return child;
}

// 오른쪽-왼쪽 회전 함수
AvlNode *rotate_RL(AvlNode *parent)
{
	AvlNode *child = parent->right_child;
	parent->right_child = rotate_LL(child);

	return rotate_RR(parent);
}

// 왼쪽-오른쪽 회전 함수
AvlNode *rotate_LR(AvlNode *parent)
{
	AvlNode *child = parent->left_child;
	parent->left_child = rotate_RR(child);

	return rotate_LL(parent);
}

// 트리를 균형트리로 만든다
AvlNode *rebalance(AvlNode **node)
{
	int height_diff = get_height_diff(*node);

	if (height_diff > 1)
	{
		if (get_height_diff((*node)->left_child) > 0)
			*node = rotate_LL(*node);

		else
			*node = rotate_LR(*node);
	}

	else if (height_diff < -1)
	{
		if (get_height_diff((*node)->right_child) < 0)
			*node = rotate_RR(*node);

		else
			*node = rotate_RL(*node);
	}

	return *node;
}

// AVL 트리의 삽입 연산
AvlNode *avl_add(AvlNode **root, Data new_key)
{
	if (*root == NULL)
	{
		*root = (AvlNode *)malloc(sizeof(AvlNode));

		if (*root == NULL)
		{
			puts("Memory Allocation Error!");
			exit(1);
		}

		(*root)->data = new_key;
		(*root)->left_child = (*root)->right_child = NULL;
	}

	else if (strcmp(new_key.word, (*root)->data.word) < 0)
	{
		(*root)->left_child = avl_add(&((*root)->left_child), new_key);
		*root = rebalance(root);
	}

	else if (strcmp(new_key.word, (*root)->data.word) > 0)
	{
		(*root)->right_child = avl_add(&((*root)->right_child), new_key);
		(*root) = rebalance(root);
	}

	else
	{
		puts("Key Duplication Error!");
		exit(1);
	}

	return *root;
}

// AVL 트리의 탐색함수
AvlNode *avl_search(AvlNode *node, Data key)
{
	if (node == NULL)
		return NULL;

	if (!strcmp(key.word, node->data.word))
		return node;

	else if (strcmp(key.word, node->data.word) < 0)
		return avl_search(node->left_child, key);

	else
		return avl_search(node->right_child, key);
}

// 트리의 높이를 반환
int get_height(AvlNode *node)
{
	int height = 0;

	if (node != NULL)
	{
		height = 1 + max(get_height(node->left_child),
			get_height(node->right_child));
	}

	return height;
}

// 노드의 균형인수를 반환
int get_height_diff(AvlNode *node)
{
	if (node == NULL)
		return 0;

	return get_height(node->left_child) - get_height(node->right_child);
}

void display(AvlNode *root, AvlNode *check, int space, int count)
{
	int i;

	if (root == NULL)
		return;

	space += count;

	display(root->right_child, root, space, count);

	printf("\n");

	if (!strcmp(root->data.word, check->data.word))
	{
		printf("Root  ->  ");

		for (i = count; i < space * 2; i++)
			printf(" ");

		printf("%7s - %-7s|\n", root->data.word, root->data.mean);
	}

	else
	{
		for (i = count; i < space * 3; i++)
			printf(" ");

		printf("%7s - %-7s|\n", root->data.word, root->data.mean);
	}

	display(root->left_child, root, space, count);
}
