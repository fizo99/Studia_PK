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

   printf("Dziala zadanie t21\n");
   fflush(stdout);
   fp = fopen("wynik.txt", "a");
   fprintf(fp,"Sekcja t21 procesu o PID=%d\n", pidNr);
   fclose(fp);
   sleep(2);
   signalSemafor(semID, 1);
   waitSemafor(semID, 2, 0);
   printf("Dziala zadanie t22\n");
   fflush(stdout);
   fp = fopen("wynik.txt","a");
   fprintf(fp,"Sekcja t22 procesu o PID=%d\n",pidNr);
   fclose(fp);\
   sleep(2);
}



