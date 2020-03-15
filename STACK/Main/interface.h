#pragma once

#include <string.h>
#include <stdio.h>
#include <cstdlib>

#include "data.h"
#include "stack.h"

enum OPTION {
	DODAJ_PIERWSZY,
	USUN_PIERWSZY,
	WYCZYSC_STOS,
	POKAZ_PIERWSZY,
	POKAZ_STOS,
	SZUKAJ,
	ZAPISZ,
	WCZYTAJ,
	STOP
};

//menu
void show_menu();
void end();

//obsluga stosu
void push();
void pop();
void clear();
void show_top();
void show_stack();
void find();
void save();
void load();


