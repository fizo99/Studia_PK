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

void swap(int *a, int &b){
    int temp = b;
    b = *a;
    *a = temp;
}

int main(int argc, char *argv[]){
    int *a = new int(3);
    int b = 5;

    cout << "Para: "  << *a << " " << b << endl;
    swap(a,b);
    cout << "Wynik: " << *a << " " << b << endl;
}