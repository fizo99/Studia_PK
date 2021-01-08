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
        key_t klucz;        //klucz do kolejki komunikatow
        key_t kluczm;       //klucz do pamieci dzielonej
        key_t kluczSemafor; //klucz do semaforow

        int msgID; //id kolejki kom.
        int shmID; //id pamieci dzielonej
        int semID; //id semaforow

        struct bufor komunikat;
        int i;

        /** UZYSKANIE DO ZASOBOW Z MAIN(KOLEJKA,PAMIEC DZIELONA,SEMAFOR) **/
        //utworzenie klucza do kolejki komunikatow
        if ((klucz = ftok(".", 'A')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }
        //uzyskanie identyfikatora kolejki utworzonej w main
        msgID = msgget(klucz, IPC_CREAT | 0666);

        //utworzenie klucza do pamieci dzielonej
        if ((kluczm = ftok(".", 'B')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }
        //uzyskanie identyfikatora pamieci dzielonej utworzonej w main
        if ((shmID = shmget(kluczm, MAX2 * sizeof(int), IPC_CREAT | 0666)) == -1)
        {
                printf("blad shmget\n");
                exit(1);
        }
        //utworzenie klucza semafora utworzonego w main
        if ((kluczSemafor = ftok(".", 'C')) == -1)
        {
                printf("Blad ftok (C)\n");
                exit(1);
        }
        //uzyskanie identyfikatora semafora
        semID = alokujSemafor(kluczSemafor, 1, IPC_CREAT | 0666);
        //przylaczenie pamieci dzielonej
        pam = (int *)shmat(shmID, NULL, 0);
        if (*pam == -1)
        {
                printf("blad shmat\n");
                exit(1);
        }
        /** ------------------------------------------------------ **/

        //odebranie komunikatu pelnego
        if (msgrcv(msgID, &komunikat, sizeof(komunikat.mvalue), PELNY, 0) == -1)
        {
                printf("blad msgrcv\n");
                exit(1);
        }

        //odczyt z pamieci dzielonej
        // SEKCJA KRYTYCZNA

        //zajmij semafor
        //struct sembuf operacje={0,-1,0};
        //semop(semID,&operacje,1);

        waitSemafor(semID,0,0);

        fprintf(stderr, "KONSUMENT odczytID: %d, odczytany pid: %d\n", odczyt, pam[odczyt]);
        odczyt += 1;
        if(odczyt == MAX) odczyt = 0;

        signalSemafor(semID,0);
        //opusc semafor
        //struct sembuf op2={0,1,0};
        //semop(semID,&op2,1);

        // SEKCJA KRYTYCZNA


        //zapis komunikatu pustego
        komunikat.mtype = PUSTY;
        if (msgsnd(msgID, &komunikat, sizeof(komunikat.mvalue), 0) == -1)
        {
                printf("blad wyslania kom. pustego\n");
                exit(1);
        };

        // if(waitSemafor(semID, 1, 0) == -1){
        //         fprintf(stderr,"blad wait semafor");
        // }

        // if(waitSemafor(semID, 1,0) == -1){
        //         fprintf(stderr,"blad signal semafor");
        // }

        // if(signalSemafor(semID, 1) == -1){
        //         fprintf(stderr,"blad signal semafor");
        // }

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
