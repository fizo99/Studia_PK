#include "headers/interface.h"
#include "headers/data.h"
#include "headers/stack.h"

#pragma warning(disable:4996)

void push() {
	system("cls");
	
	char surname[255];
	int year;
	int spec;

	char buffer[255];
	int retval;

	printf("\n\tADDING NEW ELEMENT");

	//specialization
	printf("\n\t(0) Computer Science        ");
	printf("\n\t(1) Maths        ");
	printf("\n\t(2) Physics        ");
	printf("\n\n\tChoice (number):  ");
	retval = scanf_s("%s", buffer,2);
	
	if (!retval || !spec_validate(buffer)) {
		raise_error(SPEC_NOT_VALID);
		clean_stream();
		end();
		return;
	}
	spec = (int)atoi(buffer);
	memset(buffer, 0, 255);

	//surname
	printf("\tSurname:          ");
	retval = scanf_s("%s", buffer,254);

	if (!retval || !surname_validate(buffer)) {
		raise_error(SURNAME_NOT_VALID);
		clean_stream();
		end();
		return;
	}
	strcpy(surname, buffer);
	memset(buffer, 0, 255);

	//year
	printf("\tYear (1900-2020): ");
	retval = scanf_s("%s", buffer,5);

	if (!retval || !year_validate(buffer)) {
		raise_error(YEAR_NOT_VALID);
		clean_stream();
		end();
		return;
	}
	year = (int)atoi(buffer);

	if (STACK_push(DATA_new(surname, (SPECS)spec, year))) raise_communicate(STACK_ELEM_PUSHED);
	else raise_error(PUSH_FAILED);
	end();
}
void pop() {
	system("cls");

	STACK_pop(DATA_free);
	end();
}
void clear() {
	system("cls");

	if (STACK_ret_first() == NULL) {
		raise_communicate(STACK_EMPTY);
		end();
		return;
	}

	if (STACK_free(DATA_free)) raise_communicate(STACK_CLEARED);
	else raise_error(CLEAR_FAILED);
	end();
}
void show_top() {
	system("cls");

	if (STACK_ret_first() == NULL) {
		raise_communicate(STACK_EMPTY);
		end();
		return;
	}
	printf("\n\tFIRST ELEMENT OF STACK\n\n");
	STACK_show_top(DATA_show);
	end();
}
void show_stack() {
	system("cls");

	STACK_show_stack(DATA_show);
	end();
}
void find() {
	system("cls");

	char temp[255] = "\0";
	int retval;

	printf("\n\tSEARCHING BY SURNAME\n");
	printf("\n\tsurname: ");
	retval = scanf_s("%s", temp,254);
	if (!retval) {
		raise_error(INPUT_NOT_VALID);
		clean_stream();
		return;
	}
	printf("\n\tRESULTS: ");
	STACK_find_surname(temp, DATA_compare_surname, DATA_show);
	end();
}
void save() {
	system("cls");

	if (STACK_ret_first() == NULL) {
		raise_communicate(STACK_EMPTY);
		end();
		return;
	}

	char buffer[255] = "\0";
	char ext[5] = ".bin";
	int retval;

	printf("\n\tFile name (without extension): ");
	retval = scanf_s("%s", buffer, 254);
	if (!retval) {
		raise_error(INPUT_NOT_VALID);
		clean_stream();
		return;
	}
	strncat(buffer, ext, 4);

	FILE *f = fopen(buffer, "wb");
	if (f == NULL) {
		raise_error(FILE_OPEN_FAILED);
		end();
		return;
	}
	bool ret = STACK_save(f, DATA_save);

	if (fclose(f) == EOF) {
		raise_error(FILE_CLOSE_FAILED);
		end();
		return;
	}
	if (ret) {
		raise_communicate(STACK_SAVED);
		end();
	}
	else end();
}
void load() {
	system("cls");

	char buffer[255] = "\0";
	char ext[5] = ".bin";
	int retval;

	printf("\n\tFile name (without extension): ");
	retval = scanf_s("%s", buffer,254);
	if (!retval) {
		raise_error(INPUT_NOT_VALID);
		clean_stream();
		return;
	}
	strncat(buffer, ext, 4);
	
	FILE *f = fopen(buffer, "rb+");
	if (f == NULL) {
		raise_error(FILE_OPEN_FAILED);
		end();
		return;
	}
	int lines = num_lines(f);
	if (lines == 0) {
		raise_communicate(FILE_EMPTY);
		fclose(f);
		end();
		return;
	}
	STACK_load(f, DATA_load);
	if (fclose(f) == EOF) {
		raise_error(FILE_CLOSE_FAILED);
		end();
		return;
	}
	raise_communicate(STACK_LOADED);
	end();
}
void clear_and_quit() {
	if (STACK_free(DATA_free)) raise_communicate(STACK_CLEARED);
	else raise_error(CLEAR_FAILED);
}

//menu
void show_menu() {
	system("cls");
	printf("\n\tCHOOSE OPTION\n\n");
	printf("\t0: Push\n");
	printf("\t1: Pop\n");
	printf("\t2: Clear stack\n");
	printf("\t3: Show first element\n");
	printf("\t4: Show stack\n");
	printf("\t5: Look for element in stack\n");
	printf("\t6: Save stack to file\n");
	printf("\t7: Load stack from file\n");
	printf("\t8: Clear stack and stop programme\n");
	printf("\n\tCURRENT NUMBER OF ELEMENTS ON STACK: %d\n", STACK_capacity());
	printf("\n\tOption: ");
}
void end() {
	printf("\n\t");
	system("pause");
}
void clean_stream() {
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {}
}

// data validation
bool surname_validate(char *buffer) {
	int length = strlen(buffer);
	int i = 0;
	while (i < length) {
		if ((buffer[i] > 64 && buffer[i] < 91) || (buffer[i] > 96 && buffer[i] < 123)) {
			i++;
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}
bool spec_validate(char *buffer) {
	if (strlen(buffer) == 1) {
		if (buffer[0] == '0') return true;
		else if (buffer[0] == '1' || buffer[0] == '2') return true;
		else {
			return false;
		}
	}
	return false;
}
bool year_validate(char *buffer) {
	if (strlen(buffer) == 4) {
		for (int i = 0; i < 4; i++) {
			if (isdigit(buffer[i]) == 0) {
				return false;
			}
			else continue;
		}
		int year = (int)atoi(buffer);
		if (year > 1899 && year < 2021) return true;
	}
	return false;
}
