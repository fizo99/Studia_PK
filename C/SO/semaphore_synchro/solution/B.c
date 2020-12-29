
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
      printf("Blad ftok (B)\n");
      exit(2);
   }

   semID = alokujSemafor(klucz, N, IPC_CREAT | 0666);
   pidNr = getpid();

   waitSemafor(semID, 0, 0);

   //zad 1
   printf("B) ZAD 1\n");
   fflush(stdout);
   sleep(5);

   //zad 2
   printf("B) ZAD 2\n");
   fflush(stdout);
   sleep(3);

   signalSemafor(semID, 3);

   //zad 3
   printf("B) ZAD 3\n");
   fflush(stdout);
   sleep(0);
   
}

