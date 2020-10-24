#include "container.h"


int TAB_DYN::last = 0;

//stworz tablice size-elementow¹
TAB_DYN *init(int size) {
	TAB_DYN *tab = (TAB_DYN*)malloc(size*sizeof(TAB_DYN));
	if (!tab)
		printf("BLAD ALOKACJI");
	return tab;
}

//dodaj element na pierwszej wolnej pozycji
void append(TAB_DYN *tab,void *ptr, PTR_FUN_FREE pFunFree, PTR_FUN_PRINT pFunPrint, PTR_FUN_CREATE_COPY cpy) {
	size_t size = _msize(tab) / sizeof(TAB_DYN);

	//printf("%d %d", size, (tab->last));
	if ((int)size < tab->last + 1) {
		printf("\nERROR: TAB is full\n");
		return;
	}
	//if ((int)size < tab->last + 1) {
	//	TAB_DYN *newTab = (TAB_DYN*)realloc((void*)tab, (size_t)(2 * size * sizeof(TAB_DYN)));
	//	TAB_DYN *temp = tab;
	//	tab = newTab;
	//	free_tab(temp);
	//}

	tab[tab->last].pDat = ptr;
	tab[tab->last].pFunFree = pFunFree;
	tab[tab->last].pFunPrint = pFunPrint;
	tab[tab->last].pFunCreateCopy = cpy;
	tab->last++;

}

//wyprowadz tablice na monitor
void show(TAB_DYN *tab) {
	for (int i = 0; i < tab->last; i++) 
		tab[i].pFunPrint(tab[i].pDat);
}

//zwolnij pamiec
void free_tab(TAB_DYN *tab) {
	for (int i = 0; i < tab->last; i++)
		tab[i].pFunFree(tab[i].pDat);
	free(tab);
}

void assign(TAB_DYN *tab, int i, int j) {
	if (!tab) {
		printf("\nERROR: Pusty wskaznik\n");
		return;
	}


	if (i >= tab->last || j >= tab->last || i == j) {

		printf("\nERROR: niepoprawne indeksy\n");
		return;
	}

	tab[j].pFunFree(tab[j].pDat);
	tab[j].pDat = tab[i].pFunCreateCopy(tab[i].pDat);
	tab[j].pFunCreateCopy = tab[i].pFunCreateCopy;
	tab[j].pFunFree = tab[i].pFunFree;
	tab[j].pFunPrint = tab[i].pFunPrint;
}

TAB_DYN *make_copy(TAB_DYN *tab) {
	size_t size;
	TAB_DYN *newTab = NULL;
	if (tab) {
		size_t size = _msize(tab) / sizeof(*tab);
		newTab = (TAB_DYN*)malloc(size * sizeof(TAB_DYN));
	}
	else {
		printf("blad przy robieniu kopii");
		return NULL;
	}


	for (int i = 0; i < tab->last; i++) {
		newTab[i].pDat = tab[i].pFunCreateCopy(tab[i].pDat);
		newTab[i].pFunCreateCopy = tab[i].pFunCreateCopy;
		newTab[i].pFunFree = tab[i].pFunFree;
		newTab[i].pFunPrint = tab[i].pFunPrint;
	}

	return newTab;
}
