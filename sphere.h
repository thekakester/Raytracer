#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "intersectable.h"
#include "ray.h"

class Sphere : public Intersectable{
public:
	Sphere();
	Sphere(float x, float y, float z, float radius);
	float intersectsRay(Ray ray) override;
	Vec3 getNormal(Vec3 intersect) override;
	float radius;
	Vec3 pos;

protected:
	~Sphere(){}
};
#endif
