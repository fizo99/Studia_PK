// first build - Terminal -> Configure default build task
// ctrl+shift+B to build
// new terminal -> ./helloworld to run exe file

// to debug
// run -> add configuration -> C++(GDB) -> g++ build and debug

//if u have launch.json and tasks.json configured you can direcly run code with debugger by pressing F5

#include <iostream>
#include <algorithm> //swap

int main(int argc, char *argv[]){
    if(argc == 1) return 1;

    //bubblesort
    for(int i = 1; i < argc; i++){
        for(int j = i + 1; j < argc; j++){
            int v1 =  atoi(argv[i]);
            int v2 =  atoi(argv[j]);
            if( v1 > v2 ){
                std::swap(argv[i],argv[j]);
            }
        }
    }

    std::cout << "out = ";
    for(int i = 1; i < argc; i++){
        std::cout << argv[i] << " ";
    }

    return 0;
}