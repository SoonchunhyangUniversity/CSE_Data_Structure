/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 이중 연결 리스트
	* 작성일 : 2018 - 05 - 08
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free함수 사용을 위한 헤더파일 선언
#define TRUE 1 // 기호상수 TRUE 1 선언
#define FALSE 0 // 기호상수 FALSE 0 선언

typedef int element; // typedef로 int 키워드 대신 element 키워드 사용 가능

/* 이중 연결 리스트의 노드 구조체 */
typedef struct DlistNode
{
	element data; // 정수형 데이터
	struct DlistNode *llink; // 왼쪽 노드를 가리키는 포인터 구조체
	struct DlistNode *rlink; // 오른쪽 노드를 가리키는 포인터 구조체
} DlistNode; // typedef로 구조체 선언 없이 DlistNode 키워드 사용 가능

/* 이중 연결 리스트를 초기화하는 함수 */
void init(DlistNode *phead)
{
	phead->llink = phead; // phead의 llink가 자기 자신을 가리키게 한다.
	phead->rlink = phead; // phead의 rlink가 자기 자신을 가리키게 한다.
}

/* 이중 연결 리스트의 노드를 출력하는 함수 */
void display(DlistNode *phead)
{
	DlistNode *p; // phead대신에 사용할 리스트 선언

	printf("< ");

	/* p에 phead의 rlink 대입 p 가 phead와 같아질 때 까지 다음 노드로 이동 */
	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("%d ", p->data); // 데이터 출력

	printf(">\n");
}

/* 이중 연결 리스트의 노드를 역순으로도 출력하는 함수 */
void display_add_reverse(DlistNode *phead)
{
	DlistNode *p; // phead대신에 사용할 리스트 선언

	printf("< ");
	/* p에 phead의 rlink 대입 p 가 phead와 같아질 때 까지 다음 노드로 이동 */
	for (p = phead->rlink; p != phead; p = p->rlink)
		printf("%d ", p->data);  // 데이터 출력
	printf(">\n");

	printf("< ");
	/* p에 phead의 llink 대입 p 가 phead와 같아질 때 까지 이전 노드로 이동 */
	for (p = phead->llink; p != phead; p = p->llink)
		printf("%d ", p->data); // 데이터 출력
	printf(">\n\n");
}

/* 노드를 동적으로 생성하여 반환하는 함수 */
DlistNode *create_node(element data)
{
	DlistNode *new_node = (DlistNode *)malloc(sizeof(DlistNode));
	// 노드를 동적 할당할 포인터 노드 선언 및 동적 할당

	new_node->data = data; // new_node의 데이터에 data 저장
	new_node->llink = NULL; // new_node의 llink에 NULL 저장
	new_node->rlink = NULL; // new_node의 rlink에 NULL 저장

	return new_node; // new_node 반환
}


/* 노드 new_node를 노드 before의 왼쪽에 삽입하는 함수 */
void dinsert_node(DlistNode *before, DlistNode * new_node)
{
	new_node->rlink = before; // new_node의 rlink에 before 저장
	new_node->llink = before->llink; // new_node의 llink에 before의 llink 저장
	before->llink->rlink = new_node; // before의 llink의 rlink에 new_node 저장
	before->llink = new_node; // before의 llink에 new_node 저장
}

/* 리스트에서 key값에 해당하는 데이터를 삭제하는 함수 */
void delete_node(DlistNode *phead, int key)
{
	int check = 1; // 반복 조건을 체크하기 위한 변수 선언 및 초기화

	/* check가 0이 될 때까지 반복 */
	while (check)
	{
		check = 0; // check에 0저장
		DlistNode *temp = phead; // temp에 phead저장
		DlistNode *f = NULL; // f에 NULL저장

		/* phead의 데이터가 key값과 같다면 */
		if (phead->data == key)
		{
			/* phead의 rlink가 NULL일 경우 */
			if (phead->rlink != NULL)
			{
				phead = phead->rlink; // phead의 phead의 rlink 저장
				phead->llink = NULL; // phead의  llink에 NULL 저장
			}

			/* phead의 rlink가 NULL이 아닐 경우*/
			else
				phead = NULL; // phead에 NULL 저장

			free(temp); // temp 노드의 메모리 할당 해제
			check = 1; // 데이터가 삭제되었으므로 check에 1저장
		}

		/* temp의 rlink가 phead이면 반복 종료 */
		while (temp->rlink != phead)
		{
			/* temp의 rlink의 데이터가 key값과 같다면 */
			if (temp->rlink->data == key)
			{
				f = temp->rlink; // f에 temp의 rlink 저장

				temp->rlink = temp->rlink->rlink;
				// temp의 rlink에 temp의 rlink의 rlink 저장
				temp->rlink->llink = temp;
				// temp의 rlink의 llink에 temp 저장

				free(f); // f 노드의 메모리 할당 해제
				check = 1; // 데이터가 삭제 되었으므르 check에 1저장
			}
			temp = temp->rlink; // temp를 다음 노드로 이동
		}
	}
}

int main() // 메인 함수 시작
{
	int data, input;
	// 데이터를 임시로 저장할 변수, 사용자에게 값을 입력 받을 변수 선언
	DlistNode list;
	// 이중 연결 리스트 구조체 list 선언

	/* 파일포인터 fp 선언 및 data3.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data3.txt", "r");

	/* 파일을 여는데 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 에러메세지 출력
		return 0; // 메인 함수 종료
	}

	init(&list); // init함수로 list를 초기화

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fscanf(fp, "%d", &data);
		// fp의 정수형 데이터를 data에 저장
		dinsert_node(&list, create_node(data));
		// 저장한 data를 create_node함수로 노드를 생성한 후 dinsert_node함수로 list노드에 삽입
	}

	display(&list); // display함수로 리스트의 데이터 출력

	do
	{
		printf("지울 값을 입력하세요(0 : 종료) : ");
		scanf("%d", &input); // 사용자에게 입력값을 받는다.

		/* 사용자의 입력값이 0이면 */
		if (input == 0)
			break; // 반복문 종료

		delete_node(&list, input);
		// delete_node함수로 리스트의 input과 같은 데이터를 삭제
		display_add_reverse(&list);
		// display_add_reverse함수로 리스트의 데이터를 출력

	} while (TRUE); // 무한 루프

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
