#include "trip.h"


//alokowanie pamieci
MY_TRIP *trip_alloc(int trace_length) {
	MY_TRIP *newTrip = (MY_TRIP*)malloc(sizeof(MY_TRIP));
	newTrip->trace = (char*)malloc((trace_length+1) * sizeof(char));
	return newTrip;
}

//zwalnianie pamieci
void trip_free(void *pDat) {
	if (pDat) {
		MY_TRIP *temp = (MY_TRIP*)pDat;
		if(temp->trace)
			free(temp->trace);
		free(temp);
	}
}

//pokazanie danych
void trip_show(void *pDat) {
	MY_TRIP *temp = (MY_TRIP*)pDat;
	printf("\nTRASA");
	printf("\nTrasa: %s\n", temp->trace);
}

//tworzenie nowego obiektu
void *newTrip() {
	char buff[255];
	printf("Trasa: ");
	scanf("%s", buff);

	MY_TRIP *newTrip = trip_alloc(strlen(buff));
	strcpy(newTrip->trace, buff);
	
	return (void*)newTrip;
}

void *trip_copy(void *src) {
	MY_TRIP *temp = (MY_TRIP*)src;

	MY_TRIP *nTrip = (MY_TRIP*)malloc(sizeof(MY_TRIP));
	nTrip->trace = (char*)malloc((strlen(temp->trace) + 1) * sizeof(char));

	strcpy(nTrip->trace, temp->trace);

	return (void*)nTrip;

}