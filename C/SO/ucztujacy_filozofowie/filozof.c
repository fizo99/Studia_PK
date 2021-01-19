#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include "operacje.h"

#define CYKLE 5
#define CZAS_JEDZENIA 4
#define CZAS_MYSLENIA 2
#define SEMAFOR_SHM 5

int *pam;

void request(int semID, int lewyWidelec, int prawyWidelec, int id)
{
        //strefa krytyczna - pamiec dzielona
        waitSemafor(semID, SEMAFOR_SHM, 0);

        pam[lewyWidelec] = id;
        pam[prawyWidelec] = id;

        signalSemafor(semID, SEMAFOR_SHM);
}
void release(int semID, int lewyWidelec, int prawyWidelec)
{
        //strefa krytyczna - pamiec dzielona
        waitSemafor(semID, SEMAFOR_SHM, 0);

        pam[lewyWidelec] = 1234;
        pam[prawyWidelec] = 1234;

        signalSemafor(semID, SEMAFOR_SHM);
}

void jedz(int id, char *imie, int semID, int lewyWidelec, int prawyWidelec)
{
        waitSemafor(semID, lewyWidelec, 0);
        waitSemafor(semID, prawyWidelec, 0);

        request(semID, lewyWidelec, prawyWidelec, id);

        fprintf(stderr, "%15s (ID = %d) je\n", imie, id);
        sleep(CZAS_JEDZENIA);

        release(semID, lewyWidelec, prawyWidelec);

        signalSemafor(semID, lewyWidelec);
        signalSemafor(semID, prawyWidelec);
}

void mysl(int id, char *imie)
{
        fprintf(stderr, "%15s (ID = %d) mysli\n", imie, id);
        sleep(CZAS_MYSLENIA);
}

int main(int argc, char *argv[])
{
        key_t kluczSemafor;
        key_t kluczm;

        int semID;
        int shmID;
        int i;

        //argumenty
        int lewyWidelec = atoi(argv[2]);
        int prawyWidelec = atoi(argv[3]);
        int id = atoi(argv[4]);

        //klucze
        if ((kluczSemafor = ftok(".", 'A')) == -1)
        {
                printf("Blad ftok (A)\n");
                exit(1);
        }
        if ((kluczm = ftok(".", 'B')) == -1)
        {
                printf("Blad ftok (main)\n");
                exit(1);
        }

        semID = alokujSemafor(kluczSemafor, 6, IPC_CREAT | 0666);
        if ((shmID = shmget(kluczm, 5 * sizeof(int), IPC_CREAT | 0666)) == -1)
        {
                printf("blad shmget\n");
                exit(1);
        }
        pam = (int *)shmat(shmID, NULL, 0);
        if (*pam == -1)
        {
                printf("blad shmat\n");
                exit(1);
        }

        for (i = 0; i < CYKLE; i++)
        {
                mysl(id, argv[1]);
                jedz(id, argv[1], semID, lewyWidelec, prawyWidelec);
        }
}
