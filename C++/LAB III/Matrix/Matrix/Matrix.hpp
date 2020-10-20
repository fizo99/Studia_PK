#pragma once
#include <string>

class Matrix {
private:
	int row;
	int col;
public:
	double **m1 = nullptr;
	Matrix(int row, int col);
	Matrix(int dim);
	virtual ~Matrix();
	void set(int n, int m, double val);
	double get(int n, int m);
	Matrix* add(Matrix &m2);
	Matrix* subtract(Matrix &m2);
	Matrix* multiply(Matrix &m2);
	int cols();
	int rows();
	void print();
	void store(std::string filename, std::string path);
	Matrix(std::string path);
};