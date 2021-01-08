#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include "operacje.h"

#define P 3     // liczba procesow prod i kons
#define MAX 10  //rozmiar buforu
#define MAX2 12 // + dwa pola na indeksy zapis/odczyt
#define PUSTY 1 //typ komunikatu
#define PELNY 2 //typ komunikatu

//struktura komunikatu
struct bufor
{
   long mtype;
   long mvalue;
};

int main()
{
   key_t klucz, kluczm, kluczSemafor; //klucze do kk i pam. dz.
   int msgID;           //id kolejki kom.
   int shmID;           //id pamieci dzielonej
   int semID;           //id semafora do pamiedzi dzielonej

   int i;
   struct bufor komunikat;

   if ((klucz = ftok(".", 'A')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   msgID = msgget(klucz, IPC_CREAT | IPC_EXCL | 0666); //tworzenie kk
   //msgID=msgget(klucz,IPC_CREAT|0666); //tworzenie kk
   if (msgID == -1)
   {
      printf("blad kolejki komunikatow\n");
      exit(1);
   }
   printf("%d", msgID);

   kluczm = ftok(".", 'B');
   shmID = shmget(kluczm, MAX2 * sizeof(int), IPC_CREAT | IPC_EXCL | 0666); //tworzenie pam. d$
   //shmID=shmget(kluczm, MAX2*sizeof(int), IPC_CREAT|0666);//tworzenie pam. d$
   //shmID=shmget(kluczm, P, IPC_CREAT|IPC_EXCL|0666);//tworzenie pam. d$


   //SEMAFOR
   if ((kluczSemafor = ftok(".", 'C')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }
   semID = alokujSemafor(kluczSemafor, 2, IPC_CREAT | IPC_EXCL | 0666);
   inicjalizujSemafor(semID, 0, 0); // inicjalizujemy zerami
   inicjalizujSemafor(semID, 1, 0); // inicjalizujemy zerami


   komunikat.mtype = PUSTY;
   //   komunikat.mvalue=0;   wazny jest typ komunikatu, tresc - dowolna

   //for(i=0;i<P;i++)
   for (i = 0; i < MAX; i++)
   {
      if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1) //wyslanie komun$
      {
         printf("blad wyslania kom. pustego\n");
         exit(1);
      };
      printf("wyslany pusty komunikat %d\n", i);
   }

   for (i = 0; i < P; i++)
      switch (fork())
      {
      case -1:
         perror("Blad fork (mainprog)");
         exit(2);
      case 0:
         execl("./prod", "prod", NULL);
      }

      for(i=0;i<P;i++)
           switch (fork())
           {
   	case -1:

               printf("Blad fork (mainprog)\n");
               exit(2);
           case 0:
                  	execl("./kons","kons",NULL);
           }

   /*
if (fork()==0)
            execl("./prod","prod", NULL);
else
            execl("./kons","kons",NULL);
*/
   for (i = 0; i < 2*P; i++)
      wait(NULL);

   //zwalnianie zasobow
   zwolnijSemafor(semID, 2);
   //zwolnijSemafor(semID, 1);
   msgctl(msgID, IPC_RMID, NULL);
   shmctl(shmID, IPC_RMID, NULL);
   printf("MAIN: Koniec.\n");
}
