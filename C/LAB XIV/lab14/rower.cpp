#include "rower.h"

//alokowanie pamieci
MY_ROWER *rower_alloc(int model_length) {
	//obsluga bledow DODAC
	MY_ROWER *newRower = (MY_ROWER*)malloc(sizeof(MY_ROWER));
	newRower->model = (char*)malloc((model_length+1) * sizeof(char));
	return newRower;
}


//zwalnianie pamieci
void rower_free(void *ptr) {
	//obsluga bledow DODAC
	MY_ROWER *temp = (MY_ROWER*)ptr;
	free(temp->model);
	free(temp);
}

//pokazanie danych
void rower_show(void *pDat) {
	MY_ROWER *temp = (MY_ROWER*)pDat;
	printf("\nRower");
	printf("\nModel: %s", temp->model);
	printf("\nRok: %d\n", temp->year);
}

////tworzenie nowego obiektu
void *newRower() {
	char buff[255];
	printf("\nNazwa: ");
	scanf("%s", buff);

	MY_ROWER *rower = rower_alloc(strlen(buff));
	strcpy(rower->model, buff);

	printf("Rok: ");
	scanf("%d", &rower->year);

	return (void*)rower;
}

void *rower_copy(void *src) {
	MY_ROWER *temp = (MY_ROWER*)src;

	MY_ROWER *nRower = (MY_ROWER*)malloc(sizeof(MY_ROWER));
	nRower->model = (char*)malloc((strlen(temp->model) + 1) * sizeof(char));

	strcpy(nRower->model, temp->model);
	nRower->year = temp->year;

	return (void*)nRower;
}