/*
 * Model.h
 *
 *  Created on: 23 janv. 2020
 *      Author: olejnicz5u
 */

#ifndef MODEL_H_
#define MODEL_H_

#include <vector>
#include <cstring>
#include "Triangle.h"
#include "Vecteur.h"
#include "tgaimage.h"

class Model {
public:
  const char* name;
  TGAImage diffuse;
  TGAImage normals;
  bool is_diffuse;
  bool is_normal;
  
  std::vector<Triangle> faces;		//triangles
  std::vector<Triangle> texCoord;	//textures of triangles
  std::vector<Triangle> normCoord;	//Normal of triangles
  std::vector<Vec3f> vertices;		//vertices
  std::vector<Vec3f> textures;
  std::vector<Vec3f> norms;
  
  Model(const char* file);
  
  void loadDiffuse(TGAImage img){
    std::string tag(name);
    tag = tag.substr(0, tag.size() - strlen(".obj"));
    tag = tag + "_diffuse.tga";
    diffuse = img;
    is_diffuse = diffuse.read_tga_file((char*)tag.c_str());
  }

  void loadNormal(TGAImage img){
    std::string tag(name);
    tag = tag.substr(0, tag.size() - strlen(".obj"));
    tag = tag + "_nm.tga";
    normals = img;
    is_normal = normals.read_tga_file((char*)tag.c_str());
  }

  Vec3f getVertices(int iface, int ivert){
    Triangle &t = faces.at(iface);
    Vec3f ret = vertices.at(t.points[ivert]);
    return ret;
  }
  
  Vec3f getNormals(int iface, int ivert){
    Triangle &t = normCoord.at(iface);
    Vec3f ret = norms.at(t.points[ivert]);
    return ret;
  }

  Vec3i getTextures(int iface, int ivert){
    Triangle &t = texCoord.at(iface);
    Vec3f &tmp = textures.at(t.points[ivert]);
    Vec3i ret;
    ret.x = tmp.x * diffuse.get_width();
    ret.y = tmp.y * diffuse.get_height();
    ret.z = tmp.z;
    return ret;
  }
  
  Model(){;}
  virtual ~Model();

};

#endif /* MODEL_H_ */
