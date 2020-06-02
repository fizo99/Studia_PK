#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

enum SPECS{
	COMPSCI,
	MATHS,
	PHYSICS
};
struct DATA {
	char *surname;
	SPECS spec;
	int year;
};

// returns pointer to object made with given arguments
void *DATA_new(char *surname, SPECS spec, int year);
// removes object from memory
bool  DATA_free(void *ptr);
// prints object fields on screen
void  DATA_show(void *ptr);	
// comparing functions
void DATA_compare_spec(void *ptr1, void *ptr2);
void DATA_compare_surname(void *ptr1, void *ptr2);
void DATA_compare_year(void *ptr1, void *ptr2);
// returns pointer to new object made with data from file
void *DATA_load(FILE *f);		
// writes object fields to file (all as strings)
void  DATA_save(FILE *f,void *ptr);	
