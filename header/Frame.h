#ifndef FRAME_H_
#define FRAME_H_

#include <vector>
#include "Vecteur.h"
#include "Couleur.h"

class Frame {
 private:
  std::vector<Couleur> pixmap;
  bool flipVertical;
  
 public:
  int width;
  int height;
  
  Frame(int width, int height);
  virtual ~Frame(){};
  
  void putPixel(int x, int y, Couleur &c);
  void drawLine(int x0, int y0, int x1, int y1, Couleur &c);
  void drawLine(Vec3f &s1,Vec3f &s2, Couleur &c);
  void drawLine(Vec3i &s1,Vec3i &s2, Couleur &c);
  void flipVerticaly(bool);
  void writeImage();

};

#endif /* !FRAME_H_ */
