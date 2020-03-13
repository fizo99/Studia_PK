#include "interface.h"
#include "data.h"
#include "stack.h"



#pragma warning(disable:4996)

//menu
void show_menu() {
	printf("\n\tWybierz opcje\n");
	printf("\t0: Dodaj element na stos\n");
	printf("\t1: Usun element ze stosu\n");
	printf("\t2: Wyczysc stos\n");
	printf("\t3: Pokaz pierwszy element\n");
	printf("\t4: Pokaz caly stos\n");
	printf("\t5: Szukaj elementu na stosie\n");
	printf("\t6: Zapisz stos na dysk\n");
	printf("\t7: Wczytaj stos z dysku\n");
	printf("\t8: Wyczysc stos i zakoncz program\n");
	printf("\n\tILOSC ELEMENTOW NA STOSIE: %d\n", STACK_capacity());
	printf("\n\tOpcja: ");
}
void end() {
	char *temp = (char*)malloc(2);
	char *comp = (char*)malloc(2);
	temp[0] = 'x';
	temp[1] = '\0';

	printf("\n\n\tWpisz 'x' aby kontynuowac: ");
	scanf("%s", comp);

	if (strcmp(temp, comp) == 0) {
		system("cls");
		free(temp);
		free(comp);
		return;
	}
	else {
		while (strcmp(temp, comp) != 0) {
			printf("\n\tBlad... Podaj litere jeszcze raz: ");
			scanf("%s", comp);
		}
	}
	free(temp);
	free(comp);
	system("cls");
}


//obsluga stosu
void push() {
	char *nazwisko = (char*)malloc(255*sizeof(char));// = (char*)malloc(255 * sizeof(char));
	int rok;
	SPECS spec;
	system("cls");
	printf("\n\tDODAWANIE NOWEGO ELEMENTU");
	printf("\n\t(0)Informatyka        ");
	printf("\n\t(1)Matematyka        ");
	printf("\n\t(2)Fizyka        ");
	printf("\n\n\tKierunek(nr): ");
	scanf("%d", &spec);
	printf("\tNazwisko:     ");
	scanf("%s", nazwisko);
	printf("\tRok:          ");
	scanf("%d", &rok);

	void *n_data = DATA_new(nazwisko, spec, rok);

	if (STACK_push(n_data) != NULL) {
		printf("\n\tPomyslnie dodano dane na stos !");
	}
	end();
}
void pop() {
	system("cls");
	STACK_pop(DATA_free);
	end();
}
void clear() {
	system("cls");
	if (STACK_free(DATA_free)) {
		printf("\n\tStos wyczyszczony");
	}
	end();
}
void show_top() {
	system("cls");
	printf("\n\tPIERWSZY ELEMENT STOSU\n");
	STACK_show_first(DATA_show);
	end();
	return;
}
void show_stack() {
	system("cls");
	STACK_show_stack(DATA_show);
	end();
}

//TODO

void save() {

}
void load() {

}
void find() {
	system("cls");
	char *temp = (char*)malloc(255 * sizeof(char));
	printf("\n\tSZUKANIE ELEMENTU PO NAZWISKU");
	printf("\n\tPodaj nazwisko: ");
	scanf("%s", temp);
	void *s;
	STACK_find_surname(temp, (DATA_COMP_SURNAME*)DATA_compare_surname,DATA_show);
	end();
}

//void find() {
//	system("cls");
//	printf("\n\tSZUKANIE ELEMENTU");
//	printf("\n\tSPOSOB SZUKANIA: ");
//	printf("\n\t(0)po roku");
//	printf("\n\t(1)po nazwisku");
//	printf("\n\t(2)po specjalizacji");
//	printf("\n\tOpcja: ");
//	SEARCH_TYPE s = SURNAME;
//	scanf("%d", &s);
//	system("cls");
//	int *temp_int = (int*)malloc(sizeof(int));
//	char *temp_char = (char*)malloc(255 * sizeof(char));
//	int *temp_spec = (int*)malloc(sizeof(int));
//	switch (s) {
//	case YEAR:
//		printf("\n\tSZUKANIE PO ROKU");
//		printf("\n\tPodaj rok: ");
//		scanf("%d", temp_int);
//		STACK_find(YEAR, (void*)temp_int);
//		break;
//	case SURNAME:
//		printf("\n\tSZUKANIE PO NAZWISKU");
//		printf("\n\tPodaj nazwisko: ");
//		scanf("%s", temp_char);
//		STACK_find(SURNAME, (void*)temp_char);
//		break;
//	case SPEC:
//		printf("\n\tSZUKANIE PO SPECJALIZACJI");
//		printf("\n\t(0)Informatyka        ");
//		printf("\n\t(1)Matematyka        ");
//		printf("\n\t(2)Fizyka        ");
//		printf("\n\tPodaj nr specjalizacji: ");
//		scanf("%d", temp_spec);
//		STACK_find(SPEC, (void*)temp_spec);
//		break;
//	}
//	end();
//}