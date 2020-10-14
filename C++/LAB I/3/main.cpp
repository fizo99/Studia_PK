#include <iostream>
#include <Windows.h> //SetConsoleOutputCP


int main(int argc, char *argv[]){
    SetConsoleOutputCP(CP_UTF8); //znaki UTF-8

    float masa;
    float wzrost;

    std::cout << "Podaj mase: ";
    std::cin >> masa;

    std::cout << "Podaj wzrost: ";
    std::cin >> wzrost;

    float BMI = masa / ( wzrost * wzrost );

         if(BMI < 16)   std::cout << "wygłodzenie";
    else if(BMI < 17)   std::cout << "wychudzenie";
    else if(BMI < 18.5) std::cout << "niedowaga";
    else if(BMI < 25)   std::cout << "wartość prawidłowa";
    else if(BMI < 30)   std::cout << "nadwaga";
    else if(BMI < 35)   std::cout << "I stopień otylości";
    else if(BMI < 40)   std::cout << "II stopień otyłości";
    else                std::cout << "otyłość skrajna";

    return 0; 
}