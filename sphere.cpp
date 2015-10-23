#ifndef SPHERE_CPP
#define SPHERE_CPP

#include "sphere.h"

Sphere::Sphere() : pos(0,0,0) {
	Sphere::radius = 1;
}

Sphere::Sphere(float x, float y, float z, float radius) : pos(x,y,z) {
	Sphere::radius = 1;
}

#endif
