/*
 * Point3D.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include <sstream>
#include <cmath>

class Vec3f {
public:
  float x;
  float y;
  float z;

  Vec3f(float a, float b, float c){
    x = a;
    y = b;
    z = c;
  }

  Vec3f(){
    x = 0;
    y = 0;
    z = 0;
  }
	
  std::string toString(){
    std::ostringstream ss;
    ss << x << " " << y << " " << z;
    return (ss.str());
  }

  Vec3f cross(Vec3f v){
    Vec3f ret;
	  
    ret.x = y * v.z - z * v.y;
    ret.y = z * v.x - x * v.z;
    ret.z = x * v.y - y * v.x;
    return ret;
  }

  float dot(Vec3f v){
    float ret;
	  
    ret = x * v.x + y * v.y + z * v.z;
    return ret;
  }

  float norm(){
    return (sqrt(x *x + y * y + z * z));
  }
	
  void normalize(){
    float norme = norm();
    x = x / norme;
    y = y / norme;
    z = z / norme;
  }
	
  virtual ~Vec3f(){};
};

class Vec3i{
public:
  int x;
  int y;
  int z;

  Vec3i(int a, int b, int c = 0){
    x = a;
    y = b;
    z = c;
  }

  Vec3i(){
    x = 0;
    y = 0;
    z = 0;
  }
  
  float norm(){
    return (sqrt(x*x + y*y + z*z));
  }

  virtual ~Vec3i(){};
};

#endif /* POINT3D_H_ */
