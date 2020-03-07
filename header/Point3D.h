/*
 * Point3D.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef POINT3D_H_
#define POINT3D_H_

#include <sstream>

class Point3D {
public:
	float x;
	float y;
	float z;

	Point3D(float a, float b, float c){
		x = a;
		y = b;
		z = c;
	}

	std::string toString(){
		std::ostringstream ss;
		ss << x << " " << y << " " << z;
		return (ss.str());
	}

	virtual ~Point3D(){};
};

#endif /* POINT3D_H_ */
