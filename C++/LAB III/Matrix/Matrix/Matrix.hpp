#pragma once
#include <string>

class Matrix {
protected:
	int row;
	int col;
public:
	double **m1 = nullptr;
	Matrix(int row, int col);
	Matrix(int dim);
	Matrix(std::string path);
	virtual ~Matrix();
	void set(int n, int m, double val);
	double get(int n, int m);
	Matrix* add(Matrix &m2);
	Matrix* subtract(Matrix &m2);
	Matrix* multiply(Matrix &m2);
	int cols();
	int rows();
	void print();
	void store(std::string filename);
	//fill matrix with random values
	void fillMatrix();
};