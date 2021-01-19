#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include "operacje.h"

void initFilozof(int id, char *imie, int lewyWidelec, int prawyWidelec)
{
   char arg2[20], arg3[20], arg4[20];
   snprintf(arg2, sizeof(arg2), "%d", lewyWidelec);
   snprintf(arg3, sizeof(arg3), "%d", prawyWidelec);
   snprintf(arg4, sizeof(arg4), "%d", id);
   switch (fork())
   {
   case -1:
      perror("Blad fork (mainprog)");
      exit(2);
   case 0:
      execl("./filo", "filo", imie, arg2, arg3, arg4, (char *)NULL);
      fprintf(stderr, "Blad execl(main)\n");
   }
}

int main()
{
   key_t kluczSemafor;
   key_t kluczm;

   int shmID; //id pamieci dzielonej
   int semID; //id semaforow
   int i;

   //klucze
   if ((kluczSemafor = ftok(".", 'A')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }
   if ((kluczm = ftok(".", 'B')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   semID = alokujSemafor(kluczSemafor, 6, IPC_CREAT | IPC_EXCL | 0666);
   if ((shmID = shmget(kluczm, 5 * sizeof(int), IPC_CREAT | IPC_EXCL | 0666)) == -1)
   {
      printf("Blad shmget (main)\n");
      exit(1);
   }

   for (i = 0; i < 6; i++)
      inicjalizujSemafor(semID, i, 1);

   //tworzymy filozofow
   initFilozof(0, "Arystoteles", 1, 0);
   initFilozof(1, "Platon", 2, 1);
   initFilozof(2, "Sokrates", 3, 2);
   initFilozof(3, "Kartezjusz", 4, 3);
   //widelce na odwrót - beda podnoszone w odwrotnej kolejnosci
   initFilozof(4, "Cyceron", 4, 0);

   for (int i = 0; i < 5; i++)
   {
      wait(NULL);
   }

   //zwalnianie pamieci
   shmctl(shmID, IPC_RMID, NULL);
   zwolnijSemafor(semID, 6);
   printf("MAIN: Koniec.\n");
}
