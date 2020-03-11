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
#define DELTA (6 + WIDTH / 100)
#define NW (WIDTH + DELTA)
using namespace std;

Matrix matrix_win(Frame &frame){
  Matrix m(4, 4);
  
  m.identity();
  m[0][0] = (float)frame.getWidth() / 2;
  m[1][1] = (float)frame.getHeight() / 2;
  return m;
}

void render(Frame &frame, Frame &frame2, Model &mod){  
  int size = mod.faces.size();
  float *zbuffer = new float[NW*HEIGHT];
  float *zbuffer2 = new float[NW*HEIGHT];
  Matrix screen = matrix_win(frame);
  Matrix proj(4, 4);
  
  proj.identity();
  proj[3][2] = 1./0.2;
  for (int z=0; z != frame.getNbPix(); z++){
    zbuffer[z] = -std::numeric_limits<float>::max();
    zbuffer2[z] = -std::numeric_limits<float>::max();
  }
  for (int i = 0; i != size; i++){
    std::vector<Vec3i> norms(3);
    std::vector<Vec3f> v(3); // vertices float
    std::vector<Vec3f> s(3); // vertices int
    std::vector<Vec3i> texs(3); //textures
    Triangle &t = mod.faces.at(i);
    Triangle &t2 = mod.texCoord.at(i);
    Triangle &t3 = mod.normCoord.at(i);
    for (int j = 0; j != 3; j++){
      v[j] = mod.vertices.at(t.points[j]);
      s[j] = Vec3f((v[j].x + 1.), (v[j].y + 1.), v[j].z);
      s[j] = MatToVec(screen * VectoMat(s[j]));
      Vec3f &tmp = mod.textures.at(t2.points[j]);
      texs[j] = Vec3i(tmp.x * 1024, tmp.y * 1024);
      Vec3f &tmp2 = mod.norms.at(t3.points[j]);
      norms[j] = Vec3i(tmp2.x * 1024, tmp2.y * 1024);
    }
    
    Vec3f normal = Vec3f(v[1].x - v[0].x, v[1].y - v[0].y, v[1].z - v[0].z);
    Vec3f tmp = Vec3f(v[0].x -  v[2].x,  v[0].y - v[2].y, v[0].z - v[2].z);
    normal = normal.cross(tmp);
    normal.normalize();
    float intensity = (float)normal.dot(frame.getLight());
    if (intensity > 0){
      triangle(mod, frame, s, intensity, zbuffer, texs, norms);
      triangle(mod, frame2, s, intensity, zbuffer2, texs, norms);
    }
  }
}

Frame anaglyph(Frame &frame, Frame &frame2) {
  Frame frameRet(WIDTH, HEIGHT);
  frameRet.flipVerticaly(true);
  for(int j = 0 ; j != HEIGHT ; j++){
    for (int i = 0; i != WIDTH; i++){
      Couleur c1 = frame.getPixel(i, j, DELTA);
      Couleur c2 = frame.getPixel(i, j);
      float max1 = std::max(c1[0], std::max(c1[1], c1[2]));
      if (max1>1) c1.mult(1./max1);
      float max2 = std::max(c2[0], std::max(c2[1], c2[2]));
      if (max2>1) c2.mult(1./max2);
      
      float avg1 = (c1.r+c1.g+c1.b)/3.;
      float avg2 = (c2.r+c2.g+c2.b)/3.;
      Couleur c(avg1, 0, avg2);
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
  frame.setEye(Vec3f(0.1, 0, 0));
  frame.setLight(Vec3f(0, 0, -1));
  frame2.flipVerticaly(true);
  frame2.setEye(Vec3f(-0.1, 0, 0));
  frame2.setLight(Vec3f(0, 0, -1));
  
  mod.loadDiffuse(TGAImage(1024, 1024, TGAImage::RGB));
  mod.loadNormal(TGAImage(1024, 1024, TGAImage::RGB));
  mod.diffuse.flip_vertically();
  mod.normals.flip_vertically();
  render(frame, frame2, mod);
  Frame frameRet = anaglyph(frame, frame2);
  frameRet.writeImage("final.ppm");
  //frame.writeImage("final.ppm");
  
  cout << "Sucess" << endl;
}
