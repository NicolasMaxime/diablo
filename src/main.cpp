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

#define WIDTH 1024
#define HEIGHT 768

using namespace std;

Vec3f light_dir = Vec3f(0, 0, -1);

void render(Frame &frame, Model &mod){  
  
  int size = mod.faces.size();
  float *zbuffer = new float[WIDTH*HEIGHT];
  for (int z=0; z != frame.getNbPix(); z++)
    zbuffer[z] = -std::numeric_limits<float>::max();
  for (int i = 0; i != size; i++){
    std::vector<Vec3f> v(3); // vertices float
    std::vector<Vec3f> s(3); // vertices int
    std::vector<Vec3i> texs(3); //textures
    Triangle &t = mod.faces.at(i);
    Triangle &t2 = mod.texCoord.at(i);
    for (int j = 0; j != 3; j++){
      v[j] = mod.vertices.at(t.points[j]);
      s[j] = Vec3f((v[j].x + 1.) * (float)WIDTH / 2., (v[j].y + 1.) * (float)HEIGHT / 2., v[j].z);
      Vec3f &tmp = mod.textures.at(t2.points[j]);
      texs[j] = Vec3i(tmp.x * 1024, tmp.y * 1024);
    }
    
    Vec3f normal = Vec3f(v[1].x - v[0].x, v[1].y - v[0].y, v[1].z - v[0].z);
    Vec3f tmp = Vec3f(v[0].x -  v[2].x,  v[0].y - v[2].y, v[0].z - v[2].z);
    normal = normal.cross(tmp);
    normal.normalize();
    float intensity = (float)normal.dot(light_dir);
    if (intensity > 0){
      triangle(mod, frame, s, zbuffer, texs, intensity);
    }
  }
}


int main(int ac, char **av) {
  Model mod;
  Frame frame(WIDTH, HEIGHT);
  
  if (ac >= 2 )
    mod = Model(av[1]);
  else 
    mod = Model("rsc/diablo3_pose.obj");
  frame.flipVerticaly(true);
  frame.setEye(Vec3f(-0.2, 0, 0));
  mod.loadDiffuse(TGAImage(1024, 1024, TGAImage::RGB));
  mod.diffuse.flip_vertically();
  render(frame, mod);
  cout << "Sucess" << endl;
  frame.writeImage();

  return 0;
}
