#include "headers/data.h"
#pragma warning (disable : 4996)

void *DATA_new(char *surname, SPECS spec, int year) {
	DATA *temp = (DATA *)malloc(sizeof(DATA));

	if (!temp)
		return NULL;

	if (surname)
		temp->surname = (char *)malloc((strlen(surname) + 1) * sizeof(char)); //SF       + 1 ?
	else
		temp->surname = NULL;
	//

	if (temp != NULL) {
		temp->spec = spec;
		temp->year = year;
		if (surname)
			strcpy(temp->surname, surname);
	}
	return (void *)temp;
}
bool DATA_free(void *ptr) {
	if (ptr) {
		DATA *temp = (DATA*)ptr;
		if (temp->surname)
			free(temp->surname);
		free(ptr);
		return true;
	}
	else return false;
}
void  DATA_show(void *ptr) {
	if (ptr != NULL) {
		DATA *temp = (DATA *)ptr;

		printf("\tSurname:        %s\n", temp->surname);
		printf("\tYear:           %d\n", temp->year);

		switch (temp->spec) {
		case COMPSCI:
			printf("\tSpecialization: Computer Science\n");
			break;
		case MATHS:
			printf("\tSpecialization: Mathematics\n");
			break;
		case PHYSICS:
			printf("\tSpecialization: Physics\n");
			break;
		}
	}
}
void DATA_compare_spec(void *ptr1, void *ptr2) {
	DATA *temp1 = (DATA*)ptr1;
	DATA *temp2 = (DATA*)ptr2;

	if ((int)temp1->spec == (int)temp2->spec)
		DATA_show(ptr1);
}
void DATA_compare_surname(void *ptr1, void *ptr2) {
	DATA *temp1 = (DATA*)ptr1;
	DATA *temp2 = (DATA*)ptr2;

	if (temp1->surname && temp2->surname)
		if (!strcmp(temp1->surname, temp2->surname))
			DATA_show(ptr1);
}
void DATA_compare_year(void *ptr1, void *ptr2) {
	DATA *temp1 = (DATA*)ptr1;
	DATA *temp2 = (DATA*)ptr2;

	if ((int)temp1->year == (int)temp2->year)
		DATA_show(ptr1);
}
void  DATA_save(FILE *f, void *ptr) {
	DATA *temp = (DATA*)ptr;
	int length = strlen(temp->surname) + 1;

	fwrite(temp, 1, _msize(temp), f);
	fwrite(&length, sizeof(int), 1, f);
	fwrite(temp->surname, 1, _msize(temp->surname), f);
}
void *DATA_load(FILE *f) {
	DATA *obj = (DATA*)malloc(sizeof(DATA));
	int surnameSize;

	fread(obj, 1, _msize(obj), f);
	fread(&surnameSize, sizeof(int), 1, f);
	obj->surname = (char*)malloc(sizeof(char)*surnameSize);
	fread(obj->surname, 1, _msize(obj->surname), f);

	return (void*)obj;
}
