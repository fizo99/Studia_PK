#pragma once
#include "Matrix.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>

Matrix::Matrix(int row, int col) {
	this->m1 = new double*[row];
	for (int i = 0; i < row; ++i) {
		this->m1[i] = new double[col];
		std::fill(this->m1[i], this->m1[i] + col, 0);
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
Matrix::Matrix(std::string path) {
	//TODO error handling
	std::ifstream MyReadFile(path);
	MyReadFile >> this->row >> this->col;

	this->m1 = new double*[this->rows()];
	for (int i = 0; i < this->rows(); ++i)
		this->m1[i] = new double[this->cols()];

	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < this->cols(); j++) {
			MyReadFile >> this->m1[i][j];
		}
	}
}
Matrix::~Matrix() {
	for (int i = 0; i < rows(); ++i)
		delete[] m1[i];
	delete[] m1;
}
void Matrix::set(int n, int m, double val) {
	if (n < rows() && n >= 0 && m < cols() && m >= 0)
		m1[n][m] = val;
	else
		std::cout << "Wrong index number" << std::endl;
}
double Matrix::get(int n, int m) {
	if (n < rows() && n >= 0 && m < cols() && m >= 0)
		return m1[n][m];
	else {
		std::cout << "Wrong index number" << std::endl;
		return std::numeric_limits<double>::max();
	}
}
Matrix* Matrix::subtract(Matrix &m2) {
	int n = m2.rows();
	int m = m2.cols();
	if (n != rows() || m != cols()) {
		std::cout << "Matricies have different sizes" << std::endl;
		return nullptr;
	}

	Matrix *newMatrix = new Matrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			double val = this->get(i, j) - m2.get(i, j);
			newMatrix->set(i, j, val);
		}
	}
	return newMatrix;
}
Matrix* Matrix::multiply(Matrix &m2) {
	int m = m2.cols();
	int n = m2.rows();

	if (cols() != n) {
		std::cout << "First matrix number of columns doesn`t equals second matrix number of rows" << std::endl;
		return nullptr;
	}

	Matrix *newMatrix = new Matrix(this->rows(), m);
	//m1 NxM m2 MxK

	double sum = 0;
	for (int i = 0; i < this->rows(); i++) {
		for (int j = 0; j < m2.cols(); j++) {
			sum = 0;
			for (int k = 0; k < this->cols(); k++) {
				sum += this->get(i, k) * m2.get(k, j);
			}
			newMatrix->set(i, j, sum);
		}
	}
	return newMatrix;
}
Matrix* Matrix::add(Matrix &m2) {
	int n = m2.rows();
	int m = m2.cols();
	if (n != rows() || m != cols()) {
		std::cout << "Matricies have different sizes" << std::endl;
		return nullptr;
	}

	Matrix *newMatrix = new Matrix(n, m);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			double val = this->get(i, j) + m2.get(i, j);
			newMatrix->set(i, j, val);
		}
	}
	return newMatrix;
}
int Matrix::cols() {
	return col;
}
int Matrix::rows() {
	return row;
}
void Matrix::print() {
	for (int i = 0; i < rows(); i++) {
		for (int j = 0; j < cols(); j++) {
			std::cout << std::left << std::setw(5) << get(i, j) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void Matrix::store(std::string filename) {
	std::ofstream outfile;
	outfile.open(filename, std::ofstream::out);
	if (outfile.is_open()) {
		outfile << this->rows() << " " << this->cols() << std::endl;
		for (int i = 0; i < rows(); i++) {
			for (int j = 0; j < cols(); j++) {
				outfile << get(i, j) << " ";
			}
			outfile << std::endl;
		}
		outfile.close();
	}else{
		std::cout << "Error opening file" << std::endl;
	}
}
void Matrix::fillMatrix() {
	int row = this->rows();
	int col = this->cols();
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			this->set(i, j, (double)(rand() % 10));
		}
	}
}