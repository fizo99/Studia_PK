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
// compare object SURNAME field with given surname
bool  DATA_compare_surname(char *test_surname, void *ptr1);
// returns pointer to new object made with data from file
void *DATA_load(FILE *f,char *buffer);		
// writes object fields to file (all as strings)
void  DATA_save(FILE *f,void *ptr);	
