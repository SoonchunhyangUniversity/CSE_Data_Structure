/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 완전 이진 트리 검증
 * 작성일 : 2018-09-18
 */
#include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc 함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TRUE를 1로 정의
#define FALSE 0 // 기호상수 FALSE를 0으로 정의

typedef int Data; // typedef로 int형을 Data키워드로 선언 가능

/* 이진 트리의 노드 구조체 */
typedef struct _bTreeNode
{
	Data data; // Data타입 data 변수
	struct _bTreeNode * left; // 왼쪽 자식 노드를 가리킴
	struct _bTreeNode * right; // 오른쪽 자식 노드를 가리킴
} bTreeNode; // typedef로 bTreeNode 키워드로 선언 가능

/* 이진 트리의 전위 순회 함수 */
void pre_order_traverse(bTreeNode * root);
/* 완전 이진 트리 검증 함수 */
int is_complete(bTreeNode* root, int index, int number_nodes);
/* 이진 트리에 노드를 삽입하는 함수 */
bTreeNode *insert_node(bTreeNode *node, Data data);
/* 이진 트리의 노드를 생성하는 함수 */
bTreeNode *create_node(Data data);

int main()
{
	int temp;
	// 파일에서 읽어온 값을 저장할 변수 선언
	int idx = 0;
	// 이진 트리의 노드의 인덱스 값을 저장할 변수 선언 및 초기화
	int count = 0;
	// 이진 트리의 노드의 개수를 저장할 변수 선언 및 초기화
	bTreeNode *root = NULL;
	// 이진 트리의 루트 노드 선언 및 초기화

	/* 파일 포인터 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		// 정수형 데이터를 하나 읽어와 temp에 저장

		root = insert_node(root, temp);
		// insert_node함수로 temp에 저장된 데이터를 이진 트리에 삽입
		count++;
		// 이진 트리의 노드의 개수를 1 증가

		printf("Inserted %d\n", temp);
		// 이진 트리에 삽입된 데이터 출력
	}

	/* pre_order_traverse 함수로 이진 트리 전위 순회 */
	printf("Preorder >> ");
	pre_order_traverse(root); // 데이터 출력
	printf("\n");

	/* is_complete함수로 이진 트리가 완전 이진 트리인지 확인 */
	if (is_complete(root, idx, count)) // 완전 이진 트리일 경우
		printf("완전 이진 탐색트리 입니다.\n");

	else // 완전 이진 트리가 아닐 경우
		printf("완전 이진 탐색트리가 아닙니다.\n");

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/**
 * [pre_order_traverse 함수]
 * @param root [이진 트리 루트 노드]
 */
void pre_order_traverse(bTreeNode *root)
{
	/* 노드가 하나도 없을 경우 */
	if (root == NULL)
		return; // 함수 종료

	printf("%d ", root->data);
	// 현재 노드의 데이터 출력
	pre_order_traverse(root->left);
	// pre_order_traverse 함수 호출 왼쪽 자식 노드 탐색
	pre_order_traverse(root->right);
	// pre_order_traverse 함수 호출 오른쪽 자식 노드 탐색
}

/**
 * [is_complete 함수]
 * @param  root         [이진 트리 루트 노드]
 * @param  index        [root 노드의 인덱스 번호]
 * @param  number_nodes [이진 트리의 노드 개수]
 * @return              [완전 이진 트리 여부]
 */
int is_complete(bTreeNode *root, int index, int number_nodes)
{
	/* root가 NULL인 경우 */
	if (root == NULL)
		return TRUE; // TRUE 반환

	/* 현재 노드의 index가 노드의 개수보다 클 경우 */
	if (index >= number_nodes)
		return FALSE; // FALSE 반환

	return (is_complete(root->left, 2 * index + 1, number_nodes) &&
		is_complete(root->right, 2 * index + 2, number_nodes));
	// is_complete 함수를 호출해 왼쪽 노드 부터 탐색
	// 맨 아래의 자식노드까지 확인 후 함수로 복귀하여
	// is_complete 함수 호출하여 오른쪽 자식 노드 탐색
	// 둘다 TRUE가 나올 경우 TRUE 반환
}

/**
 * [insert_node 함수]
 * @param  node     [이진 트리에 삽입될 노드]
 * @param  data     [새로운 노드에 삽입될 데이터]
 * @return          [노드가 삽입된 루트 노드]
 */
bTreeNode *insert_node(bTreeNode *node, Data data)
{
	/* 루트 노드가 비어있을 경우 */
	if (node == NULL)
		return create_node(data);
	// create_node 함수로 새 노드를 만들고 데이터 삽입 후 반환

	/* 새로 삽입될 데이터가 현재 노드의 데이터 보다 작을 경우 */
	if (data < node->data)
		node->left = insert_node(node->left, data);
	// 왼쪽 노드에 insert_node 함수로 노드 삽입

	/* 새로 삽입될 데이터가 현재 노드의 데이터 보다 클 경우 */
	else if (data > node->data)
		node->right = insert_node(node->right, data);
		// 오른쪽 노드에 insert_node 함수로 노드 삽입

	return node; // 새 노드가 삽입된 노드 반환
}

/**
 * [create_node 함수]
 * @param  data [노드에 삽입될 데이터]
 * @return      [데이터가 삽입된 노드]
 */
bTreeNode *create_node(Data data)
{
	bTreeNode *temp = (bTreeNode *)malloc(sizeof(bTreeNode));
	// 데이터가 삽입될 노드를 동적 할당

	temp->data = data; // 데이터 삽입
	temp->left = NULL; // 왼쪽 자식 노드를 NULL로 저장
	temp->right = NULL; // 오른쪽 자식 노드를 NULL로 저장

	return temp; // 데이터가 저장된 노드를 반환
}
