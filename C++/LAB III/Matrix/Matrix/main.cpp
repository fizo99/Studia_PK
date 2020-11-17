// Matrix.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <iomanip>
#include "Matrix.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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
	srand(time(NULL));
	int r = rand() % 10 + 4;
	int c = rand() % 10 + 4;

	
	Matrix *m_mult1 = new Matrix(r, c);
	Matrix *m_mult2 = new Matrix(c, r);
	Matrix *m_square = new Matrix(r);
	Matrix *m_file = nullptr;
	Matrix *add = nullptr;
	Matrix *sub = nullptr;
	Matrix *mult = nullptr;

	//

	////2 arg constructor
	printf("Matrix(int rows, int cols) rows: %d, cols: %d\n",r,c);
	m_mult1->print();
	m_mult1->fillMatrix();
	m_mult2->fillMatrix();
	//
	//1 arg constructor and set()
	printf("Matrix(int dim) dim: %d\n", r);
	m_square->print();
	printf("Matrix filled with set(int n, int m, double val) method:\n");
	m_square->fillMatrix();
	m_square->print();
	int randRow = rand() % r;
	int randCol = rand() % r;
	printf("get(int row, int col) row %d , col %d: %lf\n\n", randRow,randCol,m_square->get(randRow,randCol));

	//saving to file
	printf("store(string filename) filename: matrix.txt\n");
	m_square->print();
	m_square->store("matrix.txt");

	//constructor with file name
	printf("Matrix(string filename) filename: \"matrix.txt\"\n");
	m_file = new Matrix("matrix.txt");
	m_file->print();

	//cols() rows()
	printf("rows() for the matrix from above return value: %d\n", m_file->rows());
	printf("cols() for the matrix from above return value: %d\n\n", m_file->cols());

	
	m_file->fillMatrix();

	add = m_square->add(*m_file);
	sub = m_square->subtract(*m_file);
	mult = m_mult1->multiply(*m_mult2);
	
	
	printOutput("ADDITION:",'+', *m_square, *m_file, *add);
	printOutput("SUBTRACION:",'-', *m_square, *m_file, *sub);
	printOutput("MULTIPLICATION:",'*', *m_mult1, *m_mult2, *mult);

	delete m_mult1;
	delete m_mult2;
	delete m_square;
	delete m_file;
	delete add;
	delete sub;
	delete mult;
}
