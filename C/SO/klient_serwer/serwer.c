#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <ctype.h>

typedef struct struktura_komunikatu
{
        long int typ_komunikatu;
        char wiadomosc[16];
        int nadawca;
} Komunikat;

int main()
{
        key_t klucz;
        int msgid, i;
        char c;
        Komunikat kom, *komunikat;
        komunikat = &kom;
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
        printf("serwer wystartowal\n");
        while (1)
        {
                msgrcv(msgid, komunikat, sizeof(Komunikat) - sizeof(long int), 1, 0);
                printf("Odebralem wiadomosc od %d: \n %s\n", komunikat->nadawca,komunikat->wiadomosc);
                for (i = 0; i < 5; i++)
                        komunikat->wiadomosc[i] = toupper(komunikat->wiadomosc[i]);
                komunikat->typ_komunikatu = komunikat->nadawca;
                msgsnd(msgid, komunikat, sizeof(Komunikat) - sizeof(long int), 0);
        }
        msgctl(msgid, IPC_RMID, 0);
        
}