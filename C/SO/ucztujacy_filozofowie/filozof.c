#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include "operacje.h"

void jedz(char* imie, int semID, int lewyWidelec, int prawyWidelec){
        waitSemafor(semID,lewyWidelec,0);
        waitSemafor(semID,prawyWidelec,0);

        fprintf(stderr,"%s je\n", imie);
        sleep(2);

        signalSemafor(semID,lewyWidelec);
        signalSemafor(semID,prawyWidelec);
}

void mysl(char* imie){
        fprintf(stderr,"%s mysli\n", imie);
        sleep(2);
}

int main(int argc, char *argv[])
{
        key_t kluczSemafor; //klucz do semaforow
        int semID; //id semaforow
        int i;

        int lewyWidelec = atoi(argv[2]);
        int prawyWidelec = atoi(argv[3]);

        //utworzenie klucza semafora utworzonego w main
        if ((kluczSemafor = ftok(".", 'A')) == -1)
        {
                printf("Blad ftok (A)\n");
                exit(1);
        }
        semID = alokujSemafor(kluczSemafor, 6, IPC_CREAT | 0666);

        fprintf(stderr,"%s Usiadl do stolu. Widelce: %s %s\n", argv[1],argv[2],argv[3]);

        //waitSemafor(semID, 5, 0);
        struct sembuf s = {5,-1,0};
        semop(semID, &s, 1);
   

        //fprintf(stderr,"koniec\n");

        //signalSemafor(semID,5);
        while(1){
                if(semctl(semID,5,GETNCNT,NULL) == 1) {
                        //fprintf(stderr,"%d",semctl(semID,5,GETNCNT,NULL));
                        break;
                }
                jedz(argv[1], semID,lewyWidelec,prawyWidelec);
                mysl(argv[1]);
        }
}
