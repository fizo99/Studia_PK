#include <stdio.h>

#include "rower.h"
#include "trip.h"
#include "container.h"

const char* menu = " \n[0] - dodaj\n[1] - pokaz\n[2] - zakoncz\n[3] - kopia\n[4] - przypisz element tablicy i do elementu tablicy j(tab[j] = tab[i])\n\nOpcja: ";

enum INTERFACE {
	DODAJ,
	POKAZ,
	ZAKONCZ,
	KOPIA,
	PRZYPISZ
};

enum OPTION {
	ROWER,
	TRIP
};

int main()
{
	INTERFACE op = DODAJ;

	int size;
	printf("KONFIGURACJA\nPODAJ ROZMIAR TABLICY: ");
	scanf("%d", &size);

	TAB_DYN *kopia = NULL;
	TAB_DYN *tab = init(size);
	void *ptr = NULL;

	while (op == DODAJ || op == POKAZ || op == KOPIA || op == PRZYPISZ ) {
		printf("%s", menu);
		scanf("%d", &op);
		switch (op) {
		case DODAJ:
		{
			OPTION vehicle = ROWER;
			printf("\nPODAJ TYP DANYCH: ");
			printf("\n[0] - Rower");
			printf("\n[1] - Trasa\n\nOpcja: ");
			scanf("%d", &vehicle);
			if (vehicle == ROWER) {
				ptr = newRower();
				append(tab, ptr, rower_free, rower_show, rower_copy);
			}
			else {
				ptr = newTrip();
				append(tab, ptr, trip_free, trip_show, trip_copy);
			}
			break;
		}
		case KOPIA:
			if (kopia)
				free_tab(kopia);
			kopia = make_copy(tab); // stworzenie kompletnej kopii tablicy
			if(kopia)
				show(kopia);
			break;
		case PRZYPISZ:
		{
			int i, j;
			printf("\nindeks elementu przypisywanego i: ");
			scanf("%d", &i);
			printf("indeks j(miejsce docelowe dla elementu tab[%d]): ",i);
			scanf("%d", &j);
			assign(tab,i, j);
			break;
		}
		case POKAZ:
			if(tab)
				show(tab);
			break;
		case ZAKONCZ:
			if(tab)
				free_tab(tab);
			if (kopia)
				free_tab(kopia);
			return 0;
		}
	}
	
}

