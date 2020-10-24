// Kolokw_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include "memory.h"

MY_CAR * fun_create_array(int dim);
void fun_fill_array(MY_CAR *tab);
MY_CAR * fun_add(int num, MY_CAR *t1, MY_CAR *t2);
void fun_print_tab(MY_CAR *t, char *title);
void fun_free(MY_CAR **t);


int main()
{
	int dim_1, dim_2, num;

	printf("Podaj rozmiar pierwszej tablicy oraz drugiej\n");
	scanf_s("%d%d", &dim_1, &dim_2);

	MY_CAR *tab_1 = fun_create_array(dim_1);
	MY_CAR *tab_2 = fun_create_array(dim_2);
	fun_fill_array(tab_1);
	fun_fill_array(tab_2);

	fun_print_tab(tab_1, "tab_1");
	fun_print_tab(tab_2, "tab_2");

	printf("Podaj numer elementu pierwszej tablicy, przed ktorym trzeba dodac druga tablice\n");
	scanf_s("%d", &num);

	tab_1 = fun_add(num, tab_1, tab_2);
	fun_print_tab(tab_1, "tab_1");

	fun_free(&tab_1);
	fun_free(&tab_2);

	system("pause");

    return 0;
}

MY_CAR * fun_create_array(int dim)
{
	MY_CAR *ptr = (MY_CAR *)malloc(dim * sizeof(MY_CAR));
	if (!ptr)
		return NULL;
	memset(ptr, 0, dim * sizeof(MY_CAR));
	return ptr;
}

void fun_free(MY_CAR **t)
{
	MY_CAR *ptr = *t;
	if (ptr)
	{
		free(ptr);
		*t = NULL;
	}
}

void fun_fill_array(MY_CAR *tab)
{
	size_t i, j;
	char symb = 'a';
	int start_numb = 1000;
	size_t dim = _msize(tab) / sizeof(MY_CAR);

	for (i = 0; i < dim; ++i)
	{
		tab[i].year = start_numb;

		for (j = 0; j < 5; ++j)
			tab[i].nazwa[j] = symb;
		tab[i].nazwa[j] = '\n';

		symb++;
		start_numb += 100;
	}
}

MY_CAR * fun_add(int num, MY_CAR *t1, MY_CAR *t2)
{
	size_t num_elem_in_1 = _msize(t1) / sizeof(MY_CAR);
	size_t num_elem_in_2 = _msize(t2) / sizeof(MY_CAR);

	t1 = (MY_CAR *)realloc(t1, (num_elem_in_1 + num_elem_in_2) * sizeof(MY_CAR));
	if (!t1)
		return NULL;

	memmove(t1 + num_elem_in_2 + num, t1 + num, (num_elem_in_1 - num) * sizeof(MY_CAR));
	memcpy(t1 + num, t2, num_elem_in_2 * sizeof(MY_CAR));

	return t1;
}

void fun_print_tab(MY_CAR *t, char *title)
{
	printf("%s\n", title);
	size_t dim = _msize(t) / sizeof(MY_CAR);
	for (size_t i = 0; i < dim; ++i)
	{
		printf("i = %d   nazwa = %s   rok = %d\n", i, t[i].nazwa, t[i].year);
	}
}

