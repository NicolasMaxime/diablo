/*
 * Model.h
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include "Triangle.h"

class Model {
public:
	int nbVertices();                           // number of vertices
	int nbTriangles();                          // number of triangles

	std::vector<Triangle> triangles;			//triangles
	std::vector<Point3D> vertices;				//vertices

	Model(const char* file);
	virtual ~Model();

};

#endif /* MODEL_H_ */
