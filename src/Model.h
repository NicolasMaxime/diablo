/*
 * Model.h
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#ifndef MODEL_H_
#define MODEL_H_

class Model {
public:
	Model();
	virtual ~Model();
	int nbVertices();                           // number of vertices
	int nbTriangles();                           // number of triangles
};

#endif /* MODEL_H_ */
