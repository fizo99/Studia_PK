#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

struct MY_ROWER
{
	char *model; //nazwa modelu
	int year; //rok sprzeda¿y
};


//alokowanie pamieci
MY_ROWER *rower_alloc(int model_length);

//zwalnianie pamieci
void rower_free(void *pDat);

//pokazanie danych
void rower_show(void *pDat);

//tworzenie nowego obiektu
void *newRower();

void *rower_copy(void *src);