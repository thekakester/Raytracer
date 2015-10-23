#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "material.h"
#include "ray.h"

class Sphere {
public:
	Sphere();
	Sphere(float x, float y, float z, float radius);
	float intersectsRay(Ray ray);
	Material mat;
	float radius;
	Vec3 pos;
};
#endif
