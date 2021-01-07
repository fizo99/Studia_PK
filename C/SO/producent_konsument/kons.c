#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>


struct bufor{
	int mtype;
        int mvalue;
};

int *pam;
#define MAX2 12
#define MAX 10
#define PELNY 2
#define PUSTY 1
#define zapis pam[MAX+1]
#define odczyt pam[MAX]

int main()
{
   key_t klucz, kluczm;
   int msgID, shmID;
   int i;
   struct bufor komunikat;

   printf("konsument--------------------------------\n");


//uzyskanie dosepu do kolejki komunikatow

//uzyskanie dosepu do pamieci dzielonej


//przylaczenie pam. dzielonej-- shmat


//sekcja krytyczna -- semafor -- operacje na pamięci dzielonej
//odbieranie/wysylanie odpowiednich komunikatow +
// odczyt z bufora  elementu o  indeksie odczyt (pam. dzielona)
//modyfikacja indeksu do odczytu
//msgrcv -- odbior komunikatu


}
