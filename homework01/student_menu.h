#include <stdio.h>
#include <string.h>

#define NAMELEN				128
#define MAX_STUDENT			100

typedef struct
{
	char fullName[NAMELEN];
	unsigned int id;
	unsigned int birthYear;
	float mediumScore;
}student_t;

student_t *student_info_lookup(unsigned int id);
void student_info_add();
void student_info_delete();
void student_info_edit();
void student_info_dump();