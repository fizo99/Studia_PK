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

   waitSemafor(semID, 0, 0);
   printf("Dziala zadanie t31\n");
   fflush(stdout);
   fp = fopen("wynik.txt", "a");
   fprintf(fp,"Sekcja t31 procesu o PID=%d\n", pidNr);
   fclose(fp);
   sleep(3);
   printf("Dziala zadanie t32\n");
   fflush(stdout);
   fp = fopen("wynik.txt","a");
   fprintf(fp,"Sekcja t32 procesu o PID=%d\n",pidNr);
   fclose(fp);
   sleep(4);

}






