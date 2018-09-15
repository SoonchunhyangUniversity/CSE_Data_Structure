#include <stdio.h>
#include <stdlib.h>


int main(void)
{

	FILE *fp;	// 파일포인터 변수선언
	int m_row = 0, m_col = 3;  // 행렬의 크기를 0으로 초기화
	int **matrix;
	int temp1, temp2, temp3;
	int i,j;

	fp = fopen("data.txt", "r");	// data.txt파일을 읽기모드로 열어 생성된 FILE구조체를 fp에 할당
	if(fp==NULL)	// 만약 fopen함수에서 에러가 발생하여 fp에 NULL값이 저장되었다면 파일열기실패
	{
		printf("파일에 열리지 않았습니다.\n");
		return 0;	// 메세지 출력하고 프로그램 종료
	}

	// 행렬의 크기를 계산함
	while(!feof(fp))
	{
		fscanf(fp, "%d%d%d", &temp1, &temp2, &temp3);
		m_row++;
	}

	// Dynamic 배열의 크기에 따른 할당
	matrix = (int**) malloc(sizeof(int *) * m_row);
	for(i = 0; i < m_row; i++)
	{
		matrix[i] = (int*) malloc(sizeof(int ) * m_col);
	}
	rewind(fp);

	// 파일에서 읽어온 행렬의 크기를 가지고 그만큼의 행렬 내용을 읽어 옴
	for(i = 0; i < m_row; i++)  // 행을 증가 시킴
	{
		for(j = 0; j < m_col; j++) // 열을 증가 시킴
		{
			fscanf(fp, "%d", &matrix[i][j]);  // 행열의 값을 파일에서 하나씩 읽어옴
		}
	}
	fclose(fp);

	printf("=== 입력된 행렬 ===\n");
	for(i = 0; i < m_row; i++)  // 행을 증가 시킴
	{
		for(j = 0; j < m_col; j++) // 열을 증가 시킴
		{
			printf("%3d ", matrix[i][j]); // 화면에 출력
		}
		printf("\n");  // 화면에 개행문자 출력
	}

	// Dynamic으로 할당된 배열을 해제
	for(i = 0; i < m_row; i++)  free(matrix[i]);
	free(matrix);

	return 0;
}
