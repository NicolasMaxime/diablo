#include <iostream>
#include <new>
#include "Matrix.h"

void showError(int line, int col){
  std::cout << "can't alloc memory for matrix(" << line << ", " << col << ")";
  std::cout << std::endl;
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

void Matrix::display(){
  for (int i = 0; i != nLine; i++){
    std::cout << "[ ";
    for (int j = 0; j != nCol; j++){
      std::cout << m[i][j] << " ";
    }
    std::cout <<"]" << std::endl;
  }
}

void Matrix::one(){
  for (int i = 0; i != nLine; i++){
    for (int j = 0; j != nCol; j++){
      m[i][j] = 1;
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

Matrix::~Matrix(){
  for (int i = 0; i != nLine; i++){
    delete m[i];
  }
  delete m;
}
