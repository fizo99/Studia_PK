#pragma once
#include <string>
#include <vector>

class Matrix {
protected:
	int row;
	int col;
	double **m1 = nullptr;
public:
	Matrix(int row, int col);
	Matrix(int row, int col, const double *values);
	Matrix(int dim);
	Matrix(const std::string path) noexcept(false);
	virtual ~Matrix();
	void set(int n, int m, double val);
	double get(int n, int m) const;
	Matrix* add(const Matrix &m2) const noexcept(false);
	Matrix* subtract(const Matrix &m2) const noexcept(false);
	Matrix* multiply(const Matrix &m2) const noexcept(false);
	int cols() const;
	int rows() const;
	void print() const;
	void store(const std::string filename) const noexcept(false);
	void save_to_db(const char * db_name) const noexcept(false);
	static std::vector<Matrix*>* load_all(const char * db_name) noexcept(false);
	static Matrix* load_one(const char * db_name, int id) noexcept(false);
	//fill matrix with random values
	void fill_matrix();
};