#include "Vecteur.h"
#include "Matrix.h"

Matrix VectoMat(Vec3f &v){
    Matrix m(4, 1);

    m[0][0] = v.x;
    m[1][0] = v.y;
    m[2][0] = v.z;
    m[3][0] = 1;
    return m;
  }

Vec3f MatToVec(Matrix m){
    float div = m [3][0];
    float l1 = m[0][0] / div;
    float l2 = m[1][0] / div;
    float l3 = m[2][0] / div;
    return Vec3f(l1, l2, l3);
}

Matrix anaglyphMatrix(){
  Matrix m(3, 6);
    
  m[0][0] = 0.4154;
  m[0][1] = 0.4710;
  m[0][2] = 0.1669;
  m[0][3] = -0.0109;
  m[0][4] = -0.0364;
  m[0][5] = -0.0060;
  m[1][0] = -0.0458;
  m[1][1] = -0.0484;
  m[1][2] = -0.0257;
  m[1][3] = 0.3756;
  m[1][4] = 0.7333;
  m[1][5] = 0.0111;
  m[2][0] = -0.0547;
  m[2][1] = -0.0615;
  m[2][2] = 0.0128;
  m[2][3] = -0.0651;
  m[2][4] = -0.1287;
  m[2][5] = 1.2971;
  return m;
}

Matrix two_color_to_matrix(Couleur c1, Couleur c2){
  Matrix ret(6, 1);

  ret[0][0] = c1.r;
  ret[1][0] = c1.g;
  ret[2][0] = c1.b;
  ret[3][0] = c2.r;
  ret[4][0] = c2.g;
  ret[5][0] = c2.b;
  return ret;
}
