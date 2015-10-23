#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material {
public:
	Material();
	int reflective;
	Vec3 color;
};
#endif
