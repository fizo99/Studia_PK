// Matrix.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <iomanip>
#include "Matrix.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define c 10 // columns
#define r 4	 // rows

void printOutput(const char* message,char sign, Matrix &m1, Matrix &m2, Matrix &result) {
	std::cout << message << std::endl << std::endl;
	m1.print();
	std::cout << sign << std::endl << std::endl;
	m2.print();
	std::cout << "= " << std::endl << std::endl;
	result.print();
}

int main()
{

	Matrix *m = new Matrix(r, c);
	Matrix *w = new Matrix(r, c);
	Matrix *k = new Matrix(c, r);

	srand(time(NULL));
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			m->set(i,j,(double)(rand() % 10));
			w->set(i,j,(double)(rand() % 10));
		}
	}
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < r; j++) {
			k->set(i, j, (double)(rand() % 10));
		}
	}

	Matrix *add = m->add(*w);
	Matrix *sub = m->subtract(*w);
	Matrix *mult = m->multiply(*k);
	

	printOutput("ADD:",'+', *m, *w, *add);
	printOutput("SUBTRACT:",'-', *m, *w, *sub);
	printOutput("MULTIPLY:",'*', *m, *k, *mult);

	delete m;
	delete w;
	delete add;
	delete mult;
	delete sub;

}
