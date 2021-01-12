#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include "operacje.h"

int it = 0;
pid_t pidy[5];

void initFilozof(char *imie, int lewyWidelec, int prawyWidelec)
{
   char arg2[20], arg3[20];
   snprintf(arg2, sizeof(arg2), "%d", lewyWidelec);
   snprintf(arg3, sizeof(arg3), "%d", prawyWidelec);
   switch (fork())
   {
   case -1:
      perror("Blad fork (mainprog)");
      exit(2);
   case 0:
      pidy[it] = getpid();
      it++;
      execl("./filo", "filo", imie, arg2, arg3, (char*)NULL);
      fprintf(stderr,"Blad execl(main)\n");
   }
}

void *myThread(void *vargp){
   int* semID = (int*)vargp;
   //sleep(5);

   while(semctl(*semID,5,GETNCNT,NULL) != 5){
   }

   //fprintf(stderr,"%d",semctl(*semID,5,GETNCNT,NULL));
   //fprintf(stderr,"%d",semctl(*semID,5,GETZCNT,NULL));

   //zwolnienie semafora - POCZATEK UCZTY
   struct sembuf s = {5,1,0};
   int i;
   for(i = 0; i < 5; i++){
      semop(*semID, &s, 1);
   }

   //uczta trwa 10 sekund
   sleep(10);

   struct sembuf s2 = {5,-1,0};
   semop(*semID, &s2, 1);
   //signalSemafor(*semID,5);
   
}

int main()
{
   key_t kluczSemafor; //klucz do semaforow
   pthread_t thread_id;

   int semID; //id semaforow
   int i;

   //stworzenie klucza semafora
   if ((kluczSemafor = ftok(".", 'A')) == -1)
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }
   //tworzenie semafora
   //semafory dla widelcow
   semID = alokujSemafor(kluczSemafor, 6, IPC_CREAT | IPC_EXCL | 0666);
   //inicjacja zerem
   for (i = 0; i < 5; i++)
      inicjalizujSemafor(semID, i, 1);

   //osobny semafor do kontrolowania startu/konca uczty
   inicjalizujSemafor(semID,5,1);
   pthread_create(&thread_id,NULL,myThread,(void*)&semID);

   //zajecie semafora
   struct sembuf s = {5,-1,0};
   semop(semID, &s, 1);
   

   //tworzymy filozofow
   initFilozof("Arystoteles",0,1);
   initFilozof("Platon",1,2);
   initFilozof("Sokrates",2,3);
   initFilozof("Kartezjusz",3,4);
   initFilozof("Cyceron",1,4);

   //signalSemafor(semID,5);
   //pthread_join(thread_id,NULL);

   for(int i = 0; i < 5; i++){
      wait(NULL);
   }

   //sleep(10);

   zwolnijSemafor(semID, 6);
   printf("MAIN: Koniec.\n");
}
