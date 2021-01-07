
#include "Matrix.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>

// CONSTRUCTORS
Matrix::Matrix(int row, int col) {
  this->m1 = new double *[row];
  for (int i = 0; i < row; ++i) {
    this->m1[i] = new double[col];
    std::fill(this->m1[i], this->m1[i] + col, 0);
  }
  this->row = row;
  this->col = col;
}
Matrix::Matrix(int dim) {
  m1 = new double *[dim];
  for (int i = 0; i < dim; ++i) {
    m1[i] = new double[dim];
    std::fill(m1[i], m1[i] + dim, 0);
  }
  this->row = dim;
  this->col = dim;
}
Matrix::Matrix(const std::string path) {
  // TODO error handling
  std::ifstream MyReadFile(path);
  MyReadFile >> this->row >> this->col;

  this->m1 = new double *[this->rows()];
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

// setter/getter
void Matrix::set(int n, int m, double val) {
  if (n < rows() && n >= 0 && m < cols() && m >= 0)
    m1[n][m] = val;
  else
    std::cout << "Wrong index number" << std::endl;
}
double Matrix::get(int n, int m) const {
  if (n < rows() && n >= 0 && m < cols() && m >= 0) {
    return this->m1[n][m];
  } else {
    std::cout << "Wrong index number" << std::endl;
    return std::numeric_limits<double>::max();
  }
}

//operators
Matrix* Matrix::operator+(const Matrix &m2) const {
	int n = m2.rows();
	int m = m2.cols();
	if (n != this->rows() || m != this->cols()) {
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
Matrix* Matrix::operator-(const Matrix &m2) const {
	int n = m2.rows();
	int m = m2.cols();
	if (n != this->rows() || m != this->cols()) {
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
Matrix* Matrix::operator*(const Matrix &m2) const {
	int m = m2.cols();
	int n = m2.rows();

	if (this->cols() != n) {
		std::cout << "First matrix number of columns doesn`t equals second matrix "
			"number of rows"
			<< std::endl;
		return nullptr;
	}

	Matrix *newMatrix = new Matrix(this->rows(), m);
	// m1 NxM m2 MxK

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
bool Matrix::operator==(const Matrix &m2) const {
	if (this->rows() == m2.rows() && this->cols() == m2.cols()) {
		for (int i = 0; i < m2.rows(); i++) {
			for (int j = 0; j < m2.cols(); j++) {
				if (this->get(i, j) != m2.get(i, j)) return false;
			}
		}
		return true;
	}
	else {
		return false;
	}
}
double* Matrix::operator[](int index) const {
	if (index >= this->rows()) {
		std::cout << "Array index out of bound, exiting";
		return nullptr;
	}
	return this->m1[index];
}
void operator<<(std::ofstream& outfile, Matrix &m2) {
	int rows = m2.rows();
	int cols = m2.cols();

	if (outfile.is_open()) {
		outfile << rows << " " << cols << std::endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				outfile << m2.get(i, j) << " ";
			}
			outfile << std::endl;
		}
		outfile.close();
	}
}

bool Matrix::operator!=(const Matrix &m2) const
{
	if (this->rows() != m2.rows() || this->cols() != m2.cols())
	{
		return true;
	}
	for (int i = 0; i < m2.rows(); i++)
	{
		for (int j = 0; j < m2.cols(); j++)
		{
			if (this->get(i, j) == m2.get(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

//add 1 to all numbers in matrix
void Matrix::operator++(int)
{
	for (int i = 0; i < this->rows(); i++)
	{
		for (int j = 0; j < this->cols(); j++)
		{
			double val = this->get(i, j) + 1.0;
			this->set(i, j, val);
		}
	}
}
//negate all numbers in matrix
void Matrix::operator--(int)
{
	for (int i = 0; i < this->rows(); i++)
	{
		for (int j = 0; j < this->cols(); j++)
		{
			double val = this->get(i, j) - 1.0;
			this->set(i, j, val);
		}
	}
}


/////////////////
int Matrix::cols() const { return col; }
int Matrix::rows() const { return row; }
void Matrix::print() const {
  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      std::cout << std::left << std::setw(5) << this->get(i, j) << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
void Matrix::store(const std::string filename) const {
  int rows = this->rows();
  int cols = this->cols();

  std::ofstream outfile;
  outfile.open(filename, std::ofstream::out);
  if (outfile.is_open()) {
    outfile << rows << " " << cols << std::endl;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        outfile << this->get(i, j) << " ";
      }
      outfile << std::endl;
    }
    outfile.close();
  } else {
    std::cout << "Error occured while opening file" << std::endl;
  }
}
void Matrix::fillMatrix() {
  for (int i = 0; i < this->rows(); i++) {
    for (int j = 0; j < this->cols(); j++) {
      this->set(i, j, (double)(rand() % 10));
    }
  }
}
