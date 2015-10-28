#ifndef RAY_CPP
#define RAY_CPP

#include "ray.h"

//Build a ray from two points!
Ray::Ray(Vec3 origin,Vec3 destination) : origin(origin), direction(destination.minus(origin).normalize()) {}

Vec3 Ray::pointAtDistance(float d) {
	return Vec3(Ray::origin.x + (Ray::direction.x*d),
				Ray::origin.y + (Ray::direction.y*d),
				Ray::origin.z + (Ray::direction.z*d));
}

/**Reflects this ray off of a given point with a given normal
 */
Ray Ray::reflect(Vec3 point, Vec3 normal) {
	//http://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
	//Calculate a reflection vector
	//r = incomingDirection - 2(incomingDirection . n)n
	//Where n is normalized
	
	float correlation = 2*Ray::direction.dot(normal);
	Vec3 doubleAngle = normal.multiplyByScalar(correlation);
	Vec3 reflection = Ray::direction.minus(doubleAngle);
	
	//Our ray constructor takes in a DESTINATION as an argument, not a direction
	//Convert direction into a destination
	Vec3 destination = point.add(reflection);
	
	//Return a ray starting at "point" in the direction of "reflection"
	return Ray(point,destination);
}

#endif
