#include <stdio.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include <unistd.h>
#include <stdlib.h>


#define P 3   // liczba procesow prod i kons
#define MAX 10  //rozmiar buforu
#define MAX2 12 // + dwa pola na indeksy zapis/odczyt
#define PUSTY 1 //typ komunikatu
#define PELNY 2 //typ komunikatu

//struktura komunikatu
struct bufor{
	int mtype;
        int mvalue;
};

int main()
{
   key_t klucz, kluczm;  //klucze do kk i pam. dz.
   int msgID; //id kolejki kom.
   int shmID;   //id pamieci dzielonej

   int i;
   struct bufor komunikat;

   if ( (klucz = ftok(".", 'A')) == -1 )
   {
      printf("Blad ftok (main)\n");
      exit(1);
   }

   msgID=msgget(klucz,IPC_CREAT|IPC_EXCL|0666); //tworzenie kk
   //msgID=msgget(klucz,IPC_CREAT|0666); //tworzenie kk
   if (msgID==-1)
        {printf("blad kolejki komunikatow\n"); exit(1);}
        printf("%d",msgID);

   kluczm=ftok(".",'B');
   shmID=shmget(kluczm, MAX2*sizeof(int), IPC_CREAT|IPC_EXCL|0666);//tworzenie pam. d$
   //shmID=shmget(kluczm, MAX2*sizeof(int), IPC_CREAT|0666);//tworzenie pam. d$
   //shmID=shmget(kluczm, P, IPC_CREAT|IPC_EXCL|0666);//tworzenie pam. d$

   komunikat.mtype=PUSTY;
//   komunikat.mvalue=0;   wazny jest typ komunikatu, tresc - dowolna

    //for(i=0;i<P;i++)
 for(i=0;i<MAX;i++)
 
         {
	if( msgsnd(msgID,&komunikat,sizeof(komunikat.mvalue),0)==-1) //wyslanie komun$
                {
                        printf("blad wyslania kom. pustego\n");
                        exit(1);
                };
           printf("wyslany pusty komunikat %d\n",i);
        }

   for (i = 0; i < P; i++)
      switch (fork())
      {
       	 case -1:
            perror("Blad fork (mainprog)");
            exit(2);
         case 0:
            execl("./prod","prod", NULL);
      }

//    for(i=0;i<P;i++)
//         switch (fork())
//         {
// 	case -1:

//             printf("Blad fork (mainprog)\n");
//             exit(2);
//         case 0:
//                	execl("./kons","kons",NULL);
//         }

/*
if (fork()==0)
            execl("./prod","prod", NULL);
else
            execl("./kons","kons",NULL);
*/
for(i=0;i<P;i++)
   wait(NULL);

//zwalnianie zasobow
   msgctl(msgID,IPC_RMID,NULL);
   shmctl(shmID,IPC_RMID, NULL);
   printf("MAIN: Koniec.\n");
}


