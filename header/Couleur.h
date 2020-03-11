#ifndef COULEUR_H_
# define COULEUR_H_

class Couleur {
 public:
  float r;
  float g;
  float b;

  static Couleur white() { return Couleur(1., 1., 1.); }
  static Couleur red() { return Couleur(1., 0, 0); }
  static Couleur blue() { return Couleur(0, 0, 1.); }
  static Couleur grenn() { return Couleur(0, 1., 0); }
  
  void mult(float k){
    r = r * k;
    g = g * k;
    b = b * k;
  }


  float getMaxValue(){
    float ret = r;
    if (ret < g)
      ret = g;
    if (ret < b)
      ret = b;
    return ret;
  }
  
  Couleur(){;}
  Couleur(float R, float G, float B) : r(R), g(G), b(B) {}
  virtual ~Couleur(){;}

  float &operator[] (int ind){
    if (ind == 0)
      return r;
    else if (ind == 1)
      return g;
    else if (ind == 2)
      return b;
  }
};

#endif /* !COULEUR_H_ */
