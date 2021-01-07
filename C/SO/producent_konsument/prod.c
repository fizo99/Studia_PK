#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>


struct bufor{
	long mtype;
        int mvalue;
};

int *pam;

#define MAX 10
#define MAX2 12
#define PELNY 2
#define PUSTY 1
#define odczyt pam[MAX]
#define zapis pam[MAX+1]
int main()
{
   key_t klucz, kluczm;
   int msgID;
   int shmID;
   int i; // to, co ma trafic do bufora
   time_t czas;
   struct bufor komunikat;

   //uzyskanie dostepu do kolejki komunikatow
   if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }
   msgID = msgget(klucz,IPC_CREAT|0666); 

   //uzyskanie dostepu do pamieci dzielonej
   if ( (kluczm = ftok(".", 'B')) == -1 ){ 
        printf("Blad ftok (main)\n");
        exit(1);
   }

   shmID=shmget(kluczm, MAX2*sizeof(int), IPC_CREAT|0666);
   if(shmID == -1){
        printf("blad shmget\n");
        exit(1);
   }

   //wysylanie/odbieranie odpowiednich komunikatow 
   if (msgrcv(msgID,&komunikat,sizeof(komunikat.mvalue),komunikat.mtype,0) == -1 )
   {
           printf("blad msgrcv\n");
           exit(1);
   }
   fprintf(stderr,"producent-------------------------------- %d\n",komunikat.mtype);


   //przylaczenie pamieci dzielonej
   pam = (int*) shmat(shmID,NULL,0);
   if(pam == -1){
           printf("blad shmat\n");
           exit(1);
   }
   printf("%d",zapis);
   pam[zapis] = (int)getpid();
   zapis += 1;

   if(shmdt(pam) == -1){
           printf("blad schmdt");
           exit(1);
   }
//operacje na pamieci dzielonej w sekcji krytycznej -- semafory
    
    //zapis = zapis + 1;

//produkcja - dodanie rekordu do puli buforow liczby int  pod indeks - zapis  -- getp$
//np. z wykorzystaniem: ---  time(&czas);
//modyfikacja indeksu do zapisu


}


