#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Frame.h"

Frame::Frame(int w, int h) {
  std::vector<Couleur> map(w * (h + 1) +1);
  pixmap = map;
  flipVertical = false;
  width = w;
  height = h;
  nbPix = w * h;  
}

void Frame::putPixel(int x, int y, Couleur &c){
  int tmp;

  tmp = y;
  if (flipVertical)
    tmp = height - y;
  tmp = tmp * width + x;
  if (x > 0 && tmp > 0 && tmp < nbPix) {
    Couleur &ref = pixmap.at(tmp);
    ref = c;
  }
}

void Frame::flipVerticaly(bool b){
  flipVertical = b;
}

void Frame::drawLine(int x0, int y0, int x1, int y1, Couleur &c){
  bool steep = false;
  if (std::abs(x0-x1)<std::abs(y0-y1)) {
    std::swap(x0, y0);
    std::swap(x1, y1);
    steep = true;
  }
  if (x0>x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }
  int dx = x1-x0;
  int dy = y1-y0;
  float derror = std::abs(dy/float(dx));
  float error = 0;
  int y = y0;
  for (int x=x0; x<=x1; x++) {
    if (steep) {
      putPixel(y, x, c);
    } else {
      putPixel(x, y, c);
    }
    error += derror;
    if (error>.5) {
      y += (y1>y0?1:-1);
      error -= 1.;
    }
  } 
}

void Frame::drawLine(Vec3f &s1, Vec3f &s2, Couleur &c){
  int x0, y0;
  int x1, y1;

  x0 = (s1.x + 1.) * width / 2.;
  x1 = (s2.x + 1.) * width / 2.;
  y0 = (s1.y + 1.) * height / 2.;
  y1 = (s2.y + 1.) * height / 2.;
  drawLine(x0, y0, x1, y1, c);
}

void Frame::drawLine(Vec3i &s1, Vec3i &s2, Couleur &c){
  drawLine(s1.x, s1.y, s2.x, s2.y, c);
}

void Frame::setEye(Vec3f e){
  eye = e;
}

void Frame::writeImage(){
  std::ofstream ofs;
  int nbPixel = height * width;
  
  ofs.open("./out.ppm",std::ios::binary);

  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (size_t i = 0; i != nbPixel; ++i) {
    Couleur &c = pixmap.at(i);
    float max = c.getMaxValue();
    if (max>1)
      c.mult(1./max);
    ofs << (char)(255 * c.r);
    ofs << (char)(255 * c.g);
    ofs << (char)(255 * c.b);
  }
  ofs.close();

}
