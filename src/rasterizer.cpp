#include <algorithm>
#include "tgaimage.h"
#include "Matrix.h"
#include "rasterizer.h"

using namespace std;

/*
** V0_P = u V0_V1 + v V0_V2 d'où u V0_V1 + v V0_V2 + p_V0 = 0;
** (u, v, 1) orthogonal à V0_V1x, V0_V2x, p_V0x;
** (u, v, 1) orthogonal à V0_V1y, V0_V2y, p_V0y;
** d'où [V0_V1x, V0_V2x, p_V0x] x [V0_V1y, V0_V2y, p_V0y] = [u, v, 1]
*/

Vec3f barycentricT(Vec3i &p, vector<Vec3f> &v){
  Vec3f vx = Vec3f(v[2].x - v[0].x, v[1].x - v[0].x, v[0].x - p.x);
  Vec3f vy = Vec3f(v[2].y - v[0].y, v[1].y - v[0].y, v[0].y - p.y);
  Vec3f ret = vx.cross(vy);
  
  if (ret.z > -1 && ret.z < 1)
    ret = Vec3f(-1, 1, 1);
  else
    ret = Vec3f(1.f - (ret.x + ret.y)/ret.z, ret.y/ret.z, ret.x/ret.z);
  return ret;
}

/*
** Getting texture of pixel at coordinates t;
*/

void getText(Model &mod, vector<Vec3i> &t, Vec3f &bary, Couleur &ret){
  int x = (bary.x * t[0].x + bary.y * t[1].x + bary.z * t[2].x);
  int y = (bary.x * t[0].y + bary.y * t[1].y + bary.z * t[2].y);
  Vec3f res;
  TGAColor col = mod.diffuse.get(x, y);
  ret.r = col.bgra[2] / 255.;
  ret.g = col.bgra[1] / 255.;
  ret.b = col.bgra[0] / 255.;
}

float get_intensity(Model &mod, Frame &frame, vector<Vec3f> n, Vec3f &bary){
  float ret = 0;
  float inty;
  for (int i = 0; i != 3; i++){
    n[i].normalize();
    inty = n[i].dot(frame.getLight());
    ret = ret + inty * bary[i];
  }
  /*  int x = (bary.x * n[0].x + bary.y * n[1].x + bary.z * n[2].x);
  int y = (bary.x * n[0].y + bary.y * n[1].y + bary.z * n[2].y);
  TGAColor col = mod.normals.get(n[0].x, n[0].y);
  Vec3f norm;
  norm.x = col.bgra[2] / 255.;
  norm.y = col.bgra[1] / 255.;
  norm.z = col.bgra[0] / 255.;
  norm.dot(frame.getLight());
  ret = norm.dot(frame.getLight());*/
  if (ret < 0)
    ret = ret * -1;
  return ret;
}

/*
** Rasterize triangle
*/

void triangle(Model &mod, Frame &frame, vector<Vec3f> &v, float intensity, \
	      float *zbuffer, vector<Vec3i> texs, vector<Vec3f> norms){
  int x0 = (std::min(v[0].x, std::min(v[1].x, v[2].x)) + 1);
  int x1 = (std::max(v[0].x, std::max(v[1].x, v[2].x)) + 1);
  int y0 = (std::min(v[0].y, std::min(v[1].y, v[2].y)) + 1);
  int y1 = (std::max(v[0].y, std::max(v[1].y, v[2].y)) + 1);

  for (int y = y0; y != y1; y++){
    for (int x = x0; x != x1; x++){
      Vec3i p = Vec3i(x, y, 0);
      float z = 0;
      Vec3f bary = barycentricT(p, v);
      if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0) {
	for (int i = 0; i != 3; i++){
	  z += v[i].z * bary[i];
	}
	int pos = x + y * frame.getWidth();
	if (x > 0 && x < frame.getWidth() && y > 0 && y < frame.getHeight())
	  if (zbuffer[pos] < z){
	    zbuffer[pos] = z;
	    Couleur c = Couleur::white();
	    if(mod.is_normal)
	      intensity = get_intensity(mod, frame, norms, bary);
	      if (mod.is_diffuse)
		getText(mod, texs, bary, c);
	    c.mult(intensity);

	    int tmpx = (frame.getEye()).x * frame.getWidth() / 2;
	    int tmpy = (frame.getEye()).y * frame.getHeight() / 2;
	    frame.putPixel(x - tmpx, y - tmpy, c);
	  }
      }
    }
  }
}
