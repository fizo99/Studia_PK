// first build - Terminal -> Configure default build task
// ctrl+shift+B to build
// new terminal -> ./helloworld to run exe file

// to debug
// run -> add configuration -> C++(GDB) -> g++ build and debug

//if u have launch.json and tasks.json configured you can direcly run code with debugger by pressing F5

#include <iostream>
#include <algorithm> //swap
#include <cassert>
#include <typeinfo>

using std::cout;
using std::endl;

template < typename T >
void swap( T & a, T & b ){
    T temp = a;
    a = b;
    b = temp;
}

template < typename T >
void test( T a, T b ){
    T aAfter = b;
    T bAfter = a;
    std::string type = typeid(T).name();
    std::string msg = type;
    msg.append(" test failed");    

    cout << "Type: " << type << endl;
    cout << "Before " << a << " " << b << endl;
    swap(a,b);
    assert(a == aAfter && b == bAfter && msg.c_str());
    cout << "After " << aAfter << " " << bAfter << endl <<endl;
}


int main(int argc, char *argv[]){
    int a = 3, b = 5;
    test(a,b);

    double c = 3.14, d = 2.718;
    test(c,d);

    float e = 2.22, f = 13.2;
    test(e,f);

    char g = 'a',h = 'b';
    test(g,h);

    int arr[5] = {2,1,3,6,4};
    int arr2[5] = {5,2,3,6,4};
    test(arr,arr2);
}