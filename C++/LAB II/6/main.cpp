// first build - Terminal -> Configure default build task
// ctrl+shift+B to build
// new terminal -> ./helloworld to run exe file

// to debug
// run -> add configuration -> C++(GDB) -> g++ build and debug

//if u have launch.json and tasks.json configured you can direcly run code with debugger by pressing F5

#include <iostream>
#include <algorithm> //swap
#include <cassert>
#include <time.h>

#define size 5

using std::cout;
using std::endl;

template <typename T>
void swap (T& a, T& b){
    T c(std::move(a));
    a=std::move(b);
    b=std::move(c);
}

//works only with same size arrays
template <typename T, size_t N> 
void swap (T (&a)[N], T (&b)[N]){
    for (size_t i = 0; i<N; ++i) 
        swap (a[i],b[i]);
}

template <typename T, size_t N>
void printArr(T (&arr)[N]){
    for(int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template <typename T, size_t N> 
void test (T (&a)[N], T (&b)[N]){
    T newA[N];
    T newB[N];
    std::copy(std::begin(b), std::end(b), std::begin(newA));
    std::copy(std::begin(a), std::end(a), std::begin(newB));

    cout << "Before: " << endl;
    printArr(a);
    printArr(b);

    swap(a,b);
    for(int i = 0; i < N; i++)
        assert(a[i] == newA[i] && b[i] == newB[i] && "test failed");

    cout << "After: " << endl;
    printArr(a);
    printArr(b);
}


int main(int argc, char *argv[]){
    srand(time(NULL));

    int arr1[size] = {2,3,5,6,3};
    int arr2[size] = {1,2,3,4,5};
    int arr3[size] = {8,3,1,2,4};
    int arr4[size] = {3,4,2,1,3};

    double d1[size] = {2.32,3.23,5.22,6.17,3.32};
    double d2[size] = {1.32,2.67,3.55,4.73,5.0};

    int it = 0;

    cout << "Test " << it << endl;
    test(arr1,arr2); it++;

    cout << endl << "Test " << it << endl;
    test(arr3,arr4); it++;
    
    cout << endl << "Test " << it << endl;
    test(arr1,arr3); it++;

    cout << endl << "Test " << it << endl;
    test(arr1,arr4); it++;

    cout << endl << "Test " << it << endl;
    test(d1,d2); it++;
}
