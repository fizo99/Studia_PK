// struktura danych
//		[] zapis / odczyt obiektu na / z dysku
//		[*] wyprowadzenie na monitor
//		[*] inicjowanie obiektu
//		[*] zwolnienie pamieci
//		[] funkcja porownujaca wartosci obiektow
#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum   SPECS{
INFORMATYKA,
MATEMATYKA,
FIZYKA
};
struct DATA {
	char *surname;
	SPECS spec;
	int year;
};

void *DATA_new(char *surname, SPECS spec, int year);				//stworzenie nowego obiektu
int  DATA_free(void *ptr);											//zwolnienie pamieci
void DATA_show(void *ptr);											//wyprowadzenie na monitor
int  DATA_compare_surname(char *test_surname, void *ptr1);			//funkcja porownujaca
void *DATA_load(FILE *f,char *buffer);											//wczytanie danych z pliku
void DATA_save(FILE *f,void *ptr);	
//int num_lines(FILE *f);
//zapisanie danych do pliku
//char ** DATA_save(void *ptr);										
//int DATA_compare_year(void  *test_year, void *ptr1);
//int DATA_compare_spec(void *test_spec, void *ptr1);