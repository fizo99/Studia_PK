#pragma once
#pragma warning(disable:4996)

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct MY_TRIP
{
	char *trace;
};

//alokowanie pamieci
MY_TRIP *trip_alloc(int trace_length);

//zwalnianie pamieci
void trip_free(void *pDat);

//pokazanie danych
void trip_show(void *pDat);

//tworzenie nowego obiektu
void *newTrip();

void *trip_copy(void *src);