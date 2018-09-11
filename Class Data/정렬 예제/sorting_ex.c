#include <stdio.h>	// ������� ���� ��ó����ɹ�
#include <stdlib.h>	// �����Ҵ��� ���� ��ó����ɹ�

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
	int *data;	// ���Ͼ��� ������ �ڷ���.
	int cnt=0;	// ������ ������ ī��Ʈ �ϱ� ���� ����
	int i = 0,temp;
	int tot = 0;
	float avg;

	
	fp = fopen("data.txt" , "r");  // ���ϰ���
	if (fp == NULL)	
	{ 
		printf("���ϰ��濡��.");
		return ;
	}

	while(!feof(fp))	// ������ ���� �ƴϸ� ���Ͽ��� �����͸� �о��
	{
		fscanf(fp, "%d" , &temp);
		cnt++;
	}

    
	// ���������� ������ ������ ����ŭ �����Ҵ�
	data = (int*)malloc(sizeof(int) * cnt);		

	rewind(fp);


	for(i=0; i<cnt;i++)	//���Ͽ� ����� �������� ����ŭ �迭�� �Է�
	{
		fscanf(fp, "%d" , &data[i]);
	}

	fclose(fp);
	
	//�Է��� ��� ������ �װ��� ���.
	for(i=0; i<cnt; i++)
	{
		printf("%d\n",data[i]);
		tot += data[i];
	}

	avg = tot/(float)cnt;

	printf("���Ͼ��� ������ ������ %d �� �Դϴ�.\n", cnt);
	printf("������ ������ %d �Դϴ�.\n", tot);
	printf("������ ����� %2.3f �Դϴ�.\n", avg);
	
	bubble_sort(data, cnt);

	printf("\n\n���� ������ ���....\n");
	for(i=0; i<cnt; i++)
	{
		printf("%d ",data[i]);
	}
	printf("\n");

	free(data);
}