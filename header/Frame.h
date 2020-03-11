#ifndef FRAME_H_
#define FRAME_H_

#include <vector>
#include "Vecteur.h"
#include "Couleur.h"

class Frame {
 private:
  std::vector<Couleur> pixmap;
  bool flipVertical;
  int nbPix;
  int width;
  int height;
  Vec3f eye;
  Vec3f light;
 public:
  Frame(int width, int height);
  virtual ~Frame(){};

  int getWidth() { return width; }
  int getHeight() { return height; }
  int getNbPix() { return nbPix; }
  Vec3f &getEye() { return eye; }
  Vec3f &getLight() { return light; }

  void setEye(Vec3f eye);
  void setLight(Vec3f l);
  void putPixel(int x, int y, Couleur &c);
  void drawLine(int x0, int y0, int x1, int y1, Couleur &c);
  void drawLine(Vec3f &s1,Vec3f &s2, Couleur &c);
  void drawLine(Vec3i &s1,Vec3i &s2, Couleur &c);
  void flipVerticaly(bool);
  void writeImage();

};

#endif /* !FRAME_H_ */
