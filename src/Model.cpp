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

Triangle getfaces(std::string &line){
  int tab[3];
  int i, j;
  std::string tmp;
  std::string information;

  std::stringstream ss(line);
  j = 0;
  while (std::getline(ss, tmp, ' ')){
    std::stringstream sstmp(tmp);
    i = 0;
    while (std::getline(sstmp, information, '/')){
      if (i == 0){
	tab[j] = std::stoi(information) - 1;
	j = j + 1;
      }
      i = i + 1;
    } 
  }
  return Triangle(tab[0], tab[1], tab[2]);
}

Model::Model(const char* file) : vertices() {
  std::ifstream ifs(file);
  std::string line;
  float tab[3];
  char trash;
  
  if(ifs.is_open()){
    while(std::getline(ifs, line)){
      if (line.compare(0, 2, "v ") == 0){
	line.erase(0, 2);
	get_float_value(line, tab);
	vertices.push_back(Point3D(tab[0], tab[1], tab[2]));
      }
      if (line.compare(0, 2, "f ") == 0){
	int tmp[3];
	line.erase(0, 2);
	faces.push_back(getfaces(line));
	/*ifs >> trash;
	while (ifs >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
	  //for (int i=0; i<3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
	  //faces.push_back(Triangle(tmp[0], tmp[1], tmp[2]));
	
	  }*/
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


