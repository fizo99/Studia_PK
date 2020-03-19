#include "headers/data.h"
#pragma warning (disable : 4996)

void *DATA_new(char *surname, SPECS spec, int year) {
	DATA *temp = (DATA *)malloc(sizeof(DATA));
	temp->surname = (char *)malloc(strlen(surname) * sizeof(char));

	if (temp != NULL) {
		temp->spec = spec;
		temp->year = year;
		strcpy(temp->surname, surname);
	}
	return (void *)temp;
}
bool  DATA_free(void *ptr) {
	if (ptr != NULL) {
		free(ptr);
		return true;
	}
	else return false;
}
void  DATA_show(void *ptr) {
	if (ptr != NULL) {
		DATA *temp = (DATA *)ptr;

		printf("\tSurname:   %s\n", temp->surname);
		printf("\tYear:      %d\n", temp->year);

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
bool  DATA_compare_surname(char *test_surname, void *ptr1) {
	DATA *temp = (DATA*)ptr1;
	if (!strcmp(test_surname, temp->surname)) return true;
	else return false;
}
void  DATA_save(FILE *f, void *ptr) {
	//SAVING WHOLE DATASET AS STRING(one line ended by '\n')
	//format SURNAMEYEARSPECIALIZATION\n

	DATA *temp = (DATA*)ptr;
	char year[5];
	char spec[2];

	sprintf(year, "%d", temp->year);
	sprintf(spec, "%d", temp->spec);
	fwrite(temp->surname, sizeof(char), strlen(temp->surname), f);
	fwrite(year, sizeof(char), strlen(year), f);
	fwrite(spec, sizeof(char), strlen(spec), f);
	fwrite("\n", sizeof(char), 1, f); //endline
}
void *DATA_load(FILE *f, char *buffer) {
	int j = 0;
	int len = strlen(buffer);
	char specbuff = '\0';
	char yearbuff[5] = "\0";
	char surnamebuff[255] = "\0";

	specbuff = buffer[len - 1];
	for (int i = (len - 5); i < (len - 1); i++) {
		yearbuff[j] = buffer[i];
		j++;
	}
	for (int i = 0; i < len - 5; i++) {
		surnamebuff[i] = buffer[i];
	}

	int spec;
	int year;
	sscanf(&specbuff, "%d", &spec);
	sscanf(yearbuff, "%d", &year);
	return DATA_new(surnamebuff, (SPECS)spec, year);
}
