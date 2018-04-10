#include <stdio.h>
#define MAX 100

typedef struct _people
{
	char name[MAX];
	char people_num[MAX];
	char birth_info[MAX];
	char phone_num[MAX];
	char address[MAX];
} People;

int main()
{
	People people;
	int i;
	int line_count = 0;
	char temp[MAX];

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

	for (i = 0; i < line_count; i++)
	{
		fscanf(fp, "%s %s %s %s %s", people.people_num, people.name, people.birth_info, people.phone_num, people.address);

		printf("이름 : %s\n", people.name);
		printf("주민번호 : %s\n", people.people_num);
		printf("생년월일 : %s\n", people.birth_info);
		printf("전화번호 : %s\n", people.phone_num);
		printf("주소 : %s\n", people.address);
		printf("\n");
	}

	fclose(fp);

	return 0;
}
