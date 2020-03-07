#include <iostream>
#include <fstream>
#include <algorithm>
#include "Frame.h"

Frame::Frame(int w, int h) {
  std::vector<Couleur> map(w * (h + 1));
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
