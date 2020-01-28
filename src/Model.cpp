/*
 * Model.cpp
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#include <iostream>
#include <fstream>
#include <string>
#include "Model.h"

Model::Model(const char* file) {
	std::ifstream ifs(file);
	std::string line;

	if(ifs.is_open()){
		while(std::getline(ifs, line)){
			std::cout << line << std::endl;
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

int Model::nbVertices() {

}
