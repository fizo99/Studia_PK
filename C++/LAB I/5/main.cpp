
#include <iostream>
#include <time.h>
#include <stdlib.h>

#define HEIGHT 2
#define WIDTH 3

void print_matrix(int m[HEIGHT][WIDTH]);

int main(int argc, char *argv[]){
    
    int result[HEIGHT][WIDTH];
    //dwie przykladowe macierze
    int m1[HEIGHT][WIDTH] = { {2,3,5},
                              {3,2,1} };
    int m2[HEIGHT][WIDTH] = { {3,1,2},
                              {3,5,8} };


    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }

    std::cout << "macierz nr 1:" << std::endl;
    print_matrix(m1);
    std::cout << "macierz nr 2:" << std::endl;
    print_matrix(m2);
    std::cout << "wynik:" << std::endl;
    print_matrix(result);

}

void print_matrix(int m[HEIGHT][WIDTH]){
    for(int i = 0; i < HEIGHT; i++){
        for(int j = 0; j < WIDTH; j++){
            std::cout << m[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}