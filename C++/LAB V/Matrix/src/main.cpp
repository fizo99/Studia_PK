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
	
	std::cout << "INPUT:\n";
	m.print();
	m2.print();

	// +
	Matrix *add = m + m2;

	std::cout << "+ operator returns:\n";
	add->print();

	// -
	Matrix *subtract = m - m2;

	std::cout << "- operator returns:\n";
	subtract->print();

	// ==
	bool result = m == m2;

	std::cout << "== operator returns:\n";
	std::cout << (result == false ? "false\n" : "true\n") << "\n";

	// !=
	result = m != m2;

	std::cout << "!= operator returns:\n";
	std::cout << (result == false ? "false\n" : "true\n") << "\n";

	// []
	double* ptr = m[0];
	size_t size = _msize(ptr) / sizeof(double);

	std::cout << "[] operator ([0]) returns:\n";
	for (size_t i = 0; i < size; i++) {
		std::cout << ptr[i] << " ";
	}
	std::cout << "\n\n";

	// *
	Matrix *multiply = m * m3;

	std::cout << "* operator:\n";
	m.print();
	std::cout << "*\n";
	m3.print();
	std::cout << "=\n";
	multiply->print();

	// <<
	std::ofstream outfile;
	outfile.open("matrix.txt", std::ofstream::out);
	outfile << m;
	Matrix fromFile("matrix.txt");

	std::cout << "\n<< operator\nSAVE\n";
	m.print();
	std::cout << "READ\n";
	fromFile.print();

	// ++
	std::cout << "++ operator:\n";
	std::cout << "before:\n";
	add->print();
	std::cout << "after:\n";
	(*add)++;
	add->print();

	// --
	std::cout << "-- operator:\n";
	std::cout << "before:\n";
	subtract->print();
	std::cout << "after:\n";
	(*subtract)--;
	subtract->print();

	delete add;
	delete subtract;
	delete multiply;
}
