#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 30

typedef struct _teacher
{
	int num;
	char name[MAX];
} Teacher;

typedef struct _student
{
	char name[MAX];
	int std_num;
	int teacher_num;
	int num;
	int kor;
	int eng;
	int mat;
} Student;

int main()
{
	Teacher *teacher;
	Student *student;
	int teacher_count = 0, student_count = 0, check = 0;
	char char_temp[MAX];

	FILE *fp = fopen("data1.txt", "r");

	if (fp == NULL)
	{
		printf("FILE OPEN ERROR!\n");
		return 0;
	}

	while (!feof(fp))
	{
		fgets(char_temp, MAX, fp);

		if (check == 1 && strcmp(char_temp, "student\n"))
			teacher_count++;
		else if (check == 2 && strcmp(char_temp, "class\n"))
			student_count++;

		if (!strcmp(char_temp, "student\n"))
			check = 2;
		else if (!strcmp(char_temp, "class\n"))
			check = 1;
	}

	rewind(fp);

	teacher = (Teacher *)malloc(sizeof(Teacher) * teacher_count);
	student = (Student *)malloc(sizeof(Student) * student_count);

	/* class 문자열 저장 */
	fgets(char_temp, MAX, fp);

	for (int i = 0; i < teacher_count; i++)
	{
		fscanf(fp, "%d %s", &teacher[i].num, teacher[i].name);
	}

	/* 개행 문자 저장 */
	fscanf(fp, "%c", char_temp);
	/* student 문자열 저장 */
	fgets(char_temp, MAX, fp);

	for (int i = 0; i < student_count; i++)
	{
		fscanf(fp, "%s %d %d %d %d %d %d", student[i].name, &student[i].teacher_num, &student[i].num, &student[i].std_num, &student[i].kor, &student[i].eng, &student[i].mat);
	}

	for (int j = 0; j < teacher_count; j++)
	{
		printf("< %s >\n", teacher[j].name);
		printf("┌───────┬────────┬─────────┬──────┬──────┬──────┐\n");
		printf("│ 이 름 │ 번  호 │ 학   번 │ 국어 │ 영어 │ 수학 │\n");
		printf("├───────┴────────┴─────────┴──────┴──────┴──────┤\n");
		for (int i = 0; i < student_count; i++)
		{
			if (student[i].teacher_num == teacher[j].num)
			{
				printf("│%s │ %4d  │ %d │ %4d │ %4d │ %4d │\n", student[i].name, student[i].num, student[i].std_num, student[i].kor, student[i].eng, student[i].mat);
			}
		}
		printf("└───────┴───────┴──────────┴──────┴──────┴──────┘\n");
	}

	free(teacher);
	free(student);
	fclose(fp);

	return 0;
}
