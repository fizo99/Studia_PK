#include <stdio.h>
#include<unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "operacje.h"
#include <sys/wait.h>


#define P 3    // ilosc procesow

int main()
{
   key_t klucz;
   int semID;
   int N = 5;  // ilosc semaforow
   char *procesy[P] = {"A", "B", "C"};
   char sciezka[5];
   int i;

   if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   // tworzymy N = 5 semafory
   semID = alokujSemafor(klucz, N, IPC_CREAT | IPC_EXCL | 0666);
   for (i = 0; i < N; i++)
      inicjalizujSemafor(semID, i, 0); // inicjalizujemy zerami

   printf("Semafory gotowe!\n");
   fflush(stdout);

   for (i = 0; i < P; i++)
      switch (fork())
      {
       	 case -1:
            perror("Blad fork (mainprog)");
            zwolnijSemafor(semID, N);
            exit(2);
         case 0:
            sciezka[0] = '\0';
            strcat(sciezka, "./");
            strcat(sciezka, procesy[i]);
            execl(sciezka, procesy[i], NULL);
      }

   for (i = 0; i < P; i++)
      wait( (int *)NULL );

   zwolnijSemafor(semID, N);
   printf("MAIN: Koniec.\n");
}







