#include <iomanip>
#include <iostream>
#include <fstream>

#include "Matrix.hpp"


int main() {
	Matrix m(2, 3);
	Matrix m2(2, 3);
	Matrix m3(3, 3);
	m.fillMatrix();
	m2.fillMatrix();
	m3.fillMatrix();

	Matrix *add = m + m2;
	Matrix *subtract = m - m2;
	Matrix *multiply = m * m3;
	std::cout << "INPUT:\n";
	m.print();
	m2.print();

	std::cout << "ADDITION\n";
	add->print();
	std::cout << "SUBTRACTION\n";
	subtract->print();
	std::cout << "COMPARE: ";
	bool result = m == m2;
	std::cout << (result == 0 ? "false\n" : "true\n");
	std::cout << "MULTIPLICATION\n";
	m.print();
	std::cout << "*\n";
	m3.print();
	std::cout << "=\n";
	multiply->print();

	double* ptr = m[0];
	size_t size = _msize(ptr) / sizeof(double);
	std::cout << "First row of first matrix:\n";
	for (int i = 0; i < size; i++) {
		std::cout << ptr[i] << " ";
	}

	std::cout << "\nSAVING TO FILE MATRIX.TXT WITH << OPERATOR\n";
	m.print();
	std::ofstream outfile;
	outfile.open("matrix.txt", std::ofstream::out);
	outfile << m;
	std::cout << "READING FROM FILE MATRIX.TXT\n";
	Matrix fromFile("matrix.txt");
	fromFile.print();

	delete add;
	delete subtract;
	delete multiply;
}
