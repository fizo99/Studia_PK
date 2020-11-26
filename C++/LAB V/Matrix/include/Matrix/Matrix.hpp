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
	Matrix* operator+(const Matrix &m2) const;
	Matrix* operator-(const Matrix &m2) const;
	Matrix* operator*(const Matrix &m2) const;
	bool operator==(const Matrix &m2) const;
	double* operator[](int) const;
	friend void operator<<(std::ofstream& outfile, Matrix &m2);
	int cols() const;
	int rows() const;
	void print() const;
	void store(const std::string filename) const;
	//fill matrix with random values
	void fillMatrix();
};