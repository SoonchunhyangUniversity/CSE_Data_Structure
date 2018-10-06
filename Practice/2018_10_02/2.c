/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : 손님 관리 프로그램
 * 작성일 : 2018-10-02
 */

 #include <stdio.h> // 표준입출력 라이브러리 헤더파일 선언
 #define MAX 200 // 기호상수 MAX를 200으로 정의

 /* 히프의 데이터 element 구조체 */
 typedef struct
 {
 	int key; // 정수형 우선순위 필드
 	char name[MAX]; // 문자열 이름 필드
 } element; // element 키워드 선언 가능

 /* 히프 구조체 */
 typedef struct
 {
 	element heap[MAX]; // MAX사이즈의 element 구조체 배열 필드
 	int heap_size; // 히프의 크기를 저장하는 정수 필수
 } HeapType; // HeapType 키워드 선언 가능

/* 최소힙에 데이터를 삽입하는 함수 */
void insert_min_heap(HeapType *h, element item);
/* 힙의 데이터를 출력하는 함수 */
void display(HeapType *h, int idx);
/* 힙을 초기화하는 함수 */
void init(HeapType *h);
/* 힙의 데이터를 삭제하는 함수 */
element delete_min_heap(HeapType *h);

int main()
{
	char oper;
	// 연산자를 저장할 변수 선언
	int key = 0;
	// 우선순위를 저장할 변수 선언 및 초기화
	element temp;
	// 데이터를 임시로 저장할 변수 선언 및 초기화
	HeapType heap;
	// 힙 구조체 선언

	/* 파일포인터 fp 선언 및 data2.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data2.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	init(&heap); // init 함수로 힙 초기화

	/* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
        oper = 'n';
        // oper 변수 초기화
		fscanf(fp, " %c", &oper);
		// 파일 fp에서 문자 하나를 읽어와 oper에 대입

		/* oper가 'i'일 경우 */
		if (oper == 'i')
		{
			fscanf(fp, "%s", temp.name);
			// 파일 fp에서 문자열을 읽어와 temp의 name필드에 저장
			temp.key = ++key;
			// temp의 키값에 1 증가한 key값 대입

			insert_min_heap(&heap, temp);
			// insert_min_heap 함수를 사용해 힙에 데이터 삽입

			printf(">> 손님(%s) 입장\n", temp.name);
			// 삽입된 데이터 출력
			printf("< 히프 중위 순회 출력 >\n");
			display(&heap, 1);
			// display 함수를 사용하여 힙 중위 순회 출력
			printf("\n");
		}

		/* oper가 'o'일 경우 */
		else if (oper == 'o')
		{
			temp = delete_min_heap(&heap);
			// delete_min_heap 으로 힙의 데이터 삭제 후 temp에 대입
			key--;
			// key값 1 감소

			printf(">> 손님(%s) 퇴장\n", temp.name);
			// 삭제된 데이터 출력
			printf("< 히프 중위 순회 출력 >\n");
			display(&heap, 1);
			// display 함수를 사용하여 힙 중위 순회 출력
			printf("\n");
		}

		/* 잘못된 연산자일 경우 예외처리 */
		else
		{
			return 0;
		}
	}

	fclose(fp); // 열어준 파일포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}

/**
 * [insert_min_heap 함수]
 * @param h    [힙 구조체]
 * @param item [삽입될 데이터]
 */
void insert_min_heap(HeapType *h, element item)
{
	int i;
	// 반복문에 사용될 변수 선언
	i = ++(h->heap_size);
	// i 변수에 h의 heap_size를 1더한값 대입

	/* i가 1이되거나 item의 key값이 클경우 반복문 탈출 */
	while ((i != 1) && (item.key < h->heap[i / 2].key))
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
		// i를 2로 나누면서 힙의 상단으로 이동
	}

	h->heap[i] = item; // 힙의 i번째 배열에 item 데이터 삽입
}

/**
 * [display 함수]
 * @param h   [힙 구조체]
 * @param idx [탐색할 노드 인덱스]
 */
void display(HeapType *h, int idx)
{
	/* 탐색중인 노드의 인덱스가 힙의 크기보다 클 경우 */
	if (idx > h->heap_size)
		return; // 함수 종료

	display(h, 2 * idx);
	// 왼쪽 노드로 이동하여 재귀
	printf("%d - %s\n", h->heap[idx].key, h->heap[idx].name);
	// 노드의 데이터 출력
	display(h, 2 * idx + 1);
	// 오른쪽 노드로 이동하여 재귀

	/* 배열 기반 트리로 구현된 힙
				  1
			2			3
		4		5	6		7
		인덱스가 1부터 시작
		왼쪽 노드는 2 * idx
		오른쪽 노드는 2 * idx + 1 */
}

/**
 * [init 함수]
 * @param h [힙 구조체]
 */
void init(HeapType *h)
{
	h->heap_size = 0; // 힙의 사이즈를 0으로 초기화
}

/**
 * [delete_min_heap 함수]
 * @param  h [힙 구조체]
 * @return   [힙의 최솟값]
 */
element delete_min_heap(HeapType *h)
{
	int parent, child;
	// 힙의 부모노드와 자식노드 인덱스 변수 선언
	element item, temp;
	// 삭제될 데이터를 저장할 변수와 임시로 데이터를 저장할 변수 선언

	item = h->heap[1];
	// 삭제될 데이터에 힙의 최댓값 item에 저장
	temp = h->heap[(h->heap_size)--];
	// 힙의 가장 작은 데이터 temp에 저장
	parent = 1, child = 2;
	// 부모, 자식노드 인덱스값 초기화

	/* 자식노드 인덱스가 힙의 사이즈보다 크면 탈출하는 반복문 */
	while (child <= h->heap_size)
	{
		/* child의 인덱스가 힙 사이즈보다 작고
			오른쪽 자식 노드의 작을값이 클 경우*/
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++; // child 값 1 증가

		/* temp의 key값이 자식노드의 키값보다 작거나 같은 경우 */
		if (temp.key <= h->heap[child].key)
			break; // 반복문 탈출

		h->heap[parent] = h->heap[child];
		// 부모노드에 자식노드 대입
		parent = child;
		// 자식노드의 인덱스를 부모노드에 대입
		child *= 2;
		// 자식노드를 2 곱해준다.
	}

	h->heap[parent] = temp;
	// 반복이 끝난 부모노드에 temp 대입

	/* 데이터가 삭제된 후 힙의 모든 데이터에 방문하는 반복문 */
	for(int i = h->heap_size; i > 0; i--)
		h->heap[i].key--; // 키값을 1 감소

	return item; // 삭제된 데이터 반환
}
