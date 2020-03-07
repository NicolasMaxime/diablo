/*
 * Triangle.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <vector>
#include "Point3D.h"

class Triangle {
public:
	std::vector<Point3D> points;

	Triangle(Point3D a, Point3D b, Point3D c){
		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
	}

	Triangle(std::vector<Point3D> pts){
		points = pts;
	}
	
	virtual ~Triangle(){};
};

#endif /* TRIANGLE_H_ */
