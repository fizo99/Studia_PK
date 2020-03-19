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

	printf("\n\tADDING NEW ELEMENT");

	//specialization
	printf("\n\t(0) Computer Science        ");
	printf("\n\t(1) Maths        ");
	printf("\n\t(2) Physics        ");
	printf("\n\n\tChoice (number):  ");
	scanf("%s", buffer);

	//validation
	if (spec_validate(buffer)) {
		//error
		end();
		return;
	}
	spec = (int)atoi(buffer);
	memset(buffer, 0, 255);

	//surname
	printf("\tSurname:          ");
	scanf("%s", buffer);
	//validation
	if (surname_validate(buffer)) {
		//error
		end();
		return;
	}
	strcpy(surname, buffer);
	memset(buffer, 0, 255);

	//year
	printf("\tYear (1900-2020): ");
	scanf("%s", buffer);
	//validation
	if (year_validate(buffer)) {
		//error
		end();
		return;
	}
	year = (int)atoi(buffer);

	if (STACK_push(DATA_new(surname, (SPECS)spec, year))) printf("\n\tElement pushed into stack !\n\t");//komunikat
	else printf("\n\tError"); //error
	end();
}
void pop() {
	system("cls");
	STACK_pop(DATA_free);
	end();
}
void clear() {
	system("cls");
	if (STACK_free(DATA_free)) {
		printf("\n\tStack cleared");
	}
	end();
}
void show_top() {
	system("cls");
	printf("\n\tFIRST ELEMENT OF STACK\n");
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

	printf("\n\tSEARCHING BY SURNAME");
	printf("\n\ttype surname: ");
	scanf("%s", temp);

	STACK_find_surname(temp, DATA_compare_surname, DATA_show);
	end();
}
void save() {
	system("cls");

	char buffer[255] = "\0";
	char ext[5] = ".bin";

	printf("\n\tFile name (without extension): ");
	scanf("%s", buffer);
	strncat(buffer, ext, 4);

	FILE *f = fopen(buffer, "wb");
	STACK_save(f, DATA_save);
	fclose(f);
	printf("\n\tStack saved to file %s",buffer);//comm
	end();
}
void load() {
	system("cls");

	char buffer[255] = "\0";
	char ext[5] = ".bin";

	printf("\n\tFile name (without extension): ");
	scanf("%s", buffer);
	strncat(buffer, ext, 4);
	
	FILE *f = fopen(buffer, "rb+");
	STACK_load(f, DATA_load);
	fclose(f);
	printf("\n\tStack succesfully loaded from file %s", buffer);//comm
	end();
}

//menu
void show_menu() {
	system("cls");
	printf("\n\tChoose option\n");
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
			printf("\n\tError reading a surname\n");//error
			return true;
		}
	}
	return false;
}
bool spec_validate(char *buffer) {
	if (strlen(buffer) == 1) {
		if (buffer[0] == '0') return false;
		else if (buffer[0] == '1' || buffer[0] == '2') return false;
		else {
			printf("\n\tError reading a specialization"); //error
			return true;
		}
	}
	printf("\n\tError reading a specialization"); //error
	return true;
}
bool year_validate(char *buffer) {
	if (strlen(buffer) == 4) {
		for (int i = 0; i < 4; i++) {
			if (isdigit(buffer[i]) == 0) {
				printf("\n\tError reading a year"); //error
				return true;
			}
			else continue;
		}
		int year = (int)atoi(buffer);
		if (year > 1899 && year < 2021) return false;
	}
	printf("\n\tError reading a year");	//error
	return true;
}
