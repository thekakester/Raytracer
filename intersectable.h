#ifndef INTERSECT
#define INTERSECT
#include "ray.h"
#include "material.h"
#include "vec3.h"
#include <iostream>

class Intersectable {
public:
	Material mat;
	virtual float intersectsRay(Ray ray) = 0;
	virtual Vec3 getNormal(Vec3 intersect) = 0;

protected:
	~Intersectable(){}
};
#endif
