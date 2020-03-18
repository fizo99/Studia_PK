//Implementacja stosu(dynamiczne struktury danych)
//	[] obsluga bledow i komunikatow
//	[] obsluga stosu
//		{} inicjacja
//		{} zwolnienie stosu
//		{} dodanie nowego elementu
//		{} pobranie pierwszego elementu
//		{} odnalezienie podanego elementu
//		{} zapis zawartosci stosu na dysk w plik binarny
//		{} odczyt z dysku

#include "stack.h"
#pragma warning (disable:4996)

static STACK *first = NULL; //wskaznik do 1-go elementu
static int capacity = 0;	//licznik ilosci elementow stosu

void STACK_init() {

}
int STACK_capacity() {
	return capacity;
}
void *STACK_push	  (void *pdat)
{
	//alokujemy pamiec dla nowego elementu kolejki
	STACK *current = (STACK *)malloc(sizeof(STACK));

	//pusta lista
	if (first == NULL) {
		current->next = NULL;
		first = current;
	}
	//niepusta lista
	else {
		current->next = first;
		first = current;
	}
	current->data = pdat;
	capacity++;
	return current;
}
void STACK_pop		  (DATA_FREE clear){
	//alokujemy pamiec dla nowego elementu kolejki
	STACK *current = (STACK *)malloc(sizeof(STACK));

	//pusta lista
	if (first == NULL) {
		printf("\n\tLista jest pusta");
		return;
	}
	//niepusta lista
	else {
		current = first;
		first = first->next;
		if (clear(current) == 1) {
			printf("\n\tPomyslnie usunieto element");
			capacity--;
		}
		else {
			printf("\n\tBlad usuwania");
		}
	}
}
void STACK_show_first (DATA_SHOW show) {
	//STACK *temp = (STACK*)malloc(sizeof(STACK));
	//temp = first;//funkcja wyswietla pierwszy element 
	if (first != NULL) {
		show(first->data);
	}
	else {
		printf("\tBrak pierwszego elementu");
	};
}
int  STACK_free		  (DATA_FREE clear) {
	//pusta lista
	
	if (first == NULL) {
		return 1;
	}
	//lista niepusta
	else {
		STACK *current = first;
		STACK *new_current = first->next;
		if (new_current == NULL) {
			clear(current->data);
			first = new_current;
			capacity--;
			return 1;
		}
		else {
			while (new_current != NULL) {
				clear(current->data);
				free(current);
				current = new_current;
				new_current = new_current->next;
				capacity--;
			}
			capacity--;
			current = new_current;
			first = current;
		}
		return 1;
	}
}
void STACK_show_stack (DATA_SHOW show) {
	if (first == NULL) {
		printf("\n\tStos pusty");
		return;
	}
	else {
		STACK *current = first;
		int i = 1;
		while (current->next != NULL) {
			printf("\n\t%d.\n", i);
			show(current->data);
			printf("\n");
			current = current->next;
			i++;
		}
		printf("\n\t%d.\n", i);
		show(current->data);
		printf("\n");
	}
}
void STACK_find_surname(char *surname, DATA_COMP_SURNAME comp_surname, DATA_SHOW show) {
	if (first == NULL) {
		printf("\n\tStos jest pusty");
		return;
	}
	STACK *current = first;
	int k = 0;
	int i = 1;
	while (current != NULL) {
		if (comp_surname(surname, current->data)) {
			printf("\n");
			printf("\t%d.\n", i);
			show(current->data);
			current = current->next;
			i++;
			k++;
		}
		else {
			current = current->next;
			i++;
		}
	}
	if (k == 0) printf("\n\tBrak wynikow");
}
//TODO


void *STACK_ret_first() {
	return (void*)first;
}

void STACK_save(FILE *f, DATA_SAVE save) {
	STACK *temp = first;
	while (temp != NULL) {
		save(f, temp->data);
		temp = temp->next;
	}
}
void STACK_load(FILE *f, DATA_LOAD load) {
	//void *ptr;
	char buffer[255];
	while (fscanf(f, "%s", buffer) != EOF) {
		STACK_push(load(f, buffer));
	}
}

//void STACK_find(SEARCH_TYPE type,void *data){
//	if (capacity == 0) {
//		printf("\n\tStos jest pusty");
//		return;
//	}
//	else {
//		STACK *current = first;
//		DATA_SHOW show;
//		switch (type) {
//		case YEAR:
//			DATA_COMP_YEAR year;
//			while (current != NULL) {
//				if (year(data, current->data)) {
//					show(current->data);
//					current = current->next;
//				}
//			}
//			break;
//		case SURNAME:
//			DATA_COMP_SURNAME surname;
//			while (current != NULL) {
//				if (surname(data, current->data)) {
//					show(current->data);
//					current = current->next;
//				}
//			}
//			break;
//		case SPEC:
//			DATA_COMP_SPEC spec;
//			while (current != NULL) {
//				if (spec(data, current->data)) {
//					show(current->data);
//					current = current->next;
//				}
//			}
//			break;
//		}
//	}
//}
