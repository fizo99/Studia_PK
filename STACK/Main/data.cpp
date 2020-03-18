// struktura danych
//		[] zapis / odczyt obiektu na / z dysku
//		[*] wyprowadzenie na monitor
//		[*] inicjowanie obiektu
//		[*] zwolnienie pamieci
//		[] funkcja porownujaca wartosci obiektow


#include "data.h"
#pragma warning (disable : 4996)

void *DATA_new(char *surname, SPECS spec, int year) {
	//size_t sur_size = _msize(surname);
	DATA *temp = (DATA *)malloc(sizeof(DATA));
	temp->surname = (char *)malloc(10 * sizeof(char));

	if (temp != NULL) {
		temp->spec = spec;
		temp->year = year;
		strcpy(temp->surname, (const char*)surname);
	}
	return (void *)temp;
}
int  DATA_free(void *ptr) {
	if (ptr != NULL) {
		free(ptr);
		return 1;
	}
	else {
		return 0;
	}
}
void DATA_show(void *ptr) {
	if (ptr != NULL) {
		DATA *temp = (DATA *)ptr;
		printf("\tNazwisko: %s\n", temp->surname);
		printf("\tRok:      %d\n", temp->year);
		switch (temp->spec) {
		case INFORMATYKA:
			printf("\tKierunek: Informatyka\n");
			break;
		case MATEMATYKA:
			printf("\tKierunek: Matematyka\n");
			break;
		case FIZYKA:
			printf("\tKierunek: Fizyka\n");
			break;
		}
	}
}
int  DATA_compare_surname(char *test_surname, void *ptr1) {
	DATA *temp = (DATA*)ptr1;
	if (!strcmp(test_surname, temp->surname)) return 1;
	else return 0;
}
void DATA_save(FILE *f, void *ptr) {
	DATA *temp = (DATA*)ptr;
	//ZAPIS WSZYSTKICH DANYCH JAKO CIAGI ZNAKOWE(jedna linia zakonczona '\n')
	//format NAZWISKOROKSPECIALIZACJA\n
	//nazwisko
	fwrite(temp->surname, sizeof(char), strlen(temp->surname), f);
	//fwrite("\n", sizeof(char), 1, f);			//endline

	//rok
	char temp_table[5];
	sprintf(temp_table, "%d", temp->year);
	fwrite(temp_table, sizeof(char), strlen(temp_table), f);
	//fwrite("\n", sizeof(char), 1, f); //endline
	//fwrite(&temp->year, sizeof(int), 1, f);
	//fwrite("\n", sizeof(char), 1, f); //endline


	//kierunek
	//char *spec = (char*)malloc(15 * sizeof(char));
	char spec[2];
	sprintf(spec, "%d", temp->spec);
	//switch (temp->spec) {
	//	case 0:
	//		strcpy(spec, "Informatyka");
	//		break;
	//	case 1:
	//		strcpy(spec, "Matematyka");
	//		break;
	//	case 2:
	//		strcpy(spec, "Fizyka");
	//		break;
	//}
	fwrite(spec, sizeof(char), strlen(spec), f);
	fwrite("\n", sizeof(char), 1, f); //endline
	//free(spec);

	//fwrite(&temp->spec, sizeof(int), 1, f);
	//fwrite("\n", sizeof(char), 1, f); //endline

	//dodaj na koncu kazdej linii ile byte to zajelo (przy czytaniu zliczaj)
	//TOTAL MEMORY WRITTEN = size of surname + 2 ints(8 bytes) + 1byte(endline)
}
void *DATA_load(FILE *f, char *buffer) {
	//funkcja bedzie zwracala tablice z wczytanymi strukturami
	//wielkosc tablicy = wielkosc struktury * (liczba linii w pliku + 1)
	//DATA *tab = (DATA*)malloc(sizeof(DATA));
	//for (int i = 0; i < num_lines(f); i++) {
	//	tab[i] = (DATA*)malloc(sizeof(DATA));
	//}

	int len;
	int k = 0;
	len = strlen(buffer);
	char specbuff = '\0';
	char yearbuff[5] = "\0";
	char surnamebuff[255] = "\0";

	specbuff = buffer[len - 1];
	int j = 0;
	for (int i = (len - 5); i < (len - 1); i++) {
		yearbuff[j] = buffer[i];
		j++;
	}
	for (int i = 0; i < len - 5; i++) {
		surnamebuff[i] = buffer[i];
	}
	int spec;
	int year;
	sscanf(&specbuff, "%d", &spec);
	sscanf(yearbuff, "%d", &year);
	return DATA_new(surnamebuff, (SPECS)spec, year);

}

int num_lines(FILE *f) {
	int num = 0;
	char buffer[1024];
	while (fscanf(f, "%s", buffer) != EOF) {
		num++;
	}
	return num;
}
//DATA *temp = (DATA*)ptr;
//FILE *f = fopen("cos.bin", "wb");
//if (!f) {
//	printf("\n\tBlad wczytywania pliku");
//	return;
//}
//printf("%d", fwrite(&temp->year, sizeof(temp->year), 1, f));
//printf("%d", fwrite(temp->surname, 20, 1, f));
//fclose(f);
//char spec[12];
//switch (temp->spec) {
//	case 0:
//		sprintf(spec, "%s", "Informatyka");
//		break;
//	case 1:
//		sprintf(spec, "%s", "Matematyka");
//		break;
//	case 2:
//		sprintf(spec, "%s", "Fizyka");
//		break;
//}

//char year[5];
//sprintf(year, "%d", temp->year);

//fwrite(spec, sizeof(char), sizeof(spec), f);
//fwrite("\n", sizeof(char), 1, f);
//fwrite(temp->surname, sizeof(char), strlen(temp->surname), f);
//fwrite("\n", sizeof(char), 1, f);
//fwrite(year, sizeof(char), sizeof(year), f);
//fclose(f);

//TODO
//char ** DATA_save(void *ptr) {
//	DATA *temp = (DATA*)ptr;
//	char **ret = (char**)malloc(3 * sizeof(char*));//return value
//	ret[0] = (char*)malloc(15 * sizeof(char));	   //space for specialization
//	ret[1] = (char*)malloc(4 * sizeof(char));	   //space for year
//	ret[2] = (char*)malloc(_msize(temp->surname)); //space for surname
//	//char spec[15];		//buffer for specialization
//	//char year[4];		//buffer for year
//	//convert enum to string
//	strcpy(ret[2], temp->surname);
//	switch (temp->spec) {
//		case 0:
//			strcpy(ret[0], "Informatyka");
//			break;
//		case 1:
//			strcpy(ret[0], "Matematyka");
//			break;
//		case 2:
//			strcpy(ret[0], "Fizyka");
//			break;
//	}
//	//convert int to string
//	int tempyear = temp->year;
//	for (int i = 3; i >= 0; i--) {
//		ret[1][i] = tempyear % 10;
//		tempyear = (int)tempyear/10;
//	}
//
//	return ret;
//	//char surname[255];	//buffer for surname
//	//char year[4];		//buffer for year
//	//sprintf(surname, "%s", temp->surname);
//	//sprintf(surname, "%s", temp->surname);
//}



//int DATA_compare_spec(void *test_spec, void *ptr1) {
//	DATA *temp = (DATA*)ptr1;
//	if (temp->spec == *(int*)test_spec) return 1;
//	else return 0;
//}