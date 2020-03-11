#ifndef COULEUR_H_
# define COULEUR_H_

class Couleur {
 public:
  float r;
  float g;
  float b;

  static Couleur white() { return Couleur(1., 1., 1.); }
  
  void mult(float k){
    r = r * k;
    g = g * k;
    b = b * k;
  }
  
  Couleur(){;}
  Couleur(float R, float G, float B) : r(R), g(G), b(B) {}
  virtual ~Couleur(){;}

};

#endif /* !COULEUR_H_ */
