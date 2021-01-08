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

#define MAX 10
#define MAX2 12
#define PELNY 2
#define PUSTY 1
#define odczyt pam[MAX]
#define zapis pam[MAX + 1]
int main()
{
        key_t klucz, kluczm, kluczSemafor;
        int msgID;
        int shmID;
        int semID;
        
        int i; // to, co ma trafic do bufora
        time_t czas;
        struct bufor komunikat;

        //uzyskanie dostepu do kolejki komunikatow
        if ((klucz = ftok(".", 'A')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }
        msgID = msgget(klucz, IPC_CREAT | 0666);

        //wysylanie/odbieranie odpowiednich komunikatow
        komunikat.mtype = PUSTY;
        if (msgrcv(msgID, &komunikat, sizeof(komunikat.mvalue), komunikat.mtype, 0) == -1)
        {
                printf("blad msgrcv\n");
                exit(1);
        }
        //printf("PRODUCENT PID: %d  komunikat odebrany: %d\n",getpid(),komunikat.mtype);

        
        //fprintf(stderr, "producent-------------------------------- %d\n", komunikat.mtype);

        //przylaczenie pamieci dzielonej
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

        if ( (kluczSemafor = ftok(".", 'C')) == -1 )
        {
                printf("Blad ftok (C)\n");
                exit(2);
        }
        semID = alokujSemafor(kluczSemafor, 1, IPC_CREAT | 0666);
        // if(waitSemafor(semID, 0, 0) == -1){
        //         fprintf(stderr,"blad wait semafor");
        // }

        // if(waitSemafor(semID, 0,0) == -1){
        //         fprintf(stderr,"blad signal semafor");
        // }
        // if(signalSemafor(semID, 0) == -1){
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
        //fprintf(stderr,"%d", zapis);
        fprintf(stderr,"PRODUCENT zapisID: %d, pid: %d\n",zapis,getpid());
        pam[zapis] = (int)getpid();
        zapis += 1;

        //zwolnij semafor
        struct sembuf op2={0,1,0};
        semop(semID,&op2,1);

        komunikat.mtype = PELNY;
        if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1) //wyslanie komun$
        {
                printf("blad wyslania kom. pustego\n");
                exit(1);
        };
        

        // komunikat.mtype = PELNY;
        // if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1) //wyslanie komun$
        // {
        //         printf("blad wyslania kom. pustego\n");
        //         exit(1);
        // };
        
        //

        //zapis komunikatu PELNY do kolejki



        // if (shmdt(pam) == -1)
        // {
        //         printf("blad schmdt");
        //         exit(1);
        // }
        //operacje na pamieci dzielonej w sekcji krytycznej -- semafory

        //zapis = zapis + 1;

        //produkcja - dodanie rekordu do puli buforow liczby int  pod indeks - zapis  -- getp$
        //np. z wykorzystaniem: ---  time(&czas);
        //modyfikacja indeksu do zapisu
}
