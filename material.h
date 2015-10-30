#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"

class Material {
public:
	Material();
	float reflective;
	float transparent;
	Vec3 color;
	float reflectiveScatter;
};
#endif
