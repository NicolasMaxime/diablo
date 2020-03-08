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

void nuageDePoint(Frame &frame, Model &mod){
  int size = mod.vertices.size();
  for (int i = 0; i != size; i++){
    Point3D &c = mod.vertices[i];
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
      Point3D &s1 = mod.vertices[v1];
      Point3D &s2 = mod.vertices[v2];
      frame.drawLine(s1, s2, white);
      }
  }

  nuageDePoint(frame, mod);
}

bool inside(float x, float y, Point3D &v0, Point3D &v1){
  float calc = (x - v0.x) * (v1.y - v0.y) - (y - v0.y) * (v1.x - v0.x);
  return (calc > 0);
}

void triangle(Frame &frame){
  Point3D pt1(-0.5, 0.2, 0.1);
  Point3D pt2(-0.5, -0.2, 0.1);
  Point3D pt3(0.5, -0, 0.1);

  if (pt1.x >= pt2.x) std::swap(pt1, pt2);
  if (pt1.x >= pt3.x) std::swap(pt1, pt3);
  if (pt2.x >= pt3.x) std::swap(pt2, pt3);
  int x0 = (pt1.x + 1.) * WIDTH / 2.;
  int x1 = (pt3.x + 1.) * WIDTH / 2.;
  int y0 = (std::min(pt1.y, std::min(pt2.y, pt3.y)) + 1) * HEIGHT / 2;
  int y1 = (std::max(pt1.y, std::max(pt2.y, pt3.y)) + 1) * HEIGHT / 2;

  for (int j = y0; j != y1; j++){
    for (int i = x0; i != x1; i++){
      bool ret = true;
      float x = (float)i / WIDTH * 2. - 1.;
      float y = (float)j / HEIGHT * 2. - 1.;
      ret = inside(x, y, pt1, pt2);
      ret &= inside(x, y, pt2, pt3);
      ret &= inside(x, y, pt3, pt1);
      if (ret){
	frame.putPixel(i, j, white);
      }
    }
  }
  frame.drawLine(pt1, pt2, green);
  frame.drawLine(pt2, pt3, red);
  frame.drawLine(pt3, pt1, blue);

}

int main() {
  Model mod("rsc/body.obj");
  Frame frame(WIDTH, HEIGHT);

  frame.flipVerticaly(true);
  //render(frame, mod);
  triangle(frame);
  //cout << "Diablo says : !!!Hello World!!!" << endl; // prints !!!Hello World!!!
  frame.writeImage();
  return 0;
}
