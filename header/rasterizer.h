#ifndef RASTERIZER_H_
# define RASTERIZER_H_

#include <vector>
#include "Model.h"
#include "Frame.h"
#include "Vecteur.h"

void triangle(Model &mod, Frame &frame, std::vector<Vec3f> &v, float, \
	      float *zbuffer, std::vector<Vec3i>, std::vector<Vec3i>);

#endif /* !RASTERIZER_H_ */
