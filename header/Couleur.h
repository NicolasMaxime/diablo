#ifndef COULEUR_H_
# define COULEUR_H_

class Couleur {
 public:
  float r;
  float g;
  float b;
  
  Couleur(float R, float G, float B){
    r = R;
    g = G;
    b = B;
  }

  Couleur(){};

  void mult(float k){
    r *= k;
    g *= k;
    b *= k;
  }
  
  virtual ~Couleur(){};
};

#endif /* !COULEUR_H_ */
