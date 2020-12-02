#pragma once
#include <string>
#include <vector>

class Matrix {
protected:
	int row;
	int col;
	double **m1 = nullptr;
	//convert double** matrix to double* vector
	double* to_vector() const noexcept(false);
public:
	Matrix(int row, int col);
	Matrix(int row, int col, const double *values);
	Matrix(int dim);
	Matrix(const std::string path) noexcept(false);
	virtual ~Matrix();

	//set value at [n][m] index
	void set(int n, int m, double val);
	//get value from [n][m] index
	double get(int n, int m) const;

	//add two matricies
	Matrix* add(const Matrix &m2) const noexcept(false);
	//subtract two matricies
	Matrix* subtract(const Matrix &m2) const noexcept(false);
	//multiply two matricies
	Matrix* multiply(const Matrix &m2) const noexcept(false);

	//get number of columns
	int cols() const;
	//get number of rows
	int rows() const;

	//print matrix to console
	void print() const;
	//fill matrix with random values
	void fill_matrix();

	//save to file
	void store(const std::string filename) const noexcept(false);
	//save to databsase
	void save_to_db(const char * db_name) const noexcept(false);
	//load all matricies from database
	static std::vector<Matrix*>* load_all(const char * db_name) noexcept(false);
	//load matrix with given id from database
	static Matrix* load_one(const char * db_name, int id) noexcept(false);
};