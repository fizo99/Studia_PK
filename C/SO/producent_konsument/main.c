#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include "operacje.h"

#define P 50     // liczba procesow prod i kons
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
   key_t klucz;        //klucz do kolejki komunikatow
   key_t kluczm;       //klucz do pamieci dzielonej
   key_t kluczSemafor; //klucz do semaforow

   int msgID; //id kolejki kom.
   int shmID; //id pamieci dzielonej
   int semID; //id semaforow

   int i;
   struct bufor komunikat;

   //stworzenie klucza kolejki komunikatow
   if ((klucz = ftok(".", 'A')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   //stworzenie kolejki komunikatow
   msgID = msgget(klucz, IPC_CREAT | IPC_EXCL | 0666); //tworzenie kk

   if (msgID == -1)
   {
      printf("blad kolejki komunikatow(main)\n");
      exit(1);
   }

   //stworzenie klucza do pamieci dzielonej
   if ((kluczm = ftok(".", 'B')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   };
   //stworzenie pamieci dzielonej
   shmID = shmget(kluczm, MAX2 * sizeof(int), IPC_CREAT | IPC_EXCL | 0666);

   //stworzenie klucza semafora
   if ((kluczSemafor = ftok(".", 'C')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }
   //tworzenie semafora
   semID = alokujSemafor(kluczSemafor, 1, IPC_CREAT | IPC_EXCL | 0666);
   //inicjacja zerem
   inicjalizujSemafor(semID, 0, 1); // inicjalizujemy zerami

   komunikat.mtype = PUSTY; //inicjujemy kolejke komunikatow komunikatami pustymi (1)
   komunikat.mvalue = 0;    //wartosc dowolna

   //wysylamy MAX pustych komunikatow do kolejki
   for (i = 0; i < MAX; i++)
   {
      if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1)
      {
         printf("blad wyslania kom. pustego\n");
         exit(1);
      };
      printf("wyslany pusty komunikat %d\n", i);
   }

   //tworzymy producentow
   for (i = 0; i < P; i++)
   {
      switch (fork())
      {
      case -1:
         perror("Blad fork (mainprog)");
         exit(2);
      case 0:
         execl("./prod", "prod", NULL);
      }

   }
   //tworzymy konsumentow
   for (i = 0; i < P; i++)
   {
      switch (fork())
      {
      case -1:

         printf("Blad fork (mainprog)\n");
         exit(2);
      case 0:
         execl("./kons", "kons", NULL);
      }
   }


   //czekamy na zakonczenie procesow konsumentow i producentow
   for (i = 0; i < 2 * P; i++)
      wait(NULL);

   //zwalnianie zasobow
   zwolnijSemafor(semID, 1);
   msgctl(msgID, IPC_RMID, NULL);
   shmctl(shmID, IPC_RMID, NULL);
   printf("MAIN: Koniec.\n");


      /*
if (fork()==0)
            execl("./prod","prod", NULL);
else
            execl("./kons","kons",NULL);
*/
}
