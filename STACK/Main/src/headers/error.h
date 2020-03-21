#pragma once
#include <stdio.h>

enum ERRORS {
	SPEC_NOT_VALID,
	SURNAME_NOT_VALID,
	YEAR_NOT_VALID,
	FILE_OPEN_FAILED,
	FILE_CLOSE_FAILED,
	POP_FAILED,
	PUSH_FAILED,
	CLEAR_FAILED,
	INPUT_NOT_VALID
};

enum COMMUNICATE {
	STACK_ELEM_POPPED,
	STACK_ELEM_PUSHED,
	STACK_CLEARED,
	STACK_EMPTY,
	STACK_SAVED,
	STACK_LOADED,
	FILE_EMPTY,
	NO_RESULTS
};

void raise_error(ERRORS err);
void raise_communicate(COMMUNICATE comm);