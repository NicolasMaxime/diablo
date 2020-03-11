#include <iostream>
#include <new>
#include "Matrix.h"

void showError(int line, int col){
  std::cout << "can't alloc memory for matrix(" << line << ", " << col << ")";
  std::cout << std::endl;
}

void Matrix::display(){
  for (int i = 0; i != nLine; i++){
    std::cout << "[";
    for (int j = 0; j != nCol; j++){
      std::cout << m[i][j];
      if (j != nCol - 1)
	std::cout << "\t";
    }
    std::cout <<"]" << std::endl;
  }
  std::cout << std::endl;
}

void Matrix::one(){
  for (int i = 0; i != nLine; i++){
    for (int j = 0; j != nCol; j++){
      m[i][j] = 1.;
    }
  }
}

void Matrix::identity(){
  for (int i = 0; i != nLine; i++){
    for (int j = 0; j != nCol; j++){
      if (i == j)
	m[i][j] = 1;
      else
	m[i][j] = 0;
    }
  }
}

Matrix Matrix::transpose() const{
  Matrix ret(nCol, nLine);

  for (int i = 0; i != nLine; i++){
    for (int j = 0; j != nCol; j++){
      ret[j][i] = m[i][j];
    }
  }
  return ret;
}

Matrix::Matrix(const Matrix &c){
  nLine = c.line();
  nCol = c.col();

  if ((m = new float*[nLine]) == NULL){
    showError(nLine, nCol);
    exit (-1);
  }
  for (int i = 0; i != nLine; i++){
    if ((m[i] = new float[nCol]) == NULL){
      showError(nLine, nCol);
    }
    for (int j = 0; j != nCol; j++){
      m[i][j] = c[i][j];
    }
  }
}

Matrix::Matrix(const int line, const int col){
  nLine = line;
  nCol = col;

  if ((m = new float*[line]) == NULL){
    showError(line, col);
    exit (-1);
  }
  for (int i = 0; i != line; i++){
    if ((m[i] = new float[col]) == NULL){
      showError(line, col);
    }
  }
}

Matrix::~Matrix(){
  for (int i = 0; i != nLine; i++){
    delete [] m[i];
  }
  if (nLine > 0)
    delete [] m; 
}
