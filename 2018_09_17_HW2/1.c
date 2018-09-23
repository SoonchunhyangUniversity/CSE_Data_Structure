/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : HW 2
 * 작성일 : 2018-09-17
 */

#include <stdio.h>
#include <stdlib.h>

typedef int Data;

typedef struct _node
{
	Data data;
	struct _node *left;
	struct _node *right;
} Node;

int main()
{
	Data temp;
	Node *root = NULL;
	Node *node2 = NULL, *node3 = NULL, *node4 = NULL,
	     *node5 = NULL, *node6 = NULL, *node7 = NULL,
		 *node8 = NULL, *node9 = NULL, *node10 = NULL;

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);

		switch (temp)
		{
		case 1:
			root = (Node *)malloc(sizeof(Node));
			root->data = temp;
			root->left = NULL;
			root->right = NULL;
			break;

		case 2:
			node2 = (Node *)malloc(sizeof(Node));
			node2->data = temp;
			node2->left = NULL;
			node2->right = NULL;
			root->left = node2;
			break;

		case 3:
			node3 = (Node *)malloc(sizeof(Node));
			node3->data = temp;
			node3->left = NULL;
			node3->right = NULL;
			root->right = node3;
			break;

		case 4:
			node4 = (Node *)malloc(sizeof(Node));
			node4->data = temp;
			node4->left = NULL;
			node4->right = NULL;
			node2->left = node4;
			break;

		case 5:
			node5 = (Node *)malloc(sizeof(Node));
			node5->data = temp;
			node5->left = NULL;
			node5->right = NULL;
			node2->right = node5;
			break;

		case 6:
			node6 = (Node *)malloc(sizeof(Node));
			node6->data = temp;
			node6->left = NULL;
			node6->right = NULL;
			node3->left = node6;
			break;

		case 7:
			node7 = (Node *)malloc(sizeof(Node));
			node7->data = temp;
			node7->left = NULL;
			node7->right = NULL;
			node3->right = node7;
			break;

		case 8:
			node8 = (Node *)malloc(sizeof(Node));
			node8->data = temp;
			node8->left = NULL;
			node8->right = NULL;
			node4->left = node8;
			break;

		case 9:
			node9 = (Node *)malloc(sizeof(Node));
			node9->data = temp;
			node9->left = NULL;
			node9->right = NULL;
			node4->right = node9;
			break;

		case 10:
			node10 = (Node *)malloc(sizeof(Node));
			node10->data = temp;
			node10->left = NULL;
			node10->right = NULL;
			node5->left = node10;
			break;

		default:
			printf("DATA SET ERROR!\n");
			return 0;
		}
	}

	while (root != NULL)
	{
		if(root->left == NULL)
			printf("%d\n", root->data);

		else
			printf("%d의 왼쪽 자식 노드 -> ", root->data);

		root = root->left;
	}

	fclose(fp);

	return 0;
}
