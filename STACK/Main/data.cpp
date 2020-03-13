// struktura danych
//		[] zapis / odczyt obiektu na / z dysku
//		[*] wyprowadzenie na monitor
//		[*] inicjowanie obiektu
//		[*] zwolnienie pamieci
//		[] funkcja porownujaca wartosci obiektow


#include "data.h"
#pragma warning (disable : 4996)


void DATA_show	  (void *ptr) {
	if (ptr != NULL) {
		DATA *temp = (DATA *)ptr;
		printf("\tNazwisko: %s\n", temp->surname);
		printf("\tRok:      %d\n", temp->year);
		switch (temp->spec) {
		case INFORMATYKA:
			printf("\tKierunek: Informatyka\n");
			break;
		case MATEMATYKA:
			printf("\tKierunek: Matematyka\n");
			break;
		case FIZYKA:
			printf("\tKierunek: Fizyka\n");
			break;
		}
	}
}
int  DATA_free	  (void *ptr) {
	if (ptr != NULL) {
		free(ptr);
		return 1;
	}
	else {
		return 0;
	}
}
void *DATA_new	  (char *surname, SPECS spec, int year) {
	size_t sur_size = _msize(surname);
	DATA *temp = (DATA *)malloc(sizeof(DATA));
	temp->surname = (char *)malloc(sur_size*sizeof(char));

	if (temp != NULL) {
		temp->spec = spec;
		temp->year = year;
		strcpy(temp->surname,(const char*) surname);
	}
	return (void *)temp;
}

//TODO
int DATA_compare_surname(char *test_surname, void *ptr1) {
	DATA *temp = (DATA*)ptr1;
	if (!strcmp(test_surname, temp->surname)) return 1;
	else return 0;
}

//int DATA_compare_surname(void *test_surname, void *ptr1) {
//	DATA *temp = (DATA*)ptr1;
//	if (!strcmp((char*)test_surname, temp->surname)) return 1;
//	else return 0;
//}
//
//int DATA_compare_spec(void *test_spec, void *ptr1) {
//	DATA *temp = (DATA*)ptr1;
//	if (temp->spec == *(int*)test_spec) return 1;
//	else return 0;
//}