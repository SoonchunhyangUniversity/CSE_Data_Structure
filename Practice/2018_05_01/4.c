#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 사용을 위한 헤더파일 선언

typedef int element; // element 키워드로 int형 정수 선언 가능

/* 학생의 데이터를 저장하는 구조체 */
typedef struct _std
{
	element std_num; // 학번
	element kor; // 국어 점수
	element eng; // 영어 점수
	element mat; // 수학 점수
	element sum; // 총점
	double avg; // 평균
} Student; // Student 키워드로 선언 가능

/* 연결리스트의 노드 구조체 */
typedef struct ListNode
{
	Student std; // 학생 데이터
	struct ListNode *link; // 다음 노드를 가리키는 포인터 구조체
} ListNode; // ListNode 키워드로 선언 가능

/* 에러 출력 함수 */
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
		new_node->link = NULL; // new_node의 다음 노드를 NULL로 대입
		*phead = new_node; // *phead에 new_node를 대입
	}

	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead; // new_node의 다음 노드를 *phead로 대입
		*phead = new_node; // *phead에 new_node 대입
	}

	else // 둘 다 아니면
	{
		new_node->link = p->link; // new_node의 다음 노드에 p의 다음 노드 대입
		p->link = new_node; // p의 다음 노드에 new_node 대입
	}
}

/* 리스트를 출력하는 함수 */
void display(ListNode *head)
{
	ListNode *p = head; // 헤드 대신에 사용할 포인터 노드 p 선언

	printf("학번\t 국어\t 영어\t 수학\t 총점\t 평균\n");

	/* p가 NULL일 때 까지 반복 */
	while (p != NULL)
	{
		printf("%8d %6d %6d %6d %6d %8.2lf\n", p->std.std_num, p->std.kor, p->std.eng, p->std.mat, p->std.sum, p->std.avg);
		// 데이터 출력
		p = p->link; // p를 다음 노드로 이동
	}
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(element std_num, element kor, element eng, element mat, ListNode *link)
{
	ListNode *new_node; // 데이터를 담을 노드 선언
	new_node = (ListNode *)malloc(sizeof(ListNode)); // 노드의 동적 할당

	/* 동적 할당에 실패 했을 경우 */
	if (new_node == NULL)
		error("메모리 할당 에러"); // 예외 처리

	/* 매개변수로 받은 데이터를 노드에 대입 */
	new_node->std.std_num = std_num;
	new_node->std.kor = kor;
	new_node->std.eng = eng;
	new_node->std.mat = mat;

	/* 받은 데이터를 기반으로 계산해 데이터 대입 */
	new_node->std.sum = kor + eng + mat;
	new_node->std.avg = new_node->std.sum / 3.0;

	/* new_node 다음 노드에 link 대입*/
	new_node->link = link;

	return (new_node); // 동적 할당 후 데이터를 담은 노드 반환
}

/* 데이터를 교환하는 함수 */
void swap(ListNode *a, ListNode *b)
{
	Student temp = a->std;
	// 구조체를 임시로 담을 변수 선언 및 a의 std구조체 대입
	a->std = b->std;
	// a의 std구조체에 b의 std구조체 대입
	b->std = temp;
	// b의 std구조체에 temp 구조체 대입
}

/* 데이터를 정렬하는 함수 */
void sort(ListNode *phead)
{
	int check = 1; // 반복 조건을 체크하는 변수 선언 및 초기화
	ListNode *current; // 현재 노드를 가리킬 포인터 노드
	ListNode *follow = NULL; // 선행 노드를 가리킬 포인터 노드

	/* 데이터가 존재하지 않으면 */
	if (phead == NULL)
		return; // 함수 종료

	/* check가 0이 될 때 까지 반복 */
	while (check)
	{
		check = 0; // check에  0 대입
		current = phead; // node에 phead 대입

		/* 현재 노드의 다음 노드가 선행노드와 같지않으면 반복 */
		while (current->link != follow)
		{
			/* 현재 노드의 데이터가 선행 노드의 데이터 보다 크다면 */
			if (current->std.sum < current->link->std.sum)
			{
				swap(current, current->link); // 데이터의 교환
				check = 1; // check에 1 대입
			}

			current = current->link; // 다음 노드로 이동
		}

		follow = current; // 선행 노드에 현재 노드 대입
	}
}

int main() // 메인 함수 시작
{
	ListNode *list = NULL; // 헤드 노드 포인터 선언 및 초기화
	char temp[100]; // 임시로 한 줄을 통째로 받을 문자 배열 선언
	int std_count = 0, i; // 학생의 수와 반복문에서 사용할 변수 선언
	int std_num_temp, kor_temp, eng_temp, mat_temp; // 학생의 데이터를 임시로 담을 변수 선언

	/* 파일포인터 fp 선언 및 data4.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data4.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR\n");
		return 0; // 예외 처리
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fgets(temp, 100, fp);
		// fp의 한줄을 temp에 저장
		std_count++;
		// 학생의 숫자를 1 더한다
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 돌림

	/* 학생의 수 만큼 반복 */
	for (i = 0; i < std_count; i++)
	{
		fscanf(fp, "%d %d %d %d", &std_num_temp, &kor_temp, &eng_temp, &mat_temp);
		// 파일에서 데이터를 읽어서 가져온후 임시로 저장
		insert_node(&list, NULL, create_node(std_num_temp, kor_temp, eng_temp, mat_temp, NULL));
		// 임시로 저장한 데이터를 노드에 대입하여 리스트에 연결
	}

	printf("Before Sorting!!\n");
	display(list); // 노드 정렬 전 데이터 출력

	printf("\n\n");

	sort(list); // 정렬 진행

	printf("After Sorting!!\n");
	display(list); // 정렬 후 데이터 출력

	fclose(fp); // 열어준 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
