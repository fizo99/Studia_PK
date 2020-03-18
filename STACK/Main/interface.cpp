#include "interface.h"
#include "data.h"
#include "stack.h"
#include "data_validate.h"


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
	char *comp = (char*)malloc(2);

	printf("\n\n\tWpisz cokolwiek aby kontynuowac: ");
	if (scanf("%s", comp)) {
		free(comp);
		system("cls");
	}

}


//obsluga stosu
void push() {
	char *nazwisko = (char*)malloc(255*sizeof(char));
	int rok;
	int spec;

	//zmienna pomocnicza
	char buffer[255];

	system("cls");
	printf("\n\tDODAWANIE NOWEGO ELEMENTU");

	//kierunek
	printf("\n\t(0)Informatyka        ");
	printf("\n\t(1)Matematyka        ");
	printf("\n\t(2)Fizyka        ");
	printf("\n\n\tKierunek(nr):   ");
	scanf("%s", buffer);

	//walidacja danych
	if (spec_validate(buffer)) {
		end();
		return;
	} 
	spec = (int)atoi(buffer);
	memset(buffer, 0, 255);

	//nazwisko
	printf("\tNazwisko:       ");
	scanf("%s", buffer);
	//walidacja danych
	if (surname_validate(buffer)) {
		end();
		return;
	}
	strcpy(nazwisko, buffer);
	memset(buffer, 0, 255);

	//rok
	printf("\tRok(1900-2020): ");
	scanf("%s", buffer);
	//walidacja danych
	if (year_validate(buffer)) {
		end();
		return;
	}
	rok = (int)atoi(buffer);

	//jesli wszystkie dane sa poprawne tworzymy element i dodajemy na stos
	void *n_data = DATA_new(nazwisko,(SPECS)spec, rok);

	if(STACK_push(n_data)) printf("\n\tPomyslnie dodano dane na stos !");
	else printf("\n\tBlad dodawania");
	free(nazwisko);
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
void find() {
	system("cls");
	char *temp = (char*)malloc(255 * sizeof(char));
	printf("\n\tSZUKANIE ELEMENTU PO NAZWISKU");
	printf("\n\tPodaj nazwisko: ");
	scanf("%s", temp);
	void *s;
	STACK_find_surname(temp, (DATA_COMP_SURNAME*)DATA_compare_surname, DATA_show);
	end();
}

//TODO

void save() {
	char *buffer = (char*)malloc(255 * sizeof(char));

	system("cls");
	printf("\n\tPodaj nazwe pliku: ");
	scanf("%s", buffer);

	FILE *f = fopen(buffer, "wb");
	free(buffer);

	//pointer to function
	void(*foo)(FILE *f, void *ptr);
	foo = &DATA_save;

	STACK_save(f, foo);

	fclose(f);
	end();
}
void load() {
	char *buffer = (char*)malloc(255 * sizeof(char));

	system("cls");
	printf("\n\tPodaj nazwe pliku: ");
	scanf("%s", buffer);

	FILE *f = fopen(buffer, "rb");
	free(buffer);

	//pointer to function
	void*(*foo)(FILE *f,char*buffer);
	foo = &DATA_load;

	STACK_load(f, foo);

	fclose(f);
	end();
}

