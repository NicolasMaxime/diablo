//============================================================================
// Name        : diablo.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Model.h"
#include "Couleur.h"
#include "Frame.h"
#include "Matrix.h"
#include "rasterizer.h"
#include "tgaimage.h"

#define WIDTH 1080
#define HEIGHT 720
#define DEPTH 1
#define DELTA (6 + WIDTH / 100)
#define NW (WIDTH + DELTA)
using namespace std;

Matrix matrix_win(Frame &frame, int x = 0, int y = 0, int w = 0, int h = 0){
  Matrix m(4, 4);

  m.identity();
  
  m[0][3] = x+w/2.f;
  m[1][3] = y+h/2.f;
  m[2][3] = (float)DEPTH/2.f;
  
  m[0][0] = (float)frame.getWidth() / 2;
  m[1][1] = (float)frame.getHeight() / 2;
  m[2][2] = (float) DEPTH / 2;
  return m;
}

Matrix lookat(Frame &frame, Vec3f up){
  Vec3f o = frame.getOrigin();
  Vec3f z = frame.getEye() - frame.getOrigin();
  z.normalize();
  Vec3f x = up.cross(z);
  x.normalize();
  Vec3f y = z.cross(x);
  y.normalize();
  Matrix res(4, 4);

  res.identity();
  for (int i=0; i<3; i++) {
    res[0][i] = x[i];
    res[1][i] = y[i];
    res[2][i] = z[i];
    res[i][3] = -o[i];
  }
  res.display();
  return res;
}

Matrix projection(Frame &frame){
  float z = (frame.getOrigin()).z;
  float coef;
  if (z == 0)
    coef = 0;
  else
    coef = -1.f / z;
  Matrix mat(4, 4);
  
  mat.identity();
  mat[3][2] = coef;
  return mat;
}

void render(Frame &frame, Model &mod){  
  int size = mod.faces.size();
  float *zbuffer = new float[frame.getWidth() * frame.getHeight()];
  Matrix screen = matrix_win(frame);
  Matrix proj = projection(frame);
  //Matrix lookAt = lookat(frame, Vec3f(0, 0, 0));
  for (int z=0; z != frame.getNbPix(); z++){
    zbuffer[z] = -std::numeric_limits<float>::max();
  }
  for (int i = 0; i != size; i++){
    std::vector<Vec3f> norms(3);
    std::vector<Vec3f> v(3); // vertices float
    std::vector<Vec3f> s(3); // vertices int
    std::vector<Vec3i> texs(3); //textures
    Triangle &t = mod.faces.at(i);
    Triangle &t2 = mod.texCoord.at(i);
    Triangle &t3 = mod.normCoord.at(i);
    for (int j = 0; j != 3; j++){
      v[j] = mod.vertices.at(t.points[j]);
      s[j] = Vec3f((v[j].x + 1.0), (v[j].y + 1.0), v[j].z + 1.0);
      s[j] = MatToVec(screen * proj * VectoMat(s[j]));
      Vec3f &tmp = mod.textures.at(t2.points[j]);
      texs[j] = Vec3i(tmp.x * 1024, tmp.y * 1024);
      Vec3f &tmp2 = mod.norms.at(t3.points[j]);
      norms[j] = Vec3f(tmp2.x, tmp2.y, tmp2.z);
    }
    
    Vec3f normal = Vec3f(v[1].x - v[0].x, v[1].y - v[0].y, v[1].z - v[0].z);
    Vec3f tmp = Vec3f(v[0].x -  v[2].x,  v[0].y - v[2].y, v[0].z - v[2].z);
    normal = normal.cross(tmp);
    normal.normalize();
    float intensity = (float)normal.dot(frame.getLight());
    if (intensity > 0){
      triangle(mod, frame, s, intensity, zbuffer, texs, norms);
    }
  }
}

Frame anaglyph(Frame &frame, Frame &frame2) {
  Frame frameRet(WIDTH, HEIGHT);
  Matrix anag = anaglyphMatrix();

  frameRet.flipVerticaly(true);
  for(int j = 0 ; j != HEIGHT ; j++){
    for (int i = 0; i != WIDTH; i++){
      Couleur c1 = frame.getPixel(i, j, DELTA);
      Couleur c2 = frame.getPixel(i, j);
      float max1 = std::max(c1[0], std::max(c1[1], c1[2]));
      if (max1>1) c1.mult(1./max1);
      float max2 = std::max(c2[0], std::max(c2[1], c2[2]));
      if (max2>1) c2.mult(1./max2);

      //Matrix color = two_color_to_matrix(c1, c2);
      //color = anag * color;
      float avg1 = (c1.r+c1.g+c1.b)/3.;
      float avg2 = (c2.r+c2.g+c2.b)/3.;
      Couleur c(avg1, 0, avg2);
      //Couleur c(c1.r, (c2.g), c2.b);
      frameRet.putPixel(i, j, c);
    }
  }
  
  return frameRet;
}

int main(int ac, char **av) {
  Model mod;
  Frame frame(NW, HEIGHT);
  Frame frame2(NW, HEIGHT);
  std::vector<Vec3f> v(3); // vertices float
  std::vector<Vec3f> s(3); // vertices int
  
  if (ac >= 2 )
    mod = Model(av[1]);
  else 
    mod = Model("rsc/diablo3_pose.obj");
  frame.flipVerticaly(true);
  frame.setEye(Vec3f(0.2, 0, 0));
  frame.setLight(Vec3f(0, 0, -1));
  frame2.flipVerticaly(true);
  frame2.setEye(Vec3f(-0.2, 0, 0));
  frame2.setLight(Vec3f(0, 0, -1));
  
  mod.loadDiffuse(TGAImage(1024, 1024, TGAImage::RGB));
  //mod.loadNormal(TGAImage(1024, 1024, TGAImage::RGB));
  mod.diffuse.flip_vertically();
  mod.normals.flip_vertically();
  render(frame, mod);
  render(frame2, mod);
  Frame frameRet = anaglyph(frame, frame2);
  //frame.writeImage("out.ppm");
  frameRet.writeImage("final.ppm");
  
  cout << "Sucess" << endl;
}
