#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include "operacje.h"

struct bufor
{
        long mtype;
        long mvalue;
};


int *pam;
#define MAX2 12
#define MAX 10
#define PELNY 2
#define PUSTY 1
#define zapis pam[MAX + 1]
#define odczyt pam[MAX]

int main()
{
        // key_t klucz, kluczm;
        // int msgID, shmID;
        // int i;
        // struct bufor komunikat;

        //printf("konsument--------------------------------\n");


        key_t klucz, kluczm, kluczSemafor;
        int msgID;
        int shmID;
        int semID;
        
        int i; // to, co ma trafic do bufora
        struct bufor komunikat;

        //uzyskanie dostepu do kolejki komunikatow
        if ((klucz = ftok(".", 'A')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }
        msgID = msgget(klucz, IPC_CREAT | 0666);

        //uzyskanie dostepu do pamieci dzielonej
        if ((kluczm = ftok(".", 'B')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }

        shmID = shmget(kluczm, MAX2 * sizeof(int), IPC_CREAT | 0666);
        if (shmID == -1)
        {
                printf("blad shmget\n");
                exit(1);
        }


        //wysylanie/odbieranie odpowiednich komunikatow
        komunikat.mtype = PELNY;
        if (msgrcv(msgID, &komunikat, sizeof(komunikat.mvalue), komunikat.mtype, 0) == -1)
        {
                printf("blad msgrcv\n");
                exit(1);
        }
        //printf("KONSUMENT PID: %d  komunikat odebrany: %d\n",getpid(),komunikat.mtype);


        //printf("KONSUMENT PID: %d  komunikat wyslany: %d\n",getpid(),komunikat.mtype);

        
        if ( (kluczSemafor = ftok(".", 'C')) == -1 )
        {
                printf("Blad ftok (C)\n");
                exit(2);
        }

        semID = alokujSemafor(kluczSemafor, 2, IPC_CREAT | 0666);
   
        
        // if(waitSemafor(semID, 1, 0) == -1){
        //         fprintf(stderr,"blad wait semafor");
        // }

        // if(waitSemafor(semID, 1,0) == -1){
        //         fprintf(stderr,"blad signal semafor");
        // }

        // if(signalSemafor(semID, 1) == -1){
        //         fprintf(stderr,"blad signal semafor");
        // }

        //zajmij semafor
        struct sembuf operacje={0,-1,0};
        semop(semID,&operacje,1);

        pam = (int *)shmat(shmID, NULL, 0);
        if (*pam == -1)
        {
                printf("blad shmat\n");
                exit(1);
        }
        fprintf(stderr,"KONSUMENT odczytID: %d, odczytany pid: %d\n",odczyt,pam[odczyt]);
        //printf("Odczytano %d", pam[odczyt]);
        odczyt += 1;

        //zwolnij semafor
        struct sembuf op2={0,1,0};
        semop(semID,&op2,1);



        komunikat.mtype = PUSTY;
        if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1) //wyslanie komun$
        {
                printf("blad wyslania kom. pustego\n");
                exit(1);
        };
        // //




        // if (shmdt(pam) == -1)
        // {
        //         printf("blad schmdt");
        //         exit(1);
        // }

        //uzyskanie dosepu do kolejki komunikatow

        //uzyskanie dosepu do pamieci dzielonej

        //przylaczenie pam. dzielonej-- shmat

        //sekcja krytyczna -- semafor -- operacje na pamięci dzielonej
        //odbieranie/wysylanie odpowiednich komunikatow +
        // odczyt z bufora  elementu o  indeksie odczyt (pam. dzielona)
        //modyfikacja indeksu do odczytu
        //msgrcv -- odbior komunikatu
}
