/*
	*
	* 작성자 : 김민수
	* 학번 : 20174444
	* 학과 : 컴퓨터소프트웨어공학과
	* 프로그램명 : 연결 리스트
	* 작성일 : 2018 - 05 - 15
	*
*/

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // malloc, free 함수 사용을 위한 헤더파일 선언

/* 학생의 정보를 담는 구조체 */
typedef struct _std
{
	char name[10]; // 이름
	int std_num; // 학번
	int kor; // 국어 성적
	int eng; // 영어 성적
	int mat; // 수학 성적
	int sum; // 총점
	double avg; // 평균
} Student; // typedef로 Student 키워드 사용 가능

/* 연결 리스트의 노드 구조체 */
typedef struct ListNode
{
	Student data; // 학생의 구조체를 데이터로 사용
	struct ListNode *link; // 다음 노드를 가리키는 포인터 노드
} ListNode; // typedef로 ListNode 키워드 사용 가능

/* 에러 메세지를 출력하는 함수 */
void error(char *message)
{
	fprintf(stderr, "%s\n", message); // 에러 메세지 출력
	exit(1); // 프로그램 종료
}

/* 연결리스트의 노드 삽입 함수 */
void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) // 공백 리스트인 경우
	{
		new_node->link = NULL; // new_node의 link를 NULL로 저장
		*phead = new_node; // *phead를 new_node로 저장
	}
	else if (p == NULL) // p가 NULL이면 첫 번째 노드로 삽입
	{
		new_node->link = *phead; // new_node의 link를 *phead로 저장
		*phead = new_node; // *phead를 new_node로 저장
	}
	else // 둘 다 아닐 경우
	{
		new_node->link = p->link; // new_node의 link를 p의 link로 저장
		p->link = new_node; // p의 link를 new_node로 저장
	}
}

/* 총점이 가장 높은 학생의 데이터를 출력하는 함수 */
void display_max_sum(ListNode *head, int max_sum)
{
	ListNode *p = head; // 헤드 포인터 대신 사용할 포인터 노드

	printf("< 총점 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");

	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		/* 저장된 총점의 최댓값과 해당 학생의 값이 같다면 */
		if (max_sum == p->data.sum)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name,
				p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
			// 해당 학생의 데이터 출력
		}
		p = p->link; // 다음 노드로 이동
	}
	printf("│========│========│====│====│====│====│======│\n\n");
}

/* 국어 점수가 가장 높은 학생의 데이터를 출력하는 함수 */
void display_max_kor(ListNode *head, int max_kor)
{
	ListNode *p = head; // 헤드 포인터 대신 사용할 포인터 노드

	printf("< 국어 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");

	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		/* 저장된 국어 점수의 최댓값과 해당 학생의 값이 같다면 */
		if (max_kor == p->data.kor)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name,
				p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
			// 해당 학생의 데이터 출력
		}
		p = p->link; // 다음 노드로 이동
	}
	printf("│========│========│====│====│====│====│======│\n\n");
}

/* 영어점수가 가장 높은 학생의 데이터를 출력하는 함수 */
void display_max_eng(ListNode *head, int max_eng)
{
	ListNode *p = head; // 헤드 포인터 대신 사용할 포인터 노드

	printf("< 영어 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");

	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		/* 저장된 영어 점수의 최댓값과 해당 학생의 값이 같다면 */
		if (max_eng == p->data.eng)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name,
				p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
			// 해당 학생의 데이터 출력
		}
		p = p->link; // 다음 노드로 이동
	}
	printf("│========│========│====│====│====│====│======│\n\n");
}

/* 수학점수가 가장 높은 학생의 데이터를 출력하는 함수 */
void display_max_mat(ListNode *head, int max_mat)
{
	ListNode *p = head; // 헤드 포인터 대신 사용할 포인터 노드

	printf("< 수학 최고점수 >\n");
	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");
	printf("│========│========│====│====│====│====│======│\n");

	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		/* 저장된 수학 점수의 최댓값과 해당 학생의 값이 같다면 */
		if (max_mat == p->data.mat)
		{
			printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name,
				p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);
			// 해당 학생의 데이터 출력
		}
		p = p->link; // 다음 노드로 이동
	}
	printf("│========│========│====│====│====│====│======│\n\n");
}

/* 리스트의 데이터를 출력하는 함수 */
void display(ListNode *head)
{
	ListNode *p = head; // 헤드 포인터 대신에 사용할 포인터 노드
	int max_sum = 0, max_kor = 0, max_eng = 0, max_mat = 0;
	// 각 데이터들의 최댓값을 저장할 변수 선언 및 초기화

	printf("│========│========│====│====│====│====│======│\n");
	printf("│  학번  │  이름  │국어│영어│수학│총점│ 평균 │\n");;
	printf("│========│========│====│====│====│====│======│\n");

	/* 리스트의 끝까지 반복 */
	while (p != NULL)
	{
		/* 리스트안의 모든 데이터들을 출력 */
		printf("│%8d│%8s│%4d│%4d│%4d│%4d│%6.2f│\n", p->data.std_num, p->data.name,
			p->data.kor, p->data.eng, p->data.mat, p->data.sum, p->data.avg);

		/* 현재 값이 최댓값보다 큰 값이라면 최댓값 갱신 */
		if (max_sum < p->data.sum)
			max_sum = p->data.sum; // 총점 최댓값 갱신

		if (max_kor < p->data.kor)
			max_kor = p->data.kor; // 국어 점수 최댓값 갱신

		if (max_eng < p->data.eng)
			max_eng = p->data.eng; // 영어 점수 최댓값 갱신

		if (max_mat < p->data.mat)
			max_mat = p->data.mat; // 수학 점수 최댓값 갱신

		p = p->link; // 다음 노드로 이동
	}
	printf("│========│========│====│====│====│====│======│\n\n");

	/* 각 항목별 display_max함수를 사용해 데이터 출력 */
	display_max_sum(head, max_sum);
	display_max_kor(head, max_kor);
	display_max_eng(head, max_eng);
	display_max_mat(head, max_mat);
}

/* 노드를 동적으로 생성하는 프로그램 */
ListNode *create_node(Student data, ListNode *link)
{
	ListNode *new_node; // 동적 할당할 포인터 노드 선언
	new_node = (ListNode *)malloc(sizeof(ListNode)); // malloc함수로 동적 할당

	/* 동적 할당에 실패했을 경우 */
	if (new_node == NULL)
		error("메모리 할당 에러"); // 예외처리

	new_node->data = data; // new_node의 data에 data 저장
	new_node->link = link; // new_node의 link에 link 저장

	return (new_node); // 동적 할당 후 데이터 저장한 노드 반환
}

int main() // 메인 함수 시작
{
	ListNode *list = NULL; // 리스트의 선언 및 초기화
	int std_num = 0; // 학생의 수를 저장할 변수 선언 및 초기화
	int i; // 반복문에서 사용할 변수 선언
	char line_temp[100]; // 한 줄을 통째로 받기위한 문자열 선언
	Student temp; // 데이터를 임시로 저장할 구조체 변수 선언

	/* 파일포인터 fp 선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데 실패했을 경우 */
	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n"); // 예외처리
		return 0;
	}

	/* 파일의 끝까지 반복 */
	while (!feof(fp))
	{
		fgets(line_temp, 100, fp); // 한 줄을 읽어온다.
		std_num++; // 학생의 수를 하나씩 더해준다.
	}

	rewind(fp); // 파일 포인터의 위치를 처음으로 옮긴다.

	/* 학생의 수만큼 반복 */
	for (i = 0; i < std_num; i++)
	{
		fscanf(fp, "%d %s %d %d %d", &temp.std_num, temp.name, &temp.kor, &temp.eng, &temp.mat);
		// 파일에서 데이터를 가져와 temp 구조체에 저장
		temp.sum = (temp.kor + temp.eng + temp.mat);
		// 가져온 점수로 총점 계산 후 구조체에 저장
		temp.avg = (double)temp.sum / 3;
		// 계산한 총점으로 평균을 구한 후 구조체에 저장
		insert_node(&list, NULL, create_node(temp, NULL));
		// 정보가 담긴 temp구조체를 data로 노드를 만들어 insert_node함수로 list에 삽입
	}

	display(list); // display함수로 list의 정보 출력

	fclose(fp); // 파일 포인터 fp를 닫아준다.

	return 0; // 메인 함수 종료
}
