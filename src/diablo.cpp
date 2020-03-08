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
#include <stdlib.h>
#include <time.h>
#include "Model.h"
#include "Couleur.h"
#include "Frame.h"

#define WIDTH 1024
#define HEIGHT 768
#define MAX RAND_MAX
#define ALEATOIRE (rand() / (float) RAND_MAX)
using namespace std;

Couleur white(1, 1, 1);
Couleur red(1, 0, 0);
Couleur blue(0, 0, 1);
Couleur green(0, 1, 0);

Vec3f barycentricT(Vec3f &p, Vec3f &pt1, Vec3f &pt2, Vec3f &pt3){
  Vec3f ret = Vec3f(pt1.x - p.x, pt2.x - p.x, pt3.x - p.x);
  Vec3f y = Vec3f(pt1.y - p.y, pt2.y - p.y, pt3.y - p.y);
  
  return ret.cross(y);
}

void triangle(Frame &frame, Vec3f &pt1, Vec3f &pt2, Vec3f &pt3){
  int x0 = (std::min(pt1.x, std::min(pt2.x, pt3.x)) + 1) * WIDTH / 2.;
  int x1 = (std::max(pt1.x, std::max(pt2.x, pt3.x)) + 1) * WIDTH / 2.;
  int y0 = (std::min(pt1.y, std::min(pt2.y, pt3.y)) + 1) * HEIGHT / 2.;
  int y1 = (std::max(pt1.y, std::max(pt2.y, pt3.y)) + 1) * HEIGHT / 2.;
  
  Couleur c = Couleur(ALEATOIRE, ALEATOIRE, ALEATOIRE);
  for (int j = y0; j != y1; j++){
    for (int i = x0; i != x1; i++){
      bool ret = true;
      float x = (float)i / WIDTH * 2. - 1.;
      float y = (float)j / HEIGHT * 2. - 1.;
      Vec3f p = Vec3f(x, y, 0);
      Vec3f bary = barycentricT(p, pt1, pt2, pt3);
      if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0){
	frame.putPixel(i, j, c);
      }
    }
  }
  frame.drawLine(pt1, pt2, white);
  frame.drawLine(pt2, pt3, white);
  frame.drawLine(pt3, pt1, white);
}

void nuageDePoint(Frame &frame, Model &mod){
  int size = mod.vertices.size();
  for (int i = 0; i != size; i++){
    Vec3f &c = mod.vertices[i];
    float x = (c.x + 1) * WIDTH / 2;
    float y = (c.y + 1) * HEIGHT / 2;
    frame.putPixel((int)x, (int)y, red);
    }
}

void render(Frame &frame, Model &mod){  
  int size = mod.faces.size();
  for (int i = 0; i != size; i++){
    Triangle &t = mod.faces.at(i);
    Vec3f &s1 = mod.vertices.at(t.points[0]);
    Vec3f &s2 = mod.vertices.at(t.points[1]);
    Vec3f &s3 = mod.vertices.at(t.points[2]);
    triangle(frame, s1, s2, s3);
  }
}


int main() {
  Model mod("rsc/diablo3_pose.obj");
  Frame frame(WIDTH, HEIGHT);
  srand(time(NULL));
  frame.flipVerticaly(true);
  render(frame, mod);
  cout << "Diablo says : !!!Hello World!!!" << endl;
  frame.writeImage();
  return 0;
}
