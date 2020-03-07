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
    
}

void Frame::putPixel(int x, int y, Couleur &c){
  if (flipVertical){
    y = height - y;
  }
  Couleur &ref = pixmap.at(y * width + x);
  ref = c;
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

void Frame::writeImage(){
  std::ofstream ofs;
  int nbPixel = height * width;
  
  ofs.open("./out.ppm",std::ios::binary);

  ofs << "P6\n" << width << " " << height << "\n255\n";
  for (size_t i = 0; i != nbPixel; ++i) {
    Couleur &c = pixmap.at(i);
    float max = std::max(c.r, std::max(c.g, c.b));
    if (max>1)
      c.mult(1./max);
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.r)));
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.g)));
    ofs << (char)(255 * std::max(0.f, std::min(1.f, c.b)));
  }
  ofs.close();

}
