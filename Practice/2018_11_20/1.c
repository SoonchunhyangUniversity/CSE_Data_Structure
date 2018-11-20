/**
 * 작성자 : 김민수
 * 학번 : 20174444
 * 학과 : 컴퓨터소프트웨어공학과
 * 프로그램명 : Floyd의 최단 경로 알고리즘
 * 작성일 : 2018-11-20
 */

#include <stdio.h> // 표준 입출력 라이브러리 헤더파일 선언
#include <stdlib.h> // 동적 할당 함수를 사용하기 위한 헤더파일 선언
#define TRUE 1 // 기호 상수 TRUE를 1로 정의
#define FALSE 0 // 기호 상수 FALSE를 0으로 정의
#define INF 1000L // 기호 상수 INF를 1000L로 정의

/* 최소 비용 행렬을 초기화하는 함수 */
void matrix_init(int **adj_mat, int max);
/* Floyd 알고리즘의 최소 비용 행렬을 출력하는 함수 */
void display(int **adj_mat, int **update_mat, int max);
/* Floyd의 최소 비용 신장 트리 함수 */
void floyd(int **adj_mat, int max);

int main()
{
	int **adj_mat;
    // 인접 행렬을 동적 할당 할 이중 포인터 변수 선언
	int i, j;
    // 반복문에서 사용 할 변수
	int u, v, weight;
    // 정점의 정보와 가중치를 저장할 변수 선언
	int max = INT_MIN;
    // 정점의 최대 번호를 저장 할 변수 선언 및 초기화

	char c;
    // 연산자를 저장 할 변수 선언

	/* 파일 fp 선언 및 data1.txt를 읽기모드로 연다. */
	FILE *fp = fopen("data1.txt", "r");

	/* 파일을 여는데에 실패했을 경우 예외처리 */
	if (fp == NULL)
	{
		puts("FILE OPEN ERROR!");
        // 에러 메세지 출력
		return 0;
        // 메인 함수 종료
	}

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c", &c);
        // 파일 fp에서 문자 하나를 읽어와 c에 저장

        /* c가 'v'일 경우 */
		if (c == 'v')
		{
			fscanf(fp, " %d", &u);
            // 파일에서 정수형 데이터를 하나 읽어와 u에 저장

            /* 정점의 최대 번호 갱신 */
			if (max < u)
				max = u;
		}

        /* c가 'v'가 아닐 경우 */
		else
		{
			break;
            // 반복문 탈출
		}
	}

    /* (max + 1) X (max + 1) 2차원 배열 동적 할당 */
	adj_mat = (int **)malloc(sizeof(int *) * (max + 1));

	for (i = 0; i <= max; i++)
		adj_mat[i] = (int *)malloc(sizeof(int) * (max + 1));

	matrix_init(adj_mat, max);
    // matrix_init 함수 호출로 행렬 초기화

	rewind(fp);
    // 파일 포인터의 위치를 처음으로 돌린다.

    /* 파일의 끝까지 반복하는 반복문 */
	while (!feof(fp))
	{
		fscanf(fp, " %c %d", &c, &u);
        // 파일 fp에서 문자 하나를 읽어와 c에 저장

        /* c가 'v'일 경우 */
		if (c == 'v')
		{
			continue;
            // 다음 반복문으로 이동
		}

        /* c가 'v'가 아닐 경우 -> 'e'일 경우 */
		else if (c == 'e')
		{
			fscanf(fp, "  %d %d", &v, &weight);
            // 파일에서 정수형 데이터 세개를 읽어와 저장

			adj_mat[u][v] = weight;
			adj_mat[v][u] = weight;
            // 인접 행렬에 가중치 삽입
		}

        /* 잘못된 연산자일 경우 */
        else
        {
            printf("> %c < OPERATION ERROR!", c);
            // 에러 메세지 출력
            return 0;
            // 메인 함수 종료
        }
	}

	floyd(adj_mat, max);
    // floyd 함수 호출로 Floyd 알고리즘 실행

	fclose(fp);
    // 열어준 파일 포인터 fp를 닫는다.

    /* 동적 할당한 2차원 배열 메모리 할당 해제 */
	for (i = 0; i <= max; i++)
		free(adj_mat[i]);

	free(adj_mat);

	return 0;
    // 메인 함수 종료
}

/**
 * [matrix_init 함수]
 * @param adj_mat [인접 행렬]
 * @param max     [최대 정점 번호]
 */
void matrix_init(int **adj_mat, int max)
{
	int i, j;
    // 반복문에서 사용 할 변수 선언

    /* 행의 크기만큼 반복하는 반복문 */
	for (i = 0; i <= max; i++)
	{
        /* 열의 크기만큼 반복하는 반복문 */
		for (j = 0; j <= max; j++)
		{
            /* 행렬의 번호가 같은 경우 예) (0,0) (1,1) 등 */
			if (i == j)
				adj_mat[i][j] = 0;
                // 0으로 초기화

            /* 그렇지 않은 경우 */
			else
				adj_mat[i][j] = INF;
                // INF로 초기화
		}
	}
}

/**
 * [display description]
 * @param adj_mat    [인접 행렬]
 * @param update_mat [최소 비용이 갱신된 행렬]
 * @param max        [최대 정점 번호]
 */
void display(int **adj_mat, int **update_mat, int max)
{
	int i, j;
    // 반복문에서 사용 할 변수 선언

    printf(" ");

    /* 열 변호 출력 */
	for (i = 0; i <= max; i++)
		printf("%4d", i);

	printf("\n |");

    /* 상단 바 출력 */
	for (i = 0; i <= max; i++)
	{
		if (i != max)
			printf("----");

		else
			printf("---|\n");
	}

    /* 행의 크기만큼 반복하는 반복문 */
	for (i = 0; i <= max; i++)
	{
		printf("%d", i);
        // 행 번호 출력

        /* 열의 크기만큼 반복하는 반복문 */
		for (j = 0; j <= max; j++)
		{
            /* 연결되지 않은 경로일 경우 */
			if (adj_mat[i][j] == INF)
				printf("|%3c", 'x');
                // x 출력

            /* 연결된 경로일 경우 */
			else
			{
                /* 최소 비용이 갱신된 경우 */
				if (update_mat[i][j] != adj_mat[i][j])
					printf("|*%2d", adj_mat[i][j]);
                    // 갱신된 상태를 *로 표현하여 출력

                /* 이전 비용과 같을 경우 */
				else
					printf("|%3d", adj_mat[i][j]);
                    // 비용 출력
			}
		}
		printf("|\n");
	}

	printf(" |");

    /* 하단 바 출력 */
	for (i = 0; i <= max; i++)
	{
		if (i != max)
			printf("----");

		else
			printf("---|\n\n");
	}
}

/**
 * [floyd 함수]
 * @param adj_mat [초기 인접 행렬]
 * @param max     [최대 정점 번호]
 */
void floyd(int **adj_mat, int max)
{
	int i, j, k;
    // 반복문에서 사용 할 변수 선언

    /* 최소 비용 갱신 행렬 선언 및 인접 행렬과 같은 크기 동적 할당 */
	int **update_mat = (int **)malloc(sizeof(int *) * (max + 1));

	for (i = 0; i <= max; i++)
		update_mat[i] = (int *)malloc(sizeof(int) * (max + 1));

    /* 최소 비용 갱신 행렬 초기화 */
	for (i = 0; i <= max; i++)
	{
		for (j = 0; j <= max; j++)
			update_mat[i][j] = INT_MIN;
	}

	puts("< 초기 상태 >");
	display(adj_mat,  update_mat, max);
    // display 함수 호출로 초기 최소 비용 갱신 행렬 출력

    /* 인접 행렬의 데이터 최소 비용 갱신 행렬로 복사 */
	for (i = 0; i <= max; i++)
	{
		for (j = 0; j <= max; j++)
		{
			update_mat[i][j] = adj_mat[i][j];
		}
	}

    /* Floyd 알고리즘 진행 */
	for (k = 0; k <= max; k++)
	{
		for (i = 0; i <= max; i++)
		{
			for (j = 0; j <= max; j++)
			{
                /* 최소 비용을 찾을 경우 최소 비용 갱신 */
				if (update_mat[i][k] + update_mat[k][j] < update_mat[i][j])
					update_mat[i][j] = update_mat[i][k] + update_mat[k][j];
			}
		}

		printf("< %d번 정점 열림 >\n", k);
		display(update_mat, adj_mat, max);
        // display 함수 호출로 현재 최소 비용 행렬 출력

        /* 마지막 정점까지 확인했을 경우 */
        if (k == max)
            break;
            // 인접 행렬을 업데이트 할 필요 없으므로 반복문 탈출

        /* 현재의 최소 비용 행렬을 저장 */
		for (i = 0; i <= max; i++)
		{
			for (j = 0; j <= max; j++)
			{
				adj_mat[i][j] = update_mat[i][j];
			}
		}
	}
}
