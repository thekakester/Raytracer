#ifndef VEC3_CPP
#define VEC3_CPP

#include "vec3.h"
#include <math.h>

Vec3::Vec3(float x, float y, float z){
	Vec3::x = x;
	Vec3::y = y;
	Vec3::z = z;
}

/**Create a vec3 (unit vector) as a ray from this point to
"other" and return a new vec3 object
NOTE: THIS IS OPPOSITE OF SUBTRACT()**/
Vec3 Vec3::rayTo(Vec3 other) {
	return Vec3(other.x - Vec3::x, other.y - Vec3::y, other.z - Vec3::z);
}

/**Create and return a normalized vector!**/
Vec3 Vec3::normalize() {
	float magnitude = Vec3::magnitude();
	return Vec3(Vec3::x/magnitude, Vec3::y/magnitude, Vec3::z/magnitude);
}

/**Subtract "other" from this
aka "return this-other"
NOTE: THIS IS OPPOSITE OF RAYTO()**/
Vec3 Vec3::subtract(Vec3 other) {
	return Vec3(Vec3::x-other.x, Vec3::y-other.y, Vec3::z-other.z);
}

/**Get the magnitude of this vector
**/
float Vec3::magnitude() {
	return sqrt((Vec3::x*Vec3::x)+(Vec3::y*Vec3::y)+(Vec3::z*Vec3::z));
}

/**Dot two vec3s together
**/
float Vec3::dot(Vec3 other) {
	return (Vec3::x*other.x) + (Vec3::y*other.y) + (Vec3::z*other.z);
}

#endif
