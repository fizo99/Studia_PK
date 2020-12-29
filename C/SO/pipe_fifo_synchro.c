#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>


char * translateToDay(int day){
    switch(day){
        case 0:
         return "NIEDZIELA";
         break;
        case 1:
         return "PONIEDZIALEK";
         break;
        case 2:
         return "WTOREK";
         break;
        case 3:
         return "SRODA";
         break;
        case 4:
         return "CZWARTEK";
         break;
        case 5:
         return "PIATEK";
         break;
        case 6:
         return "SOBOTA";
         break;
    }
}

//proces traktowany jest jak "plik" do ktorego mozna zapisywac/ odczytywac z niego

//close(0) -> zamkniecie deskryptora czytania dla procesu (proces nie bedzie czytal ze stdin)
//close(1) -> zamkniecie deskryptora pisania dla procesu (proces nie bedzie pisal na stdout)

//oznaczenia:
// A -> proces macierzysty
// B -> proces potomny A
// C -> proces potomny B

// procesy macierzyste zanim wykonaja swoje operacje
// beda czekac az procesy potomne cos zapisza do potoku(pipe) lub kolejki(fifo)
// 1. C czyta od uzytkownika dane i zapisuje je do FIFO(fifo jest stworzone przez proces B)
// 2. B czyta dane z FIFO, konwertuje je na odpowiedni format i czesc z nich(rok) zapisuje do PIPE(pipe stworzone przez proces A)
// 3. A czyta dane z PIPE i je wypisuje

int main() {
    time_t s;
    int deskryptory[2];

    //stworzenie dwoch deskryptorow
    // deskryptory[0] -> czytanie
    // deskryptory[1] -> zapis
    pipe(deskryptory);
    time(&s);

    printf("liczba sekund dla dzis: %ld\n",s);

    switch(fork()){
        //blad tworzenia procesu
        case -1:
            fprintf(stderr,"error");
            exit(1);
        //nowy proces
        case 0:
            //stworzenie fifo (specjalny plik do zapisu/odczytu)
            if (mkfifo("./fifoFIFO", 0777) == -1)
            {   
                //fifo istnieje -> usuwamy
                system("rm fifoFIFO");
                if (mkfifo("./fifoFIFO", 0777) == -1)
                {
                    printf("blad tworzenia kolejki fifo\n");
                    exit(1);
                }
            };

            int fifodeskryptory;
            switch(fork()){
                case -1:
                    fprintf(stderr,"error");
                    exit(1);
                case 0:
                    //czytanie liczby sekund od uzytkownika
                    close(1);
                    time_t czas_uzytkownika;
                    fprintf(stderr,"C) podaj liczbe sekund: ");
                    fscanf(stdin,"%ld",&czas_uzytkownika);
                    fprintf(stderr,"C) zapis do fifo: %ld\n", czas_uzytkownika);
                    
                    //zapis do fifo
                    fifodeskryptory = open("./fifoFIFO",O_WRONLY);
                    if (fifodeskryptory != 1)
                    {	printf("blad deskryptora do zapisu fifo\n");
                        exit(1);
                    };
                    write(fifodeskryptory,&czas_uzytkownika,sizeof(czas_uzytkownika));
                    exit(1);
                default:
                    //odczyt z fifo
                    close(0);
                    fifodeskryptory = open("./fifoFIFO",O_RDONLY);
                    if (fifodeskryptory != 0)
                    {	
                        printf("blad deskryptora do odczytu fifo\n");
                        exit(1);
                    };
                    time_t odczyt;
                    read(fifodeskryptory, &odczyt, sizeof(odczyt));

                    struct tm *info;
                    info = localtime(&odczyt);

                    fprintf(stderr, "B) odczyt z fifo: %ld\n", odczyt);
                    fprintf(stderr, "B) DZIEN: %s, MIESIAC: %d ROK: %d\n", translateToDay(info->tm_wday), info->tm_mon + 1, info->tm_year + 1900);
                    
                    //zapis do pipe
                    fprintf(stderr, "B) zapis do pipe: %d\n",info->tm_year);
                    write(deskryptory[1], &info->tm_year, sizeof(int));
                    exit(1);   
            }
        //stary proces(watek macierzysty)
        default:
            //odbiera rok z pipe i wypisuje
            close(0);
            int rok;
            read(deskryptory[0],&rok,sizeof(int));
            fprintf(stderr,"A) odczyt z pipe: %d\n",rok);
    }
}


