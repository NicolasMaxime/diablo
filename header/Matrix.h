#ifndef	MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <stdlib.h>
#include "Vecteur.h"

class Vec3f;

class Matrix{
 private:
  int nLine;
  int nCol;
  float **m;
  
 public:
  void one();
  void identity();
  void display();
  int line() const { return nLine; }
  int col() const { return nCol; }
  float **getMatrix(){ return m;}
  Matrix transpose() const;

  Matrix(){ nLine = 0; nCol = 0;}
  Matrix(const int n, const int m);
  Matrix(const Matrix &c);
  virtual ~Matrix();
  
  class Proxy{
  private:
    float *m;
  public:
    Proxy(float* m) : m(m) {}

    float &operator[](int ind) const{
      return m[ind];
    }
  };

  Matrix &operator=(Matrix mat) {
    nCol = mat.col();
    nLine = mat.line();
    float **c = mat.getMatrix();
    
    m = new float*[nLine];
    for (int i = 0; i != nLine; i++){
      m[i] = new float[nCol];
      for (int j = 0; j != nCol; j++){
	m[i][j] = c[i][j];
      }
    }
    return *this;
  }

  
  Proxy operator[](int ind) const{
    return Proxy(m[ind]);
  }

  Matrix operator*(Matrix m2){
    if (nCol != m2.line()){
      std::cout << "Can't multiply Matrixs : " << nCol << " columns * ";
      std::cout << m2.line() << " lines" << std::endl;
      exit(-2);
    }
    
    Matrix ret(nLine, m2.col());
    for(int i = 0; i != nLine; i++){
	float tmp;
	for(int j = 0; j != m2.col(); j++){
	  tmp = 0;
	  for(int k = 0; k != m2.line(); k++){
	      tmp += m[i][k] * m2[k][j];	      
	  }
	  ret[i][j] = tmp;
	}	
      }
    return ret;
  }

  
};

#endif /* !MATRI_H_ */
