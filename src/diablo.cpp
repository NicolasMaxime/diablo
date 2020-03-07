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
  Couleur &ref = frame.at(y * WIDTH + x);
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

void render(){
  vector<Couleur> frame(WIDTH * HEIGHT);
  Couleur white(1, 1, 1);

  for (int i = 0; i != WIDTH; i++){
    putpixel(frame, i, HEIGHT / 2, white);
  }
  for (int i = 0; i != HEIGHT; i++){
    putpixel(frame, WIDTH / 2, i, white);
  }
  writeImage(frame);
}

int main() {
	Model mod("rsc/diablo3_pose.obj");
	render();
	cout << "Diablo says : !!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
