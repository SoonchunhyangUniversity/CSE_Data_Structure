#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode * left;
	struct _bTreeNode * right;
} BTreeNode;

BTreeNode *insert(BTreeNode *Node, int key);
void PreorderTraverse(BTreeNode * bt);
int maxDepth(BTreeNode *Node);
int countNodes(BTreeNode* root);

int main()
{
	int temp;
	int idx = 0;
	int count = 0;
	BTreeNode *root = NULL;
	FILE *fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);

		if (count == 0)
			root = insert(root, temp);
		else
			insert(root, temp);

		count++;

		printf("Inserted %d\n", temp);
	}

	printf("Preordered >> ");
	PreorderTraverse(root);
	printf("\n");

	if (isComplete(root, idx, count))
		printf("완전 이진 탐색트리 입니다.\n");

	else
		printf("완전 이진 탐색트리가 아닙니다.\n");

	fclose(fp);

	return 0;
}

BTreeNode *newNode(int item)
{
	BTreeNode *temp = (BTreeNode *)malloc(sizeof(BTreeNode));

	temp->data = item;
	temp->left = temp->right = NULL;

	return temp;
}

BTreeNode *insert(BTreeNode *Node, int key)
{

    if (Node == NULL)
		return newNode(key);

    if (key < Node->data)
        Node->left  = insert(Node->left, key);

    else if (key > Node->data)
        Node->right = insert(Node->right, key);

    return Node;
}

void PreorderTraverse(BTreeNode * bt)
{
	if (bt == NULL)
		return;

	printf("%d ", bt->data);
	PreorderTraverse(bt->left);
	PreorderTraverse(bt->right);
}

int maxDepth(BTreeNode *Node)
{
	if (Node == NULL)
		return 0;

	else
	{
		int lDepth = maxDepth(Node->left);
		int rDepth = maxDepth(Node->right);

		if (lDepth > rDepth)
			return(lDepth + 1);

		else
			return(rDepth + 1);
	}
}

int countNodes(BTreeNode* root)
{
	if (root == NULL)
		return (0);

	return (1 + countNodes(root->left) + countNodes(root->right));
}

int isComplete(BTreeNode* root, int index, int number_nodes)
{
	if (root == NULL)
		return (TRUE);

	if (index >= number_nodes)
		return (FALSE);

	return (isComplete(root->left, 2 * index + 1, number_nodes) &&
		isComplete(root->right, 2 * index + 2, number_nodes));
}
