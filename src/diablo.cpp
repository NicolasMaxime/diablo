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

void render(Frame &frame, Model &mod){
  Couleur white(1, 1, 1);
  int size = mod.vertices.size();

  for (int i = 0; i != size; i++){
    Point3D &c = mod.vertices[i];
    float x = (c.x + 1) * WIDTH / 2;
    float y = (c.y + 1) * HEIGHT / 2;
    frame.putPixel((int)x, (int)y, white);
  }
  
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
