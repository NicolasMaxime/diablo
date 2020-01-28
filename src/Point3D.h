/*
 * Point3D.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef POINT3D_H_
#define POINT3D_H_

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

	virtual ~Point3D();
};

#endif /* POINT3D_H_ */
