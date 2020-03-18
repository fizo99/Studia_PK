#include "data_validate.h"

bool surname_validate(char *buffer) {
	int length = strlen(buffer);
	int i = 0;
	while (i < length) {
		if ((buffer[i] > 64 && buffer[i] < 91) || (buffer[i] > 96 && buffer[i] < 123)) {
			i++;
			continue;
		}
		else {
			printf("\tBlad wczytywania nazwiska\n");
			return true;
		}
	}
	return false;
}
bool spec_validate(char *buffer) {
	if (strlen(buffer)==1) {
		if (buffer[0] == '0') return false;
		else if (buffer[0] == '1' || buffer[0] == '2') return false;
		else {
			printf("\n\tBlad wczytywania kierunku");
			return true;
		}
	}
	printf("\n\tBlad wczytywania kierunku");
	return true;
}
bool year_validate(char *buffer) {
	if (strlen(buffer) == 4) {
		for (int i = 0; i < 4; i++) {
			if (isdigit(buffer[i]) == 0) {
				printf("\n\tBlad wczytywania roku");
				return true;
			}
			else continue;
		}
		int year = (int)atoi(buffer);
		if (year > 1899 && year < 2021) return false;
	}
	printf("\n\tBlad wczytywania roku");
	return true;
}
