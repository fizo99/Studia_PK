#include <stdio.h>
#include "operacje.h"
#include <sys/types.h>
#include <unistd.h>

int main()
{
   key_t klucz;
   int semID;
   int N = 3;
   FILE *fp;
   pid_t pidNr;

   if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (A)\n");
      exit(2);
   }

   semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
   pidNr = getpid();

   //zad 1
   printf("A) ZAD 1\n");
   fflush(stdout);
   sleep(1);
   
   signalSemafor(semID, 0);
   signalSemafor(semID, 1);
   waitSemafor(semID, 2, 0);

   //zad 2
   printf("A) ZAD 2\n");
   fflush(stdout);
   sleep(2);

   //zad 3
   printf("A) ZAD 3\n");
   fflush(stdout);
   sleep(1);
}

