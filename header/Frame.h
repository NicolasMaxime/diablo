#ifndef FRAME_H_
#define FRAME_H_

#include <vector>
#include "Point3D.h"
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
  void drawLine(Point3D &s1, Point3D &s2, Couleur &c);
  void flipVerticaly(bool);
  void writeImage();

};

#endif /* !FRAME_H_ */
