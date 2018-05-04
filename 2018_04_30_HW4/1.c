/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 04 과제
	* 개발환경 : Visual Studio 2010
	* 컴파일러 표준 : C99
	* 작성일 : 2018 - 04 - 30
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 함수 선언
#include <stdlib.h> // malloc함수와 free함수 사용을 위한 헤더파일 선언

/* 연결리스트의 노드 구조체 */
typedef struct _node
{
	int coef; // 계수
	int expon; // 지수
	struct _node *link; // 다음 노드를 가리키는 구조체 포인터 변수
} Node; // ListNode 키워드로 선언 가능

/* 연결리스트의 헤드 구조체 */
typedef struct _header
{
	int length; // 연결리스트의 데이터 개수
	Node *head;
	Node *tail;
} Header; // ListHeader 키워드로 선언 가능

/* 연결리스트의 초기화 함수 */
void init(Header *plist)
{
	// 연결리스트의 데이터 개수를 0으로 초기화
	plist->length = 0;
	// 헤더의 tail이 NULL을 head가 tail을 가리키도록 초기화
	plist->head = plist->tail = NULL;
}

/* 연결리스트의 삽입 함수 */
void Insert_Node(Header *plist, int coef, int expon)
{
	// 데이터를 저장할 노드를 동적 할당
	Node *new_node = (Node *)malloc(sizeof(Node));

	/* 동적 할당에 실패했을 경우 */
	if (new_node == NULL)
	{
		printf("MEMORY ALLOCATION ERROR!\n");
		return 0; // 예외 처리
	}

	new_node->coef = coef; // 파라미터로 받은 계수를 노드에 대입
	new_node->expon = expon; // 파라미터로 받은 지수를 노드에 대입
	new_node->link = NULL; // 노드의 다음 리스트를 NULL로 대입

	/* 헤더 노드에 아무것도 연결되지 않았을 때 */
	if (plist->tail == NULL)
	{
		plist->head = plist->tail = new_node;
		// 헤더의 head와 tail을 new_node로 대입
	}

	/* 헤더 노드에 연결된 노드가 있을 때 */
	else
	{
		plist->tail->link = new_node; // tail의 다음 노드를 new_node로 대입
		plist->tail = new_node; // 헤더의 tail을 new_node로 대입
	}

	plist->length++; // 데이터 개수 + 1
}

/* 곱셈을 해서 새로운 리스트에 삽입하는 함수 */
void insert_node_multiply(Header *plist, int coef, int expon)
{
	Node *p = plist->head; // 헤더의 head를 대신해 사용할 p 선언 및 대입
	Node *prev = NULL; // 선행 노드 선언 및 초기화

	/* 헤더의 tail에 연결된 것이 없다면 */
	if (plist->tail == NULL)
	{
		Insert_Node(plist, coef, expon);
		// Insert_Node함수로 데이터 저장
		return; // 함수 종료
	}

	/* p가 NULL일 때 까지 반복 */
	while (p)
	{
		/* p의 차수와 삽입 할 차수가 같다면 */
		if (p->expon == expon)
		{
			p->coef += coef; // 계수를 더해준다.
			return; // 함수 종료
		}

		/* p의 차수가 삽입 차수보다 작다면 */
		else if (p->expon < expon)
		{
			// 데이터를 저장할 노드를 동적 할당
			Node *new_node = (Node *)malloc(sizeof(Node));

			/* 동적 할당에 실패했을 경우 */
			if (new_node == NULL)
			{
				printf("MEMORY ALLOCATION ERROR!\n");
				return; // 예외 처리
			}

			new_node->coef = coef; // 새로운 노드의 계수를 입력받은 계수로 대입
			new_node->expon = expon; // 새로운 노드의 차수를 입력받은 차수로 대입
			new_node->link = p; // 새 노드의 다음 노드를 p로 대입
			prev->link = new_node; // 선행 노드의 다음 노드를 새 노드로 대입

			plist->length++; // 데이터의 개수 + 1

			return; // 함수 종료
		}

		/* p의 다음 노드가 없다면 */
		if (p->link == NULL)
		{
			Insert_Node(plist, coef, expon);
			// Insert_Node 함수로 데이터 저장
			return; // 함수 종료
		}

		prev = p; // 선행노드를 p로 대입
		p = p->link; // p를 p 다음 노드로 이동
	}
}

/* 다항식의 곱셉을 하는 함수 */
void poly_mul(Header *plist1, Header *plist2, Header *plist3)
{
	Node *a = plist1->head; // a에 리스트1의 헤더를 대입
	Node *b = plist2->head; // b에 리스트2의 헤더를 대입

	int multiply; // 계수의 곱
	int expon; // 지수의 값

	/* a가 NULL일 때 까지 반복 */
	while (a)
	{
		/* b가 NULL일 때 까지 반복 */
		while (b)
		{
			multiply = a->coef * b->coef; // 계수의 곱은 두 계수의 곱
			expon = a->expon + b->expon; // 지수의 곱은 두 지수의 합
			insert_node_multiply(plist3, multiply, expon);
			// insert_node_multiply 함수로 리스트3에 데이터 삽입
 			b = b->link; // b를 다음 노드로 이동
		}

		a = a->link; // a를 다음 노드로 이동
		b = plist2->head; // b를 b의 첫번째 노드로 이동
	}
}

/* 다항식을 출력하는 함수 */
void poly_print(Header *plist)
{
	Node *p = plist->head; // p에 리스트의 헤드를 대입

	for (; p; p = p->link) // p가 NULL일 때 까지 반복
	{
		// 마지막 노드일 경우
		if(p->link == NULL)
			printf("(%dx^%d)", p->coef, p->expon); // +를 붙이지 않고 출력
		// 마지막 노드가 아닐 경우
		else
			printf("(%dx^%d) + ", p->coef, p->expon); // +를 붙여서 출력
	}

	printf("\n"); // 하나의 다항식 출력이 끝나면 개행
}

int main()
{
	Header list1, list2, list3;
	// 다항식을 저장할 2개의 리스트와 곱을 저장할 리스트 1개 선언

	int poly1_count = 0, poly2_count = 0;
	// 다항식1의 항의 개수를 저장할 변수와, 다항식2의 항의 개수를 저장할 변수 선언 및 초기화
	int i, check = 0;
	// 반복문에서 사용할 변수와, 몇 번째 다항식의 데이터인지 체크 하는 변수 선언
	int coef, expon;
	// 파일에서 차수와 계수를 받아 임시로 저장할 변수 선언
	char temp[100];
	// 파일에서 다항식1, 다항식2 를 구분할 문자열을 받을 문자열 선언

	/* 파일 포인터 fp 선언 및 data1.txt를 읽기모드로 연다 */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0; // 예외 처리
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fgets(temp, 100, fp);
		// 파일의 한줄을 통째로 받아서 temp에 저장

		i = 0; // 인덱스 값을 가리킬 변수 초기화

		/* 한 줄을 통째로 받은 것에서 공백문자가 나올 때 까지 반복 */
		while (temp[i] != '\n')
		{
			/* 다항식1에 관한 데이터이면 */
			if (check == 0)
			{
				/* 공백 문자가 나오면 */
				if (temp[i] == ' ')
					poly1_count++; // 다항식1의 항의 개수 + 1
			}

			/* 다항식2에 관한 데이터이면 */
			else
			{
				/* 공백 문자가 나오면 */
				if (temp[i] == ' ')
					poly2_count++; // 다항식2의 항의 개수 + 1
			}

			i++; // 다음 인덱스를 가리키도록 + 1
		}
		check = 1; // 한 줄을 모두 판별
	}

	/*
		다항식의 데이터는 차수, 계수 두개로 이루어져
		공백 문자가 2개씩 입력되므로, 나누기 2를 해주면,
		다항식의 개수를 얻을 수 있다.
	*/
	poly1_count /= 2;
	poly2_count /= 2;

	rewind(fp); // 파일 포인터의 위치를 처음으로 되돌린다.

	/* 데이터를 저장할 리스트의 초기화 */
	init(&list1);
	init(&list2);
	init(&list3);

	fscanf(fp, "%s", temp); // poly1 문자열 읽기

	/* poly1의 항의 개수 만큼 반복 */
	for (i = 0; i < poly1_count; i++)
	{
		// 계수, 지수 데이터 읽기
		fscanf(fp, "%d %d", &coef, &expon);
		// 읽어온 데이터를 연결리스트에 저장
		Insert_Node(&list1, coef, expon);
	}

	fread(temp, 1, 1, fp); // '\n' 읽기

	fscanf(fp, "%s", temp); // poly2 문자열 읽기

	/* poly2의 항의 개수 만큼 반복 */
	for (i = 0; i < poly2_count; i++)
	{
		// 계수, 지수 데이터 읽기
		fscanf(fp, "%d %d", &coef, &expon);
		// 읽어온 데이터를 연결리스트에 저장
		Insert_Node(&list2, coef, expon);
	}

	/* list1과 list2의 다항식 곱셈 결과를 list3에 저장 */
	poly_mul(&list1, &list2, &list3);
	/* list1을 출력 */
	poly_print(&list1);
	/* list2를 출력 */
	poly_print(&list2);
	/* list3을 출력 */
	poly_print(&list3);

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
