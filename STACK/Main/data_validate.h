#pragma once
#include <stdio.h>		//printf
#include <stdlib.h>		//atoi
#include <string.h>		//strlen
#include <cctype>		//isdigit
#include <stdbool.h>	//boolean data type


//data validation
//return true if data is not valid , otherwise false
bool surname_validate(char *buffer);	
bool spec_validate(char *buffer);
bool year_validate(char *buffer);

//todo
//ERRORS HANDLER