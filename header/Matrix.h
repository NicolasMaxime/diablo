#ifndef	MATRIX_H_
#define MATRIX_H_

class Matrix{
 private:
  int nLine;
  int nCol;
  float **m;
  
 public:
  void one();
  void identity();
  void display();
  
  Matrix(const int n, const int m);
  virtual ~Matrix();
  
  class Proxy{
  private:
    float *m;
  public:
    Proxy(float* m) : m(m) {}

    float &operator[](int ind){
      return m[ind];
    }
  };

  Proxy operator[](int ind){
    return Proxy(m[ind]);
  }
};

#endif /* !MATRI_H_ */
