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

Couleur white(1., 1., 1.);
Couleur red(1., 0., 0.);
Couleur blue(0., 0., 1.);
Couleur green(0., 1., 0.);

Vec3f barycentricT(Vec3f &p, vector<Vec3f> &v){
  Vec3f x = Vec3f(v[2].x - v[0].x, v[1].x - v[0].x, v[0].x - p.x);
  Vec3f y = Vec3f(v[2].y - v[0].y, v[1].y - v[0].y, v[0].y - p.y);
  Vec3f ret = x.cross(y);
  ret = Vec3f(1.f - (ret.x + ret.y) /ret.z, ret.y/ret.z, ret.x / ret.z);
  return ret;
}

void triangle(Frame &frame, vector<Vec3f> &v, Couleur c, float *zbuffer){

  int x0 = (std::min(v[0].x, std::min(v[1].x, v[2].x)) + 1) * WIDTH / 2.;
  int x1 = (std::max(v[0].x, std::max(v[1].x, v[2].x)) + 1) * WIDTH / 2.;
  int y0 = (std::min(v[0].y, std::min(v[1].y, v[2].y)) + 1) * HEIGHT / 2.;
  int y1 = (std::max(v[0].y, std::max(v[1].y, v[2].y)) + 1) * HEIGHT / 2.;
  
  for (int j = y0; j != y1; j++){
    float y = 2.0 * (j / (float)HEIGHT) - 1.; 
    for (int i = x0; i != x1; i++){
      float x = 2. * (i / (float)WIDTH) -1.;
      Vec3f p = Vec3f(x, y, 0);
      Vec3f bary = barycentricT(p, v);
      if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0){
	for (int i = 0; i != 3; i++){
	  p.z += v[i].z * bary.z;
	}
	int pos = i + j * WIDTH;
	if (zbuffer[pos] < p.z) {
	  zbuffer[pos] = p.z;
	  frame.putPixel(i, j, c);
	}
      }
    }
  }
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
  Vec3f lightdir = Vec3f(0, 0.5, 1);
  float *zbuffer = new float[WIDTH*HEIGHT];
  for (int i=0; i != WIDTH * HEIGHT; i++)
    zbuffer[i] = -std::numeric_limits<float>::max();
  for (int i = 0; i != size; i++){
    std::vector<Vec3f> v; // vertices
    Triangle &t = mod.faces.at(i);
    for (int j = 0; j != 3; j++){
      Vec3f &tmp = mod.vertices.at(t.points[j]);
      v.push_back(tmp);
    }
    Vec3f normal = Vec3f(v[1].x - v[0].x, v[1].y - v[0].y, v[1].z - v[0].z);
    Vec3f tmp = Vec3f(v[2].x -  v[1].x,  v[2].y - v[1].y, v[2].z - v[1].z);
    normal = normal.cross(tmp);
    normal.normalize();
    float intensity = (float)normal.dot(lightdir);
    if (intensity > 0) {
      Couleur c = Couleur(intensity, intensity, intensity);
      triangle(frame, v, c, zbuffer);
    }
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
