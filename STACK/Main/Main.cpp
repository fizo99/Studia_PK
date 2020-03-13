/*
	Implementacja stosu (dynamiczne struktury danych)
	[] obsluga bledow i komunikatow
	[] obsluga stosu
		{} inicjacja
		{*} zwolnienie stosu
		{*} dodanie nowego elementu
		{*} pobranie pierwszego elementu
		{} odnalezienie podanego elementu
		{} zapis zawartosci stosu na dysk w plik binarny
		{} odczyt z dysku
	[*] interfejs (wyprowadzenie elementow stosu oraz menu)
	[] struktura danych
		{} funkcje obslugi
			" " zapis/odczyt obiektu na/z dysku
			"*" wyprowadzenie na monitor
			"*" inicjowanie obiektu
			"*" zwolnienie pamieci
			" " funkcja porownujaca wartosci obiektow
	[+] podzial kazdej skladowej z powyzszych na plik cpp i h
		{} funkcje wewnetrzne (dostepne tylko z poziomu pliku w ktorych sie ich uzywa)
				   zewnetrzne (dostepne w kazdym miejscu programu)

*/

#include "interface.h"

#pragma warning (disable:4996)

int main()
{
	//STACK_init(DATA_free);
	OPTION op = DODAJ_PIERWSZY;
	while (op >= DODAJ_PIERWSZY && op <= STOP) {
		show_menu();
		scanf("%d", &op);
		switch (op)
		{
		case DODAJ_PIERWSZY: push();
			break;
		case USUN_PIERWSZY: pop();
			break;
		case WYCZYSC_STOS: clear();
			break;
		case POKAZ_PIERWSZY: show_top();
			break;
		case POKAZ_STOS: show_stack();
			break;
		case SZUKAJ: find();
			break;
		case ZAPISZ: save();
			break;
		case WCZYTAJ: load();
			break;
		case STOP: clear();
			return 0;
		default:
			printf("nieuznawany kod operacji\n");
		};
	}
}

