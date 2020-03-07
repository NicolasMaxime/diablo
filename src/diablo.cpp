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

#define WIDTH 1024
#define HEIGHT 768

using namespace std;

void putpixel(vector<Couleur> &frame, int x, int y, Couleur c){
  y = (HEIGHT) - y;
  int tmp = y * WIDTH + x;
  Couleur &ref = frame.at(tmp);
  ref = c;
}

void writeImage(vector<Couleur> frame){
  std::ofstream ofs;
  int nbPixel = HEIGHT * WIDTH;
  
  ofs.open("./out.ppm",std::ios::binary);

  ofs << "P6\n" << WIDTH << " " << HEIGHT << "\n255\n";
  for (size_t i = 0; i != nbPixel; ++i) {
    Couleur &c = frame.at(i);
    float max = std::max(c.r, std::max(c.g, c.b));
    if (max>1)
      c.mult(1./max);
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.r)));
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.g)));
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.b)));
  }
  ofs.close();
}

void render(Model &mod){
  vector<Couleur> frame(WIDTH * (HEIGHT + 1));
  Couleur white(1, 1, 1);
  int size = mod.vertices.size();

  for (int i = 0; i != size; i++){
    Point3D &c = mod.vertices[i];
    float x = (c.x + 1) * WIDTH / 2;
    float y = (c.y + 1) * HEIGHT / 2;
    putpixel(frame, (int)x, (int)y, white);
  }
  
  writeImage(frame);
}

int main() {
	Model mod("rsc/diablo3_pose.obj");

	render(mod);
	cout << "Diablo says : !!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
