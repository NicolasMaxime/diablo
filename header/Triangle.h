/*
 * Triangle.h
 *
 *  Created on: 28 janv. 2020
 *      Author: attuku
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <vector>
#include <sstream>
#include "Point3D.h"

class Triangle {
public:
	std::vector<int> points;

	Triangle(int a, int b, int c){
		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
	}

	Triangle(std::vector<int> pts){
	  points = pts;
	}

	std::string toString(){
	  std::ostringstream ss;
	  for(int i = 0; i != points.size(); i++){
	    ss << points[i];
	    if (i != points.size() - 1)
	      ss << "/";
	  }
	  
	  return (ss.str());
	}
	
	virtual ~Triangle(){};
};

#endif /* TRIANGLE_H_ */
