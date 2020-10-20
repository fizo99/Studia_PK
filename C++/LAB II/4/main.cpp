// first build - Terminal -> Configure default build task
// ctrl+shift+B to build
// new terminal -> ./helloworld to run exe file

// to debug
// run -> add configuration -> C++(GDB) -> g++ build and debug

//if u have launch.json and tasks.json configured you can direcly run code with debugger by pressing F5

#include <iostream>
#include <algorithm> //swap

using std::cout;
using std::endl;

int equation(int a, int b, int &sum){
    sum = a+b;
    return a*b;
}

int main(int argc, char *argv[]){
    int sum = 0;
    int a = 3;
    int b = 5;
    cout << "Iloczyn: " << equation(a,b,sum) << endl << "Suma: " << sum;
}