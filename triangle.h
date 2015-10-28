#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "material.h"
#include "intersectable.h"

class Triangle : public Intersectable{
public:
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
	float intersectsRay(Ray ray) override;
	Vec3 getNormal(Vec3 intersect) override;

	//Apparently we can't initialize arrays pre c++11,
	//so we'll do it this way since we only have 3!
	Vec3 v1;
	Vec3 v2;
	Vec3 v3;

protected:
	~Triangle(){}
};
#endif
