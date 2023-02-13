#include "student_menu.h"

student_t students_data[MAX_STUDENT];
int num_student = 0;

student_t *student_info_lookup(unsigned int id)
{
	int num;

	if(num_student == 0)
		return NULL;

	for(num = 0; num < num_student; num++)
		if(students_data[num].id == id)
			return &students_data[num];

	return NULL;
}

void student_info_add()
{
	unsigned int id;
	student_t *student_info;
	char temp;

	if(num_student == MAX_STUDENT)
	{
		printf("Cannot add student information!\n");
		return;
	}

	while(1)
	{
		printf("Enter student ID: ");
		scanf("%d", &id);
		student_info = student_info_lookup(id);
		if(student_info == NULL)
			break;
		else
			printf("Already have this student ID. Try again!\n");
	}

	students_data[num_student].id = id;
	printf("Enter Full Name of student: ");
	scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]", &students_data[num_student].fullName);
	printf("Enter Year of Birth: ");
	scanf("%u", &students_data[num_student].birthYear);
	printf("Enter Medium Score: ");
	scanf("%f", &students_data[num_student].mediumScore);
	num_student++;
}

void student_info_delete()
{
	unsigned int id;
	int num1, num2, find_id = 0;

	if(num_student == 0)
	{
		printf("Don't have student data to delete!\n");
		return;
	}

	printf("Enter student ID deleted: ");
	scanf("%d", &id);

	for(num1 = 0; num1 < num_student; num1++)
		if(students_data[num1].id == id)
		{
			memset(&students_data[num1], '\0', sizeof(student_t));
			if(num1 < (num_student - 1))
				for(num2 = num1; num2 < (num_student -1 ); num2++)
					memcpy(&students_data[num2], &students_data[num2 + 1], sizeof(student_t));
			find_id = 1;
			num_student--;
			break;
		}

	if(!find_id)
		printf("Cannot find student ID = %d to delete!\n", id);
}

void student_info_edit()
{
	unsigned int id;
	student_t *student_info;
	char temp;

	printf("Enter student ID to edit: ");
	scanf("%d", &id);

	student_info = student_info_lookup(id);
	if(!student_info)
	{
		printf("Cannot find student ID %d to edit!\n", id);
		return;
	}

	printf("Enter student ID edited: ");
	scanf("%d", &student_info->id);
	printf("Enter Full Name of student edited: ");
	scanf("%c",&temp); // temp statement to clear buffer
	scanf("%[^\n]", &student_info->fullName);
	printf("Enter Year of Birth edited: ");
	scanf("%u", &student_info->birthYear);
	printf("Enter Medium Score edited: ");
	scanf("%f", &student_info->mediumScore);
}

void student_info_dump()
{
	int num;

	if(num_student == 0)
	{
		printf("Do not have any student data to show!\n");
		return;
	}

	for(num = 0; num < num_student; num++)
	{
		printf("No.%d\n", num + 1);
		printf("Student ID: %u\n", students_data[num].id);
		printf("Full Name: %s\n", students_data[num].fullName);
		printf("Year of Birth: %u\n", students_data[num].birthYear);
		printf("Medium Score: %.2f\n", students_data[num].mediumScore);
		printf("\n");
	}
}

int main()
{
	int menu;
	int term_prog = 0;

	while(1)
	{
		printf("Menu\n");
		printf("1: Add student information\n");
		printf("2: Delete student information\n");
		printf("3: Edit student information\n");
		printf("4: Dump student information\n");
		printf("5: Terminate program\n");
		printf("\n");
		printf("Enter menu number: ");
		scanf("%d", &menu);

		switch(menu)
		{
			case 1:
				student_info_add();
				break;

			case 2:
				student_info_delete();
				break;

			case 3:
				student_info_edit();
				break;

			case 4:
				student_info_dump();
				break;

			case 5:
				term_prog = 1;
				break;

			default:
				printf("Please enter menu from 1->5\n");
				break;
		}

		if(term_prog)
			break;
		printf("----------------------------------------------------\n");
		printf("\n");
	}

	return 0;
}