#include <iostream>

int main(int argc, char *argv[]){
    if(argc < 3){
        std::cout << "no arguments";
        return 1;
    }
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    if(num1 < 2 || num2 < 2){
        std::cout << "wrong arguments";
        return 1;
    }

    int sumOne = 0;
    int sumTwo = 0;

    for(int i = 2; i < num1; i++)
        if(num1 % i == 0) sumOne += i;
    
    for(int i = 2; i < num2; i++)
        if(num2 % i == 0) sumTwo += i;
    

    if(sumOne == num2 && sumTwo == num1)
        std::cout << "skojarzone";
    else
        std::cout << "nieskojarzone";

    return 0;

}