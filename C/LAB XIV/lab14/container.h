#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

typedef void(*PTR_FUN_FREE)(void *pDat);
typedef void(*PTR_FUN_PRINT)(void *pDat);
typedef void* (*PTR_FUN_CREATE_COPY)(void*pDat); //pointer to function to make copy of data object.





struct TAB_DYN {
	void *pDat;
	PTR_FUN_FREE pFunFree;
	PTR_FUN_PRINT pFunPrint;
	PTR_FUN_CREATE_COPY pFunCreateCopy;
	static int last;
	//PTR_FUN_NEW_DATA pFunNewData;
};

TAB_DYN *init(int size);
void append(TAB_DYN *tab, void *ptr, PTR_FUN_FREE pFunFree, PTR_FUN_PRINT pFunPrint, PTR_FUN_CREATE_COPY cpy);
void show(TAB_DYN *tab);
void free_tab(TAB_DYN *tab);
void assign(TAB_DYN *tab, int i, int j);
TAB_DYN *make_copy(TAB_DYN *tab);