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

using namespace std;

Couleur white(1., 1., 1.);
Couleur red(1., 0., 0.);
Couleur blue(0., 0., 1.);
Couleur green(0., 1., 0.);

Vec3f light_dir = Vec3f(0, 0, -1);
Vec3f eye(0, 0, 0);

/*
** V0_P = u V0_V1 + v V0_V2 d'où u V0_V1 + v V0_V2 + p_V0 = 0;
** (u, v, 1) orthogonal à V0_V1x, V0_V2x, p_V0x;
** (u, v, 1) orthogonal à V0_V1y, V0_V2y, p_V0y;
** d'où [V0_V1x, V0_V2x, p_V0x] x [V0_V1y, V0_V2y, p_V0y] = [u, v, 1]
*/

Vec3f barycentricT(Vec3i &p, vector<Vec3f> &v){
  Vec3f vx = Vec3f(v[2].x - v[0].x, v[1].x - v[0].x, v[0].x - p.x);
  Vec3f vy = Vec3f(v[2].y - v[0].y, v[1].y - v[0].y, v[0].y - p.y);
  Vec3f ret = vx.cross(vy);
  
  if (ret.z > -1 && ret.z < 1)
    ret = Vec3f(-1, 1, 1);
  else
    ret = Vec3f(1.f - (ret.x + ret.y)/ret.z, ret.y/ret.z, ret.x/ret.z);
  return ret;
}

void getText(Model &mod, vector<Vec3i> &t, Vec3f &bary, Couleur &ret){
  int x = (bary.x * t[0].x + bary.y * t[1].x + bary.z * t[2].x);
  int y = (bary.x * t[0].y + bary.y * t[1].y + bary.z * t[2].y);
  Vec3f res;
  TGAColor col = mod.diffuse.get(x, y);
  ret.r = col.bgra[2] / 255.;
  ret.g = col.bgra[1] / 255.;
  ret.b = col.bgra[0] / 255.;
}

void triangle(Model &mod, Frame &frame, vector<Vec3f> &v,	\
	      float *zbuffer, vector<Vec3i> texs, float intensity){
  int x0 = (std::min(v[0].x, std::min(v[1].x, v[2].x)) + 1);
  int x1 = (std::max(v[0].x, std::max(v[1].x, v[2].x)) + 1);
  int y0 = (std::min(v[0].y, std::min(v[1].y, v[2].y)) + 1);
  int y1 = (std::max(v[0].y, std::max(v[1].y, v[2].y)) + 1);


  for (int y = y0; y != y1; y++){
    for (int x = x0; x != x1; x++){
      Vec3i p = Vec3i(x, y, 0);
      float z = 0;
      Vec3f bary = barycentricT(p, v);
      if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0) {
	for (int i = 0; i != 3; i++){
	  z += v[i].z * bary[i];
	}
	int pos = x + y * frame.getWidth();
	if (zbuffer[pos] < z){
	  zbuffer[pos] = z;
	  Couleur c = blue;
	  c.mult(intensity);
	  int tmpx = (eye.x) * WIDTH / 2;
	  int tmpy = (eye.y) * HEIGHT / 2;
	  getText(mod, texs, bary, c);
	  c.mult(intensity);
	  frame.putPixel(x - tmpx, y - tmpy, c);
	}
      }
    }
  }
}

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
    if (intensity > 0)
      triangle(mod, frame, s, zbuffer, texs, std::abs(intensity));
  }
}


int main(int ac, char **av) {
  Model mod;

  if (ac >= 2 )
    mod = Model(av[1]);
  else 
    mod = Model("rsc/diablo3_pose.obj");

  Frame frame(WIDTH, HEIGHT);
  frame.flipVerticaly(true);
  mod.loadDiffuse(TGAImage(1024, 1024, TGAImage::RGB));
  mod.diffuse.flip_vertically();
  render(frame, mod);
  cout << "Sucess" << endl;
  frame.writeImage();
  return 0;
}
