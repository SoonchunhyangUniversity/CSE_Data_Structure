#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct _animal
{
	char type[MAX];
	char inherent_num[MAX];
	char loc[MAX];
	char population[MAX];
} Animal;

enum
{
	type = 1, inherent_num, loc, population
};

int main()
{
	int i, input, idx;
	char temp[MAX], input_info[MAX];
	Animal *struct_arr;
	int line_count = 0;

	FILE *fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fgets(temp, MAX, fp);
		line_count++;
	}

	rewind(fp);

	struct_arr = (Animal *)malloc(sizeof(Animal) * line_count);

	for (i = 0; i < line_count; i++)
	{
		fscanf(fp, "%s %s %s %s", struct_arr[i].type, struct_arr[i].inherent_num, struct_arr[i].loc, struct_arr[i].population);
	}


	printf("검색하실 조건을 선택하여 주십시오.\n");
	printf("< 1.종 2.고유번호 3.위치 4.개채수>\n");
	scanf("%d", &input);
	printf("검색하실 정보를 입력하여 주십시오 : ");
	scanf("%s", &input_info);

	switch (input)
	{
	case type:
		for (i = 0; i < line_count; i++)
		{
			if (!strcmp(input_info, struct_arr[i].type))
				idx = i;
		}
		break;
	case inherent_num:
		for (i = 0; i < line_count; i++)
		{
			if (!strcmp(input_info, struct_arr[i].inherent_num))
				idx = i;
		}
		break;
	case loc:
		for (i = 0; i < line_count; i++)
		{
			if (!strcmp(input_info, struct_arr[i].loc))
				idx = i;
		}
		break;
	case population:
		for (i = 0; i < line_count; i++)
		{
			if (!strcmp(input_info, struct_arr[i].population))
				idx = i;
		}
		break;
	default:
		printf("조건 입력 오류!\n");
		break;
	}

	printf("종 : %s\n", struct_arr[idx].type);
	printf("고유번호 : %s\n", struct_arr[idx].inherent_num);
	printf("위치 : %s\n", struct_arr[idx].loc);
	printf("개체 수 : %s\n", struct_arr[idx].population);

	free(struct_arr);
	fclose(fp);

	return 0;
}
