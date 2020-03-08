/*
 * Point3D.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include <sstream>

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

	std::string toString(){
		std::ostringstream ss;
		ss << x << " " << y << " " << z;
		return (ss.str());
	}

	virtual ~Vec3f(){};
};

#endif /* POINT3D_H_ */
