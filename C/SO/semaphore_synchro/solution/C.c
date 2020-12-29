
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
      printf("Blad ftok (C)\n");
      exit(2);
   }

   semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
   pidNr = getpid();

   waitSemafor(semID, 1, 0);

   //zad 1
   printf("C) ZAD 1\n");
   fflush(stdout);
   sleep(2);

   signalSemafor(semID, 2);

   //zad 2
   printf("C) ZAD 2\n");
   fflush(stdout);
   sleep(4);

   //zad 3
   waitSemafor(semID, 3, 0);
   printf("C) ZAD 3\n");
   fflush(stdout);
   sleep(1);
}
