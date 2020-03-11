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
