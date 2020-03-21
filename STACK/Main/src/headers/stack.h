#pragma once
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "error.h"

typedef void (DATA_SHOW) (void *ptr);								//data.h -> DATA_show				
typedef void (DATA_SAVE)(FILE *f,void *ptr);						//data.h -> DATA_save
typedef void *(DATA_LOAD)(FILE *f,char *buffer);					//data.h -> DATA_load
typedef bool (DATA_COMP_SURNAME)(char *test_surname, void *ptr1);	//data.h -> DATA_compare_surname
typedef bool (DATA_FREE)(void *ptr);								//data.h -> DATA_free

struct STACK {
	void  *data;
	STACK *next;
};

// initialization of stack
void STACK_init();
// adds element to the top of stack then returns it
void *STACK_push(void *pdat);
// removes element from the top of stack
void STACK_pop(DATA_FREE clear);
// removes all elements from stack
bool STACK_free(DATA_FREE clear);
// prints fields of the first element of stack
void STACK_show_top(DATA_SHOW show);
// prints fields of every element of stack
void STACK_show_stack(DATA_SHOW show);
// prints every element that match given surname
void STACK_find_surname(char *surname, DATA_COMP_SURNAME comp_surname, DATA_SHOW show);
// writes all stack elements to given file
bool STACK_save(FILE *f, DATA_SAVE save);
// loads stack to memory from given file
void STACK_load(FILE *f, DATA_LOAD load);
// returns first element of stack
void *STACK_ret_first();					

// returns number of stack elements
int STACK_capacity();
// returns number of lines in file
int num_lines(FILE *f);
// inverts the contents of the file (first line <-> last line)
void reverse_file(FILE *f);

