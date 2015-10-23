#ifndef SPHERE_CPP
#define SPHERE_CPP

#include "sphere.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

Sphere::Sphere() : pos(0,0,0) {
	Sphere::radius = 1;
}

Sphere::Sphere(float x, float y, float z, float radius) : pos(x,y,z) {
	Sphere::radius = 1;
}

/**Checks if this sphere intersects with a ray
NOTE: direction MUST be a unit vector!
This returns the "d" value at which the ray intersects.
If d is negative, there is no intersection
**/
float Sphere::intersectsRay(Ray ray) {
	//See https://en.wikipedia.org/wiki/Line%E2%80%93sphere_intersection
	//for line-sphere intersection formula!

	//Note . means dot!
	//under = (l . (o-c))^2  -  ||o-c||^2  +  r^2
	//l = "direction"
	//o = "origin"
	//c = "Sphere::pos"
	//r = "Sphere::radius"
	Vec3 oMinusC = ray.origin.subtract(Sphere::pos);
	float part1 = ray.direction.dot(oMinusC);
	float part2 = oMinusC.magnitude();
	float under = (part1*part1) - (part2*part2) + (Sphere::radius*Sphere::radius);

	//If under is less than 0, the value under the square root is imaginary
	//aka, there is no collision
	if (under < 0) { return -1; }	//No collision

	//If there is, we have the equation:
	//d = -(l . (o-c)) (+/-) sqrt( under)
	//In this case, we just need the closest one, so return the minus part of under
	//Note, l . (o-c) is part 1

	return (-part1) - sqrt(under);
}

#endif
