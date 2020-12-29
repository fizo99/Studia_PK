#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>

int alokujSemafor(key_t klucz, int number, int flagi);
void inicjalizujSemafor(int semID, int number, int val);
int zwolnijSemafor(int semID, int number);
int waitSemafor(int semID, int number, int flags);
void signalSemafor(int semID, int number);
int valueSemafor(int semID, int number);
//double getRand(int *nseed);
