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
   printf("Dziala zadanie t11\n");
   fflush(stdout);
   fp = fopen("wynik.txt","a");
   fprintf(fp,"Sekcja t11 procesu o PID=%d\n",pidNr);
   fclose(fp);
   sleep(1);

   signalSemafor(semID, 0);

   waitSemafor(semID, 1, 0);

   printf("Dziala zadanie t12\n");
   fflush(stdout);
   fp = fopen("wynik.txt","a");
   fprintf(fp,"Sekcja t12 procesu o PID=%d\n",pidNr);
   fclose(fp);
   sleep(2);
   signalSemafor(semID, 2);
}


