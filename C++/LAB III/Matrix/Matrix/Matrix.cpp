#pragma once
#pragma warning(disable:4996)

#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include "sqlite3.h"

namespace my_exceptions {
	class wrong_index : public std::exception
	{
		virtual const char *what() const throw()
		{
			return "wrong index number";
		}
	};
	class wrong_matrix_size : public std::exception
	{
		virtual const char *what() const throw()
		{
			return "wrong matrix size";
		}
	};
	class file_open_fail : public std::exception
	{
		virtual const char *what() const throw()
		{
			return "file opening failed";
		}
	};
}

Matrix::Matrix(int row, int col) {
	this->m1 = new double*[row];
	for (int i = 0; i < row; ++i) {
		this->m1[i] = new double[col];
		std::fill(this->m1[i], this->m1[i] + col, 0);
	}
	this->row = row;
	this->col = col;
}
Matrix::Matrix(int row, int col,const double *values) {
	this->m1 = new double*[row];
	for (int i = 0; i < row; ++i) {
		this->m1[i] = new double[col];
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			this->m1[i][j] = values[j + i * col];
		}
	}
	this->row = row;
	this->col = col;
}
Matrix::Matrix(int dim) {
	m1 = new double*[dim];
	for (int i = 0; i < dim; ++i) {
		m1[i] = new double[dim];
		std::fill(m1[i], m1[i] + dim, 0);
	}
	this->row = dim;
	this->col = dim;
}
Matrix::Matrix(const std::string path) noexcept(false) {
	std::ifstream read_file(path);
	if (read_file.is_open()) {
		read_file >> this->row >> this->col;

		this->m1 = new double*[this->rows()];
		for (int i = 0; i < this->rows(); ++i)
			this->m1[i] = new double[this->cols()];

		for (int i = 0; i < this->rows(); i++) {
			for (int j = 0; j < this->cols(); j++) {
				read_file >> this->m1[i][j];
			}
		}
	}
	else {
		throw my_exceptions::file_open_fail();
	}

}
Matrix::~Matrix()  {
	for (int i = 0; i < rows(); ++i) {
		delete[] m1[i];
	}
	delete[] m1;
}

void Matrix::set(int n, int m, double val) noexcept(false) {
	if (n < rows() && n >= 0 && m < cols() && m >= 0)
		m1[n][m] = val;
	else
		throw my_exceptions::wrong_index();
}
double Matrix::get(int n, int m) const {
	if (n < rows() && n >= 0 && m < cols() && m >= 0)
		return this->m1[n][m];
	else 
		throw my_exceptions::wrong_index();
}

Matrix* Matrix::add(const Matrix &m2) const noexcept(false) {
	int n = m2.rows();
	int m = m2.cols();
	if (n != this->rows() || m != this->cols()) 
		throw my_exceptions::wrong_matrix_size();

	Matrix *new_matrix = new Matrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			double val = this->get(i, j) + m2.get(i, j);
			new_matrix->set(i, j, val);
		}
	}
	return new_matrix;
}
Matrix* Matrix::subtract(const Matrix &m2) const noexcept(false) {
	int n = m2.rows();
	int m = m2.cols();
	if (n != this->rows() || m != this->cols()) 
		throw my_exceptions::wrong_matrix_size();

	Matrix *new_matrix = new Matrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			double val = this->get(i, j) - m2.get(i, j);
			new_matrix->set(i, j, val);
		}
	}
	return new_matrix;
}
Matrix* Matrix::multiply(const Matrix &m2) const{
	int m = m2.cols();
	int n = m2.rows();

	if (this->cols() != n) 
		throw my_exceptions::wrong_matrix_size();

	Matrix *new_matrix = new Matrix(this->rows(), m);
	//m1 NxM m2 MxK

	double sum = 0;
	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < m2.cols(); j++) {
			sum = 0;
			for (int k = 0; k < this->cols(); k++) {
				sum += this->get(i, k) * m2.get(k, j);
			}
			new_matrix->set(i, j, sum);
		}
	}
	return new_matrix;
}

int Matrix::cols() const {
	return col;
}
int Matrix::rows() const {
	return row;
}
void Matrix::print() const {
	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < this->cols(); j++) {
			std::cout << std::left << std::setw(5) << this->get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Matrix::fill_matrix() {
	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < this->cols(); j++) {
			this->set(i, j, (double)(rand() % 10));
		}
	}
}
double* Matrix::to_vector() const noexcept(false) {
	if (this->m1 == nullptr) throw "Empty matrix";
	//try catch
	double *copy = new double[this->rows() * this->cols()];
	int it = 0;
	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < this->cols(); j++) {
			copy[it] = this->get(i, j);
			it++;
		}
	}
	return copy;
}

void Matrix::store(const std::string filename) const noexcept(false) {
	int rows = this->rows();
	int cols = this->cols();

	std::ofstream outfile(filename);
	if (outfile.is_open()) {
		outfile << rows << " " << cols << std::endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				outfile << this->get(i, j) << " ";
			}
			outfile << std::endl;
		}
		outfile.close();
	}else{
		throw my_exceptions::file_open_fail();
	}
}

Matrix* Matrix::load_one(const char * db_name,int id) noexcept(false) {
	sqlite3 *db = nullptr;
	sqlite3_stmt *stmt = nullptr;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READONLY, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	char sql[50];
	sprintf(sql, "SELECT * FROM MATRIX where id = %d", id);

	rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_ROW) throw "No matrix with given id";//sqlite3_errmsg(db);

	//int id = sqlite3_column_int(stmt, 0);
	int rows = sqlite3_column_int(stmt, 1);
	int cols = sqlite3_column_int(stmt, 2);
	double *matrix = (double*)sqlite3_column_blob(stmt, 3);

	Matrix *loaded_matrix = new Matrix(rows, cols, matrix);

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	return loaded_matrix;
}
std::vector<Matrix*>* Matrix::load_all(const char * db_name) noexcept(false) {
	sqlite3 *db = nullptr;
	sqlite3_stmt *stmt = nullptr;
	std::vector<Matrix*> *results = new std::vector<Matrix*>();
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READONLY, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	const char *sql = "SELECT * FROM MATRIX";

	rc = sqlite3_prepare(db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
		//int id = sqlite3_column_int(stmt, 0);
		int rows = sqlite3_column_int(stmt, 1);
		int cols = sqlite3_column_int(stmt, 2);
		double *matrix = (double*)sqlite3_column_blob(stmt,3);
		results->push_back(new Matrix(rows, cols, matrix));
	}

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);
	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	return results;
}


void Matrix::save_to_db(const char *db_name) const noexcept(false) {
	//copy of array to make blob from it
	double *copy = to_vector();
	if (copy == nullptr) return;

	sqlite3 *db = nullptr;
	sqlite3_stmt *stmt = nullptr;
	char *zErrMsg = 0;
	int rc;

	const char *create = 
		"CREATE TABLE IF NOT EXISTS MATRIX("  \
		"ID		INTEGER  PRIMARY KEY  AUTOINCREMENT  NOT NULL," \
		"ROWS   INT									 NOT NULL," \
		"COLS   INT									 NOT NULL," \
		"ARRAY  BLOB								 NOT NULL);";

	const char *insert =
		"INSERT INTO MATRIX(ROWS, COLS, ARRAY)"\
		" VALUES(?1, ?2, ?3)";


	rc = sqlite3_open_v2(db_name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	rc = sqlite3_exec(db, create, NULL, 0, &zErrMsg);
	if (rc != SQLITE_OK) throw zErrMsg;
	
	rc = sqlite3_prepare(db,insert,-1, &stmt, NULL);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	rc = sqlite3_bind_int(stmt, 1, this->rows());
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);
	rc = sqlite3_bind_int(stmt, 2, this->cols());
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);
	rc = sqlite3_bind_blob(stmt, 3, copy, this->rows() * this->cols() * sizeof(double), SQLITE_STATIC);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	rc = sqlite3_step(stmt);	
	if (rc != SQLITE_DONE) throw sqlite3_errmsg(db);

	rc = sqlite3_finalize(stmt);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	rc = sqlite3_close(db);
	if (rc != SQLITE_OK) throw sqlite3_errmsg(db);

	delete copy;
}
