/*
 * Model.cpp
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include "Model.h"

void get_float_value(std::string& line, float *tab) {
  std::string token;
  int i;

  i = 0;
  std::istringstream ss(line);
  while (std::getline(ss, token, ' ')){
    if (token.compare(" ") != 0){
      tab[i] = std::stof(token);
      i = i + 1;
    }
  }
}

Triangle getfaces(std::string &line, int nb){
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
      if (i == nb){
	tab[j] = std::stoi(information) - 1;
	j = j + 1;
      }
      i = i + 1;
    } 
  }
  return Triangle(tab[0], tab[1], tab[2]);
}

void epur_line(std::string &line, int nb){
  int i = nb;
  while (line.at(i) == ' '){
    i = i + 1;
  }
  line.erase(0, i);
}

Model::Model(const char* file) {
  std::ifstream ifs(file);
  std::string line;
  float tab[3];
  char trash;

  is_diffuse = false;
  is_normal = false;
  name = file;
  if(ifs.is_open()){
    while(std::getline(ifs, line)){
      if (line.compare(0, 2, "v ") == 0){
	epur_line(line, 2);
	get_float_value(line, tab);
	vertices.push_back(Vec3f(tab[0], tab[1], tab[2]));
      }
      else if (line.compare(0, 2, "vt") == 0){
	epur_line(line, 2);
	get_float_value(line, tab);
	textures.push_back(Vec3f(tab[0], tab[1], tab[2]));
      }
      else if (line.compare(0, 2, "vn") == 0){
	is_normal = true;
	epur_line(line, 2);
	get_float_value(line, tab);
	norms.push_back(Vec3f(tab[0], tab[1], tab[2]));
      }
      else if (line.compare(0, 2, "f ") == 0){
	epur_line(line, 2);
	faces.push_back(getfaces(line, 0));
	texCoord.push_back(getfaces(line, 1));
	normCoord.push_back(getfaces(line, 2));
      }
    }
    std::cout << "read : " << std::endl;
    std::cout << "-> " << vertices.size() << " vertices\n"\
	      << "-> " << textures.size() << " textures vertices\n"\
	      << "-> " << faces.size() << " faces" << std::endl;
    ifs.close();
  }
  else {
    std::cout << "Unable to open file : " << file << std::endl;
    exit (-1);
  }
}

Model::~Model() {
  // TODO Auto-generated destructor stub
}


