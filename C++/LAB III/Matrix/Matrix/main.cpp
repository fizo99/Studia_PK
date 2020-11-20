#include <iomanip>
#include <iostream>

#include "Matrix.hpp"

void printOutput(const char *message, char sign, Matrix &m1, Matrix &m2,
                 Matrix &result) {
  printf("%s\n\n", message);
  m1.print();
  printf("%c\n\n", sign);
  m2.print();
  printf("= \n\n");
  result.print();
}

int main() {
  int r = 8;
  int c = 5;

  ////2 arg constructor
  printf("Matrix(int rows, int cols) rows: %d, cols: %d\n", r, c);
  Matrix matrixOne(r, c);
  matrixOne.print();
  // 1 arg constructor
  printf("Matrix(int dim) dim: %d\n", r);
  Matrix matrixSquare(r);
  matrixSquare.print();

  // set()
  printf("Matrix filled with set(int n, int m, double val) method:\n");
  matrixOne.fillMatrix();
  matrixOne.print();

  // get()
  printf("get(int row, int col) row %d , col %d: %lf\n\n", 2, 4,
         matrixOne.get(2, 4));

  // saving to file
  printf("Below matrix stored in file matrix.txt\nstore(string filename) "
         "filename: matrix.txt\n");
  matrixOne.print();
  matrixOne.store("matrix.txt");

  // constructor with file name
  printf("Below matrix loaded from file matrix.txt\nMatrix(string filename) "
         "filename: "
         "\"matrix.txt\"\n");
  Matrix matrixFile("matrix.txt");
  matrixFile.print();

  // cols() rows()
  printf("rows() for the matrix from above return value: %d\n",
         matrixFile.rows());
  printf("cols() for the matrix from above return value: %d\n\n",
         matrixFile.cols());

  Matrix matrixTwo(r, c);
  Matrix matrixToMult(c, r + 2);
  matrixTwo.fillMatrix();
  matrixToMult.fillMatrix();

  Matrix *addMatrix = matrixOne.add(matrixTwo);
  Matrix *subMatrix = matrixOne.subtract(matrixTwo);
  Matrix *multMatrix = matrixOne.multiply(matrixToMult);

  printOutput("ADDITION:", '+', matrixOne, matrixTwo, *addMatrix);
  printOutput("SUBTRACION:", '-', matrixOne, matrixTwo, *subMatrix);
  printOutput("MULTIPLICATION:", '*', matrixOne, matrixToMult, *multMatrix);

  delete addMatrix;
  delete subMatrix;
  delete multMatrix;
}
