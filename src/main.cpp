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


void render(Frame &frame, Model &mod){  
  int size = mod.faces.size();
  int width = frame.getWidth();
  int height = frame.getHeight();
  float *zbuffer = new float[frame.getWidth() * frame.getHeight()];
  Matrix screen = matrix_win(frame);
  
  for (int z=0; z != frame.getNbPix(); z++){
    zbuffer[z] = -std::numeric_limits<float>::max();
  }
  for (int i = 0; i != size; i++){
    std::vector<Vec3f> norms(3);
    std::vector<Vec3f> v(3); // vertices float
    std::vector<Vec3f> s(3); // vertices int
    std::vector<Vec3i> texs(3); //textures
    
    for (int j = 0; j != 3; j++){
      v[j] = mod.getVertices(i, j);
      s[j] = Vec3f((v[j].x + 1.0), (v[j].y + 1.0), v[j].z + 1.0);
      s[j] = MatToVec(screen * VectoMat(s[j]));
      texs[j] = mod.getTextures(i, j);
      norms[j] = mod.getNormals(i, j);
    }
    
    Vec3f normal = Vec3f(v[1].x - v[0].x, v[1].y - v[0].y, v[1].z - v[0].z);
    Vec3f tmp = Vec3f(v[0].x -  v[2].x,  v[0].y - v[2].y, v[0].z - v[2].z);
    normal = normal.cross(tmp);
    normal.normalize();
    float intensity = (float)normal.dot(frame.getLight());
    if (intensity < 0)
      intensity = 0;
    triangle(mod, frame, s, intensity, zbuffer, texs, norms);
  }
}

Frame anaglyph(Frame &frame, Frame &frame2) {
  Frame frameRet(WIDTH, HEIGHT);
  Matrix anag;

  anag = anaglyphBetter(); // The best of the three feel free to change it.
  //anag = anaglyphSimple();
  //anag = anaglyphOptimized();
  
  frameRet.flipVerticaly(true);
  for(int j = 0 ; j != HEIGHT ; j++){
    for (int i = 0; i != WIDTH; i++){
      Couleur c1 = frame.getPixel(i, j, DELTA);
      Couleur c2 = frame.getPixel(i, j);
      float max1 = std::max(c1[0], std::max(c1[1], c1[2]));
      if (max1>1) c1.mult(1./max1);
      float max2 = std::max(c2[0], std::max(c2[1], c2[2]));
      if (max2>1) c2.mult(1./max2);

      Matrix color = two_color_to_matrix(c1, c2);
      color = anag * color;

      Couleur c(color[0][0], color[1][0], color[2][0]);
      frameRet.putPixel(i, j, c);
    }
  }
  
  return frameRet;
}

int main(int ac, char **av) {
  Model mod;
  Frame frame(NW, HEIGHT);
  Frame frame2(NW, HEIGHT);
  float eyespace = 0.2;
  
  if (ac >= 2 )
    mod = Model(av[1]);
  else 
    mod = Model("rsc/diablo3_pose.obj");
  frame.flipVerticaly(true);
  frame.setEye(Vec3f(eyespace, 0, 0.));
  frame.setLight(Vec3f(0, 0, -1));
  frame.setOrigin(Vec3f(0, 0, 0));
  
  frame2.flipVerticaly(true);
  frame2.setEye(Vec3f(-eyespace, 0, 0));
  frame2.setLight(Vec3f(0, 0, -1));
  
  mod.loadDiffuse(TGAImage(1024, 1024, TGAImage::RGB));
  mod.diffuse.flip_vertically();
  mod.normals.flip_vertically();
  render(frame, mod);
  render(frame2, mod);

  Frame frameRet = anaglyph(frame, frame2);
  frame.writeImage("normal.ppm");
  frameRet.writeImage("anaglyphe.ppm");
  
  cout << "Sucess" << endl;
}
