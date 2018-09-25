/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : HW 2
 * 작성일 : 2018-09-17
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc 함수 사용을 위한 헤더파일 선언

typedef int Data; // typedef 선언으로 Data키워드로 int형 선언 가능

/* 이진 트리의 노드 구조체 */
typedef struct _node
{
	Data data; // Data형 data변수
	struct _node *left; // 왼쪽 노드를 가리키는 자체참조 구조체
	struct _node *right; // 오른쪽 노드를 가리키는 자체참조 구조체
} Node; // typedef 선언으로 Node키워드로 선언 가능

int main()
{
	Data temp;
	// 파일에서 읽어온 데이터를 임시로 저장할 변수 선언
	Node *root = NULL;
	// 이진 트리의 루트 노드 선언 및 초기화
	Node *node2 = NULL, *node3 = NULL, *node4 = NULL,
	     *node5 = NULL, *node6 = NULL, *node7 = NULL,
		 *node8 = NULL, *node9 = NULL, *node10 = NULL;
	// 이진 트리의 자식 노드들 선언 및 초기화

	/* data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일 오픈에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &temp);
		// 파일에서 정수형 데이터 하나를 읽어온다.

		/* 조건에 맞게 이진 트리에 노드 삽입 */
		switch (temp)
		{
		case 1:
			root = (Node *)malloc(sizeof(Node));
			root->data = temp;
			root->left = NULL;
			root->right = NULL;
			break;
		// 데이터가 1일 경우 루트 노드 동적 할당 후 데이터 삽입 및 초기화

		case 2:
			node2 = (Node *)malloc(sizeof(Node));
			node2->data = temp;
			node2->left = NULL;
			node2->right = NULL;
			root->left = node2;
			break;
		// 데이터가 2일 경우 노드 동적 할당 후 데이터 삽입 후
		// 루트의 왼쪽 노드로 설정 후 노드 초기화

		case 3:
			node3 = (Node *)malloc(sizeof(Node));
			node3->data = temp;
			node3->left = NULL;
			node3->right = NULL;
			root->right = node3;
			break;
		// 데이터가 3일 경우 노드 동적 할당 후 데이터 삽입 후
		// 루트의 오른쪽 노드로 설정 후 노드 초기화

		case 4:
			node4 = (Node *)malloc(sizeof(Node));
			node4->data = temp;
			node4->left = NULL;
			node4->right = NULL;
			node2->left = node4;
			break;
		// 데이터가 4일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드2의 왼쪽 노드로 설정 후 노드 초기화

		case 5:
			node5 = (Node *)malloc(sizeof(Node));
			node5->data = temp;
			node5->left = NULL;
			node5->right = NULL;
			node2->right = node5;
			break;
		// 데이터가 5일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드2의 오른쪽 노드로 설정 후 노드 초기화

		case 6:
			node6 = (Node *)malloc(sizeof(Node));
			node6->data = temp;
			node6->left = NULL;
			node6->right = NULL;
			node3->left = node6;
			break;
		// 데이터가 6일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드3의 왼쪽 노드로 설정 후 노드 초기화

		case 7:
			node7 = (Node *)malloc(sizeof(Node));
			node7->data = temp;
			node7->left = NULL;
			node7->right = NULL;
			node3->right = node7;
			break;
		// 데이터가 7일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드3의 오른쪽 노드로 설정 후 노드 초기화

		case 8:
			node8 = (Node *)malloc(sizeof(Node));
			node8->data = temp;
			node8->left = NULL;
			node8->right = NULL;
			node4->left = node8;
			break;
		// 데이터가 8일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드4의 왼쪽 노드로 설정 후 노드 초기화

		case 9:
			node9 = (Node *)malloc(sizeof(Node));
			node9->data = temp;
			node9->left = NULL;
			node9->right = NULL;
			node4->right = node9;
			break;
		// 데이터가 9일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드4의 오른쪽 노드로 설정 후 노드 초기화

		case 10:
			node10 = (Node *)malloc(sizeof(Node));
			node10->data = temp;
			node10->left = NULL;
			node10->right = NULL;
			node5->left = node10;
			break;
		// 데이터가 10일 경우 노드 동적 할당 후 데이터 삽입 후
		// 노드5의 왼쪽 노드로 설정 후 노드 초기화

		default:
			printf("DATA SET ERROR!\n");
			return 0;
		// 잘못된 데이터가 들어왔을 경우 예외처리
		}
	}

	//  데이터 삽입이 완료되었을 때 트리의 모습
	//               1
	//         2            3
	//     4      5      6      7
	//   8   9  10

	/* root가 NULL일 될 때까지 반복하는 반복문 */
	while (root != NULL)
	{
		/* 현재 노드가 최하위 노드일 경우 */
		if(root->left == NULL)
			printf("%d\n", root->data);

		/* 현재 노드가 최하위 노드가 아닐 경우*/
		else
			printf("%d의 왼쪽 자식 노드 -> ", root->data);

		root = root->left; // 왼쪽 자식노드로 이동
	}

	fclose(fp); // 열어준 파일 포인터를 닫아준다.

	return 0; // 메인 함수 종료
}
