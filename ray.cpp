#ifndef RAY_CPP
#define RAY_CPP

#include "ray.h"

//Build a ray from two points!
Ray::Ray(Vec3 origin,Vec3 destination) : origin(origin), direction(destination.subtract(origin).normalize()) {}

Vec3 Ray::pointAtDistance(float d) {
	return Vec3(Ray::origin.x + (Ray::direction.x*d),
				Ray::origin.y + (Ray::direction.y*d),
				Ray::origin.z + (Ray::direction.z*d));
}

#endif
