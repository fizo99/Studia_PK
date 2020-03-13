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
#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef enum SPECS SPECS;
typedef void *(*DATA_NEW)(char surname[], SPECS spec, int year);	//wskaznik do funkcji tworzacej obiekt(strukture) typu DATA
typedef void (DATA_SHOW) (void *ptr);								//wskaznik do funkcji pokazujacej dane struktury DATA
typedef int	 (DATA_FREE) (void *ptr);								//wskaznik do funkcji zwalniajacej miejsce po strukturze DATA

typedef int	 *(DATA_COMP_SURNAME)(char *test_surname, void *ptr1);

//typedef int	 (DATA_COMP_YEAR)(void  *test_year, void *ptr1);
//typedef int	 (DATA_COMP_SPEC)(void *test_spec, void *ptr1);

struct STACK {
	void  *data;
	STACK *next;
};
enum SEARCH_TYPE {
	YEAR,
	SURNAME,
	SPEC
};

//void STACK_init(DATA_FREE pFreeDat);		//inicjacja stosu
int STACK_capacity	  ();
int	STACK_free		  (DATA_FREE clear);	//zwolnienie pamieci
void *STACK_push	  (void *pdat);			//dodanie nowego elementu
void STACK_pop		  (DATA_FREE clear);	//usuniecie pierwszego elementu
void STACK_show_first (DATA_SHOW show);		//pokazanie 1 elementu
void STACK_show_stack (DATA_SHOW show);		//wyswietlenie calego stosu
void STACK_find_surname(char *surname, DATA_COMP_SURNAME comp_surname, DATA_SHOW show);							//odnalezienie podanego elementu
void STACK_save();							//zapis na dysk
void STACK_read();							//odczyt z dysku
