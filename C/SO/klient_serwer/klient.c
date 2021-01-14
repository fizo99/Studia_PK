#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <unistd.h>

typedef struct struktura_komunikatu
{
        long int typ_komunikatu;
        char wiadomosc[16];
        int nadawca;
} Komunikat;

int msgid;
int koniec;

#define ZAPYTANIE 1

void wysylanie()
{
        Komunikat kom, *komunikat;
        komunikat = &kom;
        while (fgets(komunikat->wiadomosc, 15, stdin) != NULL)
        {
                komunikat->nadawca = getpid();
                komunikat->typ_komunikatu = ZAPYTANIE;
                msgsnd(msgid, komunikat, sizeof(Komunikat) - sizeof(long int), 0);
                fprintf(stderr,"%d: wyslalem wiadomosc %s\n",komunikat->nadawca,komunikat->wiadomosc);
        }

        koniec = 1;
}

void odbieranie()
{
        Komunikat kom, *komunikat;
        komunikat = &kom;
        while (!koniec)
        {
                msgrcv(msgid, komunikat, sizeof(Komunikat) - sizeof(long int), getpid(), 0);
                fprintf(stderr,"%d: odebralem wiadomosc %s\n",getpid(),komunikat->wiadomosc);
        }
}

int main()
{
        pthread_t twysylanie, todbieranie;
        key_t klucz;

        printf("tworzenie klucza\n");
        if ((klucz = ftok("/", 'a')) == -1)
        {
                printf("blad tworzenia kolejki kom\n");
                exit(-1);
        }
        printf("tworzenie kolejki kom\n");
        if ((msgid = msgget(klucz, IPC_CREAT | 0666)) == -1)
        {
                printf("blad kolejki kom\n");
                exit(-1);
        }

        //tworzenie dwóch wątków
        pthread_create(&twysylanie,NULL,wysylanie,NULL);
        pthread_create(&todbieranie,NULL,odbieranie,NULL);
        // czekanie na ich zakończenie
        pthread_join(twysylanie,NULL);
        pthread_join(todbieranie,NULL);
}
