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

template < typename T >
void swap( T & a, T & b ){
    T temp = a;
    a = b;
    b = temp;
}

int main(int argc, char *argv[]){
    int a = 3;
    int b = 5;
    cout << "Int: "  << a << " " << b << endl;
    swap(a,b);
    cout << "Wynik: " << a << " " << b << endl;

    double c = 3.14;
    double d = 2.78;
    cout << "Double: "  << c << " " << d << endl;
    swap(c,d);
    cout << "Wynik: " << c << " " << d << endl;
    
}