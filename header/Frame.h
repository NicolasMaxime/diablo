#ifndef FRAME_H_
#define FRAME_H_

#include <vector>
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
  void flipVerticaly(bool);
  void writeImage();
};

#endif /* !FRAME_H_ */
