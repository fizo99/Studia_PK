#pragma once

#include <string.h>
#include <stdio.h>
#include <cstdlib>

#include <stdlib.h>		//atoi
#include <string.h>		//strlen
#include <cctype>		//isdigit
#include <stdbool.h>	//boolean data type

#include "data.h"
#include "stack.h"

enum OPTION {
	PUSH,
	POP,
	CLEAR_STACK,
	SHOW_FIRST,
	SHOW_STACK,
	FIND,
	SAVE,
	LOAD,
	STOP
};

void push();
void pop();
void clear();
void show_top();
void show_stack();
void find();
void save();
void load();

// menu
void show_menu();
void end();

// data validation
bool surname_validate(char *buffer);
bool spec_validate(char *buffer);
bool year_validate(char *buffer);


