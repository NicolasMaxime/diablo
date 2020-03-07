/*
 * Model.cpp
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Model.h"

void get_float_value(std::string& line, float *tab) {
  std::string token;
  int i;

  i = 0;
  std::istringstream ss(line);
  while (std::getline(ss, token, ' ')){
    tab[i] = std::stof(token);
    i = i + 1;
  }
}

Model::Model(const char* file) : vertices() {
  std::ifstream ifs(file);
  std::string line;
  float tab[3];

  if(ifs.is_open()){
    while(std::getline(ifs, line)){
      if (line.compare(0, 2, "v ") == 0){
	line.erase(0, 2);
	get_float_value(line, tab);
	vertices.push_back(Point3D(tab[0], tab[1], tab[2]));
      }
    }
    ifs.close();
  }
  else {
    std::cout << "Unable to open file : " << file << std::endl;
  }
}

Model::~Model() {
  // TODO Auto-generated destructor stub
}


