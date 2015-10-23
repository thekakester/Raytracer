#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vec3.h"
#include "material.h"

class Triangle {
public:
	Triangle(Vec3 p1, Vec3 p2, Vec3 p3);
	Material mat;

	//Apparently we can't initialize arrays pre c++11,
	//so we'll do it this way since we only have 3!
	Vec3 vertex1;
	Vec3 vertex2;
	Vec3 vertex3;
};
#endif
