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

#define WIDTH 1024
#define HEIGHT 768

using namespace std;

Couleur white(1, 1, 1);
Couleur red(1, 0, 0);
Couleur blue(0, 0, 1);
Couleur green(0, 1, 0);

Vec3f barycentricT(Vec3f &p, Vec3f &pt1, Vec3f &pt2, Vec3f &pt3);

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
    for (int j = 0; j != 3; j++){
      int v1 = t.points[j];
      int v2 = t.points[(j + 1) %3];
      Vec3f &s1 = mod.vertices[v1];
      Vec3f &s2 = mod.vertices[v2];
      frame.drawLine(s1, s2, white);
      }
  }

  //nuageDePoint(frame, mod);
}

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

  for (int j = y0; j != y1; j++){
    for (int i = x0; i != x1; i++){
      bool ret = true;
      float x = (float)i / WIDTH * 2. - 1.;
      float y = (float)j / HEIGHT * 2. - 1.;
      Vec3f p = Vec3f(x, y, 0);
      Vec3f bary = barycentricT(p, pt1, pt2, pt3);
      if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0){
	frame.putPixel(i, j, blue);
      }
    }
  }
  frame.drawLine(pt1, pt2, white);
  frame.drawLine(pt2, pt3, white);
  frame.drawLine(pt3, pt1, white);

}

int main() {
  Model mod("rsc/body.obj");
  Frame frame(WIDTH, HEIGHT);

  frame.flipVerticaly(true);
  //render(frame, mod);
  Vec3f pt1(-0.5, 0.2, 0.1);
  Vec3f pt2(-0.5, -0.2, 0.1);
  Vec3f pt3(0.5, -0, 0.1);

  triangle(frame, pt1, pt2, pt3);
  //cout << "Diablo says : !!!Hello World!!!" << endl; // prints !!!Hello World!!!
  frame.writeImage();
  return 0;
}
