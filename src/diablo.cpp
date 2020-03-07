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
  frame.writeImage();
}

int main() {
  Model mod("rsc/diablo3_pose.obj");
  Frame frame(WIDTH, HEIGHT);

  frame.flipVerticaly(true);
  render(frame, mod);
  cout << "Diablo says : !!!Hello World!!!" << endl; // prints !!!Hello World!!!
  return 0;
}
