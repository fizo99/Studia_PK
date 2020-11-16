#pragma once
#include <string>

class Matrix {
protected:
	int row;
	int col;
	double **m1 = nullptr;
public:
	Matrix(int row, int col);
	Matrix(int dim);
	Matrix(const std::string path);
	virtual ~Matrix();
	void set(int n, int m, double val);
	double get(int n, int m) const;
	Matrix* add(const Matrix &m2) const;
	Matrix* subtract(const Matrix &m2) const;
	Matrix* multiply(const Matrix &m2) const;
	int cols() const;
	int rows() const;
	void print() const;
	void store(const std::string filename) const;
	//fill matrix with random values
	void fillMatrix();
};