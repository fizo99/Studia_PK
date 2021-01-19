#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include "operacje.h"

#define INTERWAL 4
#define CYKLE 10
#define SEMAFOR_SHM 5

int *pam;
int semID;

void sig_handler(int signum)
{
    signal(SIGINT, sig_handler);

    //strefa krytyczna pamieci dzielonej
    waitSemafor(semID, SEMAFOR_SHM, 0);

    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%10d | %d\n", i, pam[i]);
    }
    printf("\n");

    signalSemafor(semID, SEMAFOR_SHM);
    return;
}

int main(int argc, char *argv[])
{
    key_t kluczm;
    key_t kluczSemafor;

    int shmID;
    int i;

    //ctrl+z
    signal(SIGINT, sig_handler);

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

    printf("WIDELEC NR | ID FILOZOFA\n");
    while (1)
        ;

    // for(i = 0; i < CYKLE; i++){
    //     sleep(INTERWAL);

    //     //strefa krytyczna pamieci dzielonej
    //     waitSemafor(semID,SEMAFOR_SHM,0);

    //     for(int i = 0; i < 5; i++){
    //         printf("%10d | %d\n",i,pam[i]);
    //     }
    //     printf("\n");

    //     signalSemafor(semID,SEMAFOR_SHM);
    // }
}
