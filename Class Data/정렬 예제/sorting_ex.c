#include <stdio.h>	// 입출력을 위한 전처리명령문
#include <stdlib.h>	// 동적할당을 위한 전처리명령문

void bubble_sort(int *list, int n)
{
	int i, j, temp;
	for(i = n-1; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			if(list[j] > list[j+1])
			{
				temp = list[j];
				list[j] = list[j+1];
				list[j+1] = temp;
			}
		}
	}
}

void main()
{
	FILE *fp;
	int *data;	// 파일안의 숫자의 자료형.
	int cnt=0;	// 숫자의 개수를 카운트 하기 위한 변수
	int i = 0,temp;
	int tot = 0;
	float avg;

	
	fp = fopen("data.txt" , "r");  // 파일개방
	if (fp == NULL)	
	{ 
		printf("파일개방에러.");
		return ;
	}

	while(!feof(fp))	// 파일이 끝이 아니면 파일에서 데이터를 읽어옴
	{
		fscanf(fp, "%d" , &temp);
		cnt++;
	}

    
	// 정수형으로 파일의 데이터 수만큼 동적할당
	data = (int*)malloc(sizeof(int) * cnt);		

	rewind(fp);


	for(i=0; i<cnt;i++)	//파일에 저장된 데이터의 수만큼 배열에 입력
	{
		fscanf(fp, "%d" , &data[i]);
	}

	fclose(fp);
	
	//입력이 모두 끝나면 그것을 출력.
	for(i=0; i<cnt; i++)
	{
		printf("%d\n",data[i]);
		tot += data[i];
	}

	avg = tot/(float)cnt;

	printf("파일안의 숫자의 갯수는 %d 개 입니다.\n", cnt);
	printf("숫자의 총합은 %d 입니다.\n", tot);
	printf("숫자의 평균은 %2.3f 입니다.\n", avg);
	
	bubble_sort(data, cnt);

	printf("\n\n버블 정렬후 결과....\n");
	for(i=0; i<cnt; i++)
	{
		printf("%d ",data[i]);
	}
	printf("\n");

	free(data);
}