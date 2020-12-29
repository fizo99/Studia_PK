#include <iomanip>
#include <iostream>

#include "Matrix.hpp"

void printOutput(const char *message, char sign, Matrix &m1, Matrix &m2, Matrix &result) {
	printf("%s\n\n", message);
	m1.print();
	printf("%c\n\n", sign);
	m2.print();
	printf("= \n\n");
	result.print();
}

int main() {
	constexpr int r = 8;
	constexpr int c = 5;
	srand(time(NULL));

	////2 arg constructor
	Matrix matrix_one(r, c);

	printf("Matrix(int rows, int cols) rows: %d, cols: %d\n", r, c);
	matrix_one.print();

	// 1 arg constructor
	Matrix matrix_square(r);

	printf("Matrix(int dim) dim: %d\n", r);
	matrix_square.print();
	
	// set()
	printf("Matrix filled with set(int n, int m, double val) method:\n");
	matrix_one.fill_matrix();
	matrix_one.print();
	
	// get()
	printf("get(int row, int col) row %d , col %d: %lf\n\n", 2, 4,
		 matrix_one.get(2, 4));
	
	// saving to file
	printf("Below matrix stored in file matrix.txt\nstore(string filename) "
		 "filename: matrix.txt\n");
	matrix_one.print();

	try {
		matrix_one.store("matrix.txt");
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}
	
	
	// constructor with file name
	printf("Below matrix loaded from file matrix.txt\nMatrix(string filename) "
		 "filename: "
		 "\"matrix.txt\"\n");
	try {
		Matrix matrix_file("matrix.txt");
		matrix_file.print();

		// cols() rows()
		printf("rows() for the matrix from above return value: %d\n",
			matrix_file.rows());
		printf("cols() for the matrix from above return value: %d\n\n",
			matrix_file.cols());
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	Matrix matrix_two(r, c);
	Matrix matrix_to_mult(c, r + 2);
	matrix_two.fill_matrix();
	matrix_to_mult.fill_matrix();
	
	// add
	try {
		Matrix *add_matrix = matrix_one.add(matrix_two);
		printOutput("ADDITION:", '+', matrix_one, matrix_two, *add_matrix);
		delete add_matrix;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	// subtract
	try {
		Matrix *sub_matrix = matrix_one.subtract(matrix_two);
		printOutput("SUBTRACION:", '-', matrix_one, matrix_two, *sub_matrix);
		delete sub_matrix;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	// multiply
	try {
		Matrix *mult_matrix = matrix_one.multiply(matrix_to_mult);
		printOutput("MULTIPLICATION:", '*', matrix_one, matrix_to_mult, *mult_matrix);
		delete mult_matrix;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	//** DB **//
	printf("\n\n** DB **\n\n");

	//saving to db
	printf("saving to db test.db\n");
	Matrix m(5, 5);
	m.fill_matrix();
	m.print();
	try {
		m.save_to_db("test.db");
	}
	catch (const char *msg) {
		std::cout << msg;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	//loading one matrix from db with given ID
	printf("\nloading matrix with id = 1 from test.db\n");
	try {
		Matrix *new_matrix = Matrix::load_one("test.db", 1);
		new_matrix->print();
		delete new_matrix;
	}
	catch (const char *msg) {
		std::cout << msg;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

	//loading all matricies from db
	printf("\nloading all matricies from test.db\n");
	try {
		std::vector<Matrix*>* all = Matrix::load_all("test.db");
		for (const Matrix *m : *all) {
			m->print();
			delete m;
		}
		delete all;
	}
	catch (const char *msg) {
		std::cout << msg;
	}
	catch (std::exception &e) {
		std::cout << e.what();
	}

}
