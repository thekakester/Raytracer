#ifndef SPHERE_CPP
#define SPHERE_CPP

#include "sphere.h"
#include <stdlib.h>

Sphere::Sphere() : pos(0,0,0) {
	Sphere::radius = 1;
}

Sphere::Sphere(float x, float y, float z, float radius) : pos(x,y,z) {
	Sphere::radius = 1;
}

/**Checks if this sphere intersects with a ray
NOTE: direction MUST be a unit vector!
**/
bool Sphere::intersectsRay(Vec3 origin, Vec3 direction) {
	//See https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
	//for line-sphere intersection formula!

	//Note . means dot!
	//under = (l . (o-c))^2  -  ||o-c||^2  +  r^2
	//l = "direction"
	//o = "origin"
	//c = "Sphere::pos"
	//r = "Sphere::radius"
	Vec3 oMinusC = origin.subtract(Sphere::pos);
	float part1 = direction.dot(oMinusC);
	float part2 = oMinusC.magnitude();
	float under = (part1*part1) - (part2*part2) + (Sphere::radius*Sphere::radius);

	return under >= 0;
}

#endif
