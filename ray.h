#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
public:	
	Ray(Vec3,Vec3);	//Build a ray from two points!
	Vec3 origin;
	Vec3 direction;
	Vec3 pointAtDistance(float);
};


#endif
